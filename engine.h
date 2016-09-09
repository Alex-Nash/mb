#ifndef __ENGINE_H
#define __ENGINE_H

#include "PWM.h"
#include "encoder.h"
#include "sincos.h"

struct Engine
{
  struct PWM_Generator pwmGen;
  struct Encoder encoder;
  u32 gpioBaseAddress;
};

void StartForward (struct Engine *engine, u16 power, u16 loop);

void StartBack (struct Engine *engine, u16 power, u16 loop);

void InitEngine(struct Engine *engine, struct PWM_Generator *pwmGen,
    u32 encoderDeviceID, u32 gpioBaseAddress);

#endif
