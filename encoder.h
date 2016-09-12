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

#define Encoder     XSpi

u16 GetElectricalAngle(Encoder *encoder);

u16 GetMechanicalAngle(Encoder *encoder);

u16 GetMechanicalAngle(Encoder *encoder);

u16 ResetEncoder (Encoder *encoder);

Encoder* InitEncoder(Encoder *encoder, u32 SpiDeviceID);

#endif
