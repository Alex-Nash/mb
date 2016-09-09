#include "engine.h"


void StartForward (struct Engine *engine, u16 power, u16 loop)
{
  InitEngine(engine);
  StartPwmGenerator(engine->pwmGen);
  // поднимаем GPIO
  while (loop--) {
    u16 angle;
    angle = GetOrtogonalAngleLeft(GetElectricalAngle(engine->encoder));
    SetPwmGenerator(angle, power);
  }
  // опускаем GPIO

}
void StartBack (struct Engine *engine, u16 power, u16 loop)
{
  InitEngine(engine);
  StartPwmGenerator(engine->pwmGen);
  // поднимаем GPIO
  while (loop--) {
    u16 angle;
    angle = GetOrtogonalAngleRight(GetElectricalAngle(engine->encoder));
    SetPwmGenerator(angle, power);
  }
  // опускаем GPIO
}

void InitEngine(struct Engine *engine)
{
  SetCosArray();
  InitEncoder(engine->encoder);
  InitPwmGenerator(engine->pwmGen);
}
