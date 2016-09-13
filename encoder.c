
#include "encoder.h"

/**************************************
 * Convert mechanical angle to electrical
 * Returns current electrical angle 0x000..0x1FF
 * Returns 0xFFFF in the case of error
 ***************************************/
u16 GetElectricalAngle(struct Encoder *encoder)
{
  u16 angle;
  angle = GetMechanicalAngle(encoder->spi);
  if (angle == ENCODER_ERR)
    return ENCODER_ERR;
  return GetReferenceAngle(angle);
}

/**************************************
 * Reads the AMT20 Encoder
 * Returns current position 0x000..0xFFF
 * Returns 0xFFFF in the case of error
 ***************************************/
u16 GetMechanicalAngle(struct Encoder *encoder)
{
  u16 Position;
  u8 RespB;
  u8 SendB = 0x10;

  XSpi_Transfer(encoder->spi, &SendB, &RespB, 1); // send 0x10 to initiate read

  SendB = 0x00;  // switch to NOP
  while (RespB == 0xA5) {  // check for idle state response and cycle wait
    usleep(20);  // 20us delay
    XSpi_Transfer(encoder->spi, &SendB, &RespB, 1); // check back again
  }
  if (RespB == 0x10) { // if we got our request back
    usleep(20);  // 20us delay
    XSpi_Transfer(encoder->spi, &SendB, &RespB, 1);
    Position = RespB << 8;
    usleep(20);  // 20us delay
    XSpi_Transfer(encoder->spi, &SendB, &RespB, 1);
    Position |= RespB;

    return Position;
  }
  return ENCODER_ERR;
}

// заглушка метода
u16 GetMechanicalSpeed(struct Encoder *encoder)
{
  return 0;
}

/**************************************
 * Reset AMT20 Encoder Position
 * Returns 0
 * Returns 0xFFFF in the case of error
 ***************************************/
u16 ResetEncoder (struct Encoder *encoder)
{
  u8 RespB;
  u8 SendB = 0x70;

  XSpi_Transfer(encoder->spi, &SendB, &RespB, 1); // send 0x70 to start write eeprom

  SendB = 0x00; // switch to NOP
  while (RespB == 0xA5) { // check for idle state response and cycle wait
    usleep(20);  // 20us delay
    XSpi_Transfer(encoder->spi, &SendB, &RespB, 1); // check back again
  }
  if (RespB == 0x80)
    return 0;

  return ENCODER_ERR;
}

/******************************************
 * Initialize SPI controller of the encoder
 * Returns pointer to the SPI instance
 * if error returns NULL
 *******************************************/
Encoder * InitEncoder(struct Encoder *encoder, XSpi *spi,
    u32 SpiDeviceID, u32 powerEnableGPIOBaseAddress)
{
  // define Encoder properties
  encoder->spi = spi;
  encoder->powerEnableGPIOBaseAddress = powerEnableGPIOBaseAddress;

  XSpi_Config *ConfigPtr;	// Pointer to Configuration data

  ConfigPtr = XSpi_LookupConfig(SpiDeviceID); // Initialize the SPI driver so that it is  ready to use
  if (ConfigPtr == NULL)
    return NULL;

  if (XSpi_CfgInitialize(encoder->spi, ConfigPtr, ConfigPtr->BaseAddress) != XST_SUCCESS)
    return NULL;

  if (XSpi_SetOptions(encoder->spi, XSP_MASTER_OPTION | XSP_MANUAL_SSELECT_OPTION) != XST_SUCCESS)
    return NULL;

  XSpi_SetSlaveSelect(encoder->spi, 0xFFFF); // select the slave
  XSpi_Start(encoder->spi);
  XSpi_IntrGlobalDisable(encoder->spi);

  return encoder;
}
