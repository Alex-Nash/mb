#ifndef __ENCODER_H
#define __ENCODER_H

#include "sincos.h"
#include "usleep-microblaze.h"
#include "xspi.h"
#include "xspi_l.h"

#define ENCODER_COMMAND_NOP         0x00
#define ENCODER_COMMAND_RD_POS		  0x10
#define ENCODER_COMMAND_SET_ZERO    0x70

#define MAX_DS_VALUE                0xFFFF

#define ENCODER_ERR                 0xFFFF

//#define Encoder     XSpi

struct Encoder
{
  XSpi *spi;
  u32 powerEnableGPIOBaseAddress;
};

/**************************************
 * Convert mechanical angle to electrical
 * Returns current electrical angle 0x000..0x1FF
 * Returns 0xFFFF in the case of error
 ***************************************/
u16 GetElectricalAngle(struct Encoder *encoder);

/**************************************
 * Reads the AMT20 Encoder
 * Returns current position 0x000..0xFFF
 * Returns 0xFFFF in the case of error
 ***************************************/
u16 GetMechanicalAngle(struct Encoder *encoder);

/**************************************
 * Reset AMT20 Encoder Position
 * Returns 0
 * Returns 0xFFFF in the case of error
 ***************************************/
u16 ResetEncoder (struct Encoder *encoder);

/******************************************
 * Initialize SPI controller of the encoder
 * Returns pointer to the SPI instance
 * if error returns NULL
 *******************************************/
struct Encoder* InitEncoder(struct Encoder *encoder, XSpi *spi,
    u32 SpiDeviceID, u32 powerEnableGPIOBaseAddress);

#endif
