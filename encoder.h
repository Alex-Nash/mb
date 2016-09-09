#ifndef __ENCODER_H
#define __ENCODER_H

#include "sincos.h"
#include "usleep-microblaze.h"

#define ENCODER_COMMAND_NOP         0x00
#define ENCODER_COMMAND_RD_POS		  0x10
#define ENCODER_COMMAND_SET_ZERO    0x70

#define ENCODER_ERR                 0xFFFF

#define Encoder     XSpi
/*struct Encoder
{
  u32 SpiDeviceID;  // SPI device ID in device tree
  u32 BaseAddress;  // SPI base register number
  XSpi*  SpiPtr;    // Pointer to SPI device
}; */

u16 GetElectricalAngle(Encoder *encoder);

u16 GetMechanicalAngle(Encoder *encoder);

u16 GetMechanicalAngle(Encoder *encoder);

u16 ResetEncoder (Encoder *encoder);

Encoder* InitEncoder(Encoder *encoder);

#endif
