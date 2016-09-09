#include "engine.h"


void StartForward (struct Engine *engine, u16 power, u16 loop)
{
  u16 angle;
  InitEngine(engine);
  StartPwmGenerator(engine->pwmGen);
  // поднимаем GPIO
  SetGpioToHi(engine->gpioBaseAddress);
  while (loop--) {
    angle = GetOrtogonalAngleLeft(GetElectricalAngle(engine->encoder));
    SetPwmGenerator(angle, power);
  }
  // опускаем GPIO
  SetGpioToLow(engine->gpioBaseAddress);
  StopPwmGenerator();

}
void StartBack (struct Engine *engine, u16 power, u16 loop)
{
  u16 angle;
  InitEngine(engine);
  StartPwmGenerator(engine->pwmGen);
  // поднимаем GPIO
  SetGpioToHi(engine->gpioBaseAddress);
  while (loop--) {
    angle = GetOrtogonalAngleRight(GetElectricalAngle(engine->encoder));
    SetPwmGenerator(angle, power);
  }
  // опускаем GPIO
  SetGpioToLow(engine->gpioBaseAddress);
  StopPwmGenerator();
}

void InitEngine(struct Engine *engine, struct PWM_Generator *pwmGen,
    u32 encoderDeviceID, u32 gpioBaseAddress)
{
  InitEncoder(engine->encoder, encoderDeviceID);
  InitPwmGenerator(engine->pwmGen);
  engine->gpioBaseAddress = gpioBaseAddress;
}
