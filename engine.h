#ifndef __ENGINE_H
#define __ENGINE_H

#include "pwm.h"
#include "encoder.h"
#include "sincos.h"
#include "gpio.h"

struct Engine
{
  struct PwmGenerator *pwmGen;
  Encoder *encoder;
  u32 gpioBaseAddress;
};

void StartForward (struct Engine *engine, u16 power, u16 loop);

void StartBack (struct Engine *engine, u16 power, u16 loop);

void InitEngine(struct Engine *engine, struct PwmGenerator *pwmGen,
    u32 encoderDeviceID, u32 gpioBaseAddress);

#endif
