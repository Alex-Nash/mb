#ifndef __ENGINE_H
#define __ENGINE_H

#include "pwm.h"
#include "encoder.h"
#include "sincos.h"
#include "gpio.h"
#include "xbram.h"

#define MEM_MUTEX       0x00
#define MEM_ENG_EN      0x04
#define MEM_ENG_DIR     0x08
#define MEM_ENG_TORQ    0x0C

struct Engine
{

  struct PwmGenerator *pwmGen;
  Encoder *encoder;
  u32 gpioBaseAddress;
};

struct Command
{
  u32 DashBoardBaseAddress;
  u32 Mutex;
  u32 Enable;
  u32 Direction;
  u32 TORQ;
};

void StartForward (struct Engine *engine, u16 power, u16 loop);

void StartBack (struct Engine *engine, u16 power, u16 loop);

void InitEngine(struct Engine *engine, struct PwmGenerator *pwmGen,
    Encoder *encoder, u32 gpioBaseAddress);

#endif
