#include "engine.h"

void StartExecuteCommand (struct Engine *engine, struct Command command)
{
  u16 angle;
  //InitEngine(engine);
  StartPwmGenerator(engine->pwmGen);

  while () {
    GetCommand(command);
    if (command->Direction == (u32)0x1 )
      angle = GetOrtogonalAngleRight(GetElectricalAngle(engine->encoder));
    else
      angle = GetOrtogonalAngleLeft(GetElectricalAngle(engine->encoder));
    if (command->Enable)
      SetPwmGenerator(engine->pwmGen, (u16)angle, (u16)command->TORQ);
    else
      SetPwmGenerator(engine->pwmGen, (u16)angle, (u16)0x0000);
  }
}

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

void GetCommand(struct Command *command)
{
  while (command->Mutex)
  {
    Command->Mutex = (u32) XBram_ReadReg(Command->DashBoardBaseAddress, (u32)MEM_MUTEX);
  }
  // lock mutex
  XBram_WriteReg(Command->DashBoardBaseAddress, (u32)MEM_MUTEX,(u32) 0x1);
  command->Enable     = (u32) XBram_ReadReg(Command->DashBoardBaseAddress,
                            (u32)MEM_ENG_EN);
  command->Direction  = (u32) XBram_ReadReg(Command->DashBoardBaseAddress,
                            (u32)MEM_ENG_DIR);
  command->TORQ       = (u32) XBram_ReadReg(Command->DashBoardBaseAddress,
                            (u32)MEM_ENG_TORQ);
  //unlock mutex
  XBram_WriteReg(Command->DashBoardBaseAddress, (u32)MEM_MUTEX,(u32) 0x0);

}

void InitEngine(struct Engine *engine, struct PwmGenerator *pwmGen,
    u32 encoderDeviceID, u32 gpioBaseAddress)
{
  InitEncoder(engine->encoder, encoderDeviceID);
  //InitPwmGenerator(pwmGen);
  engine->gpioBaseAddress = gpioBaseAddress;
}
