#include "engine.h"

void StartBack (struct Engine *engine, u16 power, u16 loop)
{
  u16 angle;
  //InitEngine(engine);
  StartPwmGenerator(engine->pwmGen);
  // поднимаем GPIO
  SetGpioToHi(engine->gpioBaseAddress);
  while (loop--) {
    angle = GetOrtogonalAngleRight(GetElectricalAngle(engine->encoder));
    SetPwmGenerator(engine->pwmGen, (u16)angle, (u16)power);
  }
  // опускаем GPIO
  SetGpioToLow(engine->gpioBaseAddress);
  StopPwmGenerator(engine->pwmGen);
}


void StartForward (struct Engine *engine, u16 power, u16 loop)
{
  u16 angle;
  //InitEngine(engine);
  StartPwmGenerator(engine->pwmGen);
  // поднимаем GPIO
  SetGpioToHi(engine->gpioBaseAddress);
  while (loop--) {
    angle = GetOrtogonalAngleLeft(GetElectricalAngle(engine->encoder));
    SetPwmGenerator(engine->pwmGen, (u16)angle, (u16)power);
  }
  // опускаем GPIO
  SetGpioToLow(engine->gpioBaseAddress);
  StopPwmGenerator(engine->pwmGen);

}

void InitEngine(struct Engine *engine, struct PwmGenerator *pwmGen,
    Encoder *encoder, u32 gpioBaseAddress)
{
  engine->gpioBaseAddress = gpioBaseAddress;
  engine->PwmGenerator = pwmGen;
  engine->encoder = encoder;
}
