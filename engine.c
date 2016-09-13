#include "engine.h"

void StartExecuteCommand (struct Engine *engine, struct Command command)
{
  u16 angle;

  //InitEngine(engine);

  // endless cycle
  while () {
    // read command from ram
    GetCommand(engine, command);

    if (command->Direction == (u32)ENG_DIRECTION_FORWARD )
      angle = GetOrtogonalAngleRight(GetElectricalAngle(engine->encoder));
    else
      angle = GetOrtogonalAngleLeft(GetElectricalAngle(engine->encoder));


    if (command->Enable)
      SetPwmGenerator(engine->pwmGen, (u16)angle, (u16)command->TORQ);
    else
      SetPwmGenerator(engine->pwmGen, (u16)angle, (u16)0x00);
  }
}

/*
* Read command from ram and init struct Command
* Return pointer to the struct Command
*/
Command* GetCommand(struct Engine *engine, Command *command)
{
  u32 dashBoardOfset
  // find dashboard ofset for current engine
  if (engine->position == (u32)ENG_POSITION_LEFT)
    dashBoardOfset = (u32)MEM_ENG_LEFT;
  else
    dashBoardOfset = (u32)MEM_ENG_RIGHT;

  // while Mutex is lock , waiting
  while (command->mutex)
  {
    Command->mutex = (u32) XBram_ReadReg(Command->dashBoardBaseAddress, (u32)MEM_MUTEX);
  }
  // lock mutex
  XBram_WriteReg(Command->dashBoardBaseAddress, (u32)MEM_MUTEX,(u32)MUTEX_LOCK);
  // Read command from RAM
  command->enable     = (u32) XBram_ReadReg(Command->dashBoardBaseAddress,
                            dashBoardOfset + (u32)MEM_ENG_EN);
  command->direction  = (u32) XBram_ReadReg(Command->dashBoardBaseAddress,
                            dashBoardOfset + (u32)MEM_ENG_DIR);
  command->torq       = (u32) XBram_ReadReg(Command->dashBoardBaseAddress,
                            dashBoardOfset + (u32)MEM_ENG_TORQ);
  //unlock mutex
  XBram_WriteReg(Command->DashBoardBaseAddress, (u32)MEM_MUTEX,(u32)MUTEX_UNLOCK);

  return command;

}
/*
* Init struct Command
*/
void  InitCommand(struct Command *command, u32 dashBoardBaseAddress)
{
  command->dashBoardBaseAddress = dashBoardBaseAddress;
  command->mutex                = (u32)MUTEX_LOCK;
  command->enable               = (u32)ENG_DISABLE;
  command->direction            = (u32)ENG_DIRECTION_FORWARD;
  command->torq                 = (u32)0x00;
}

void InitEngine(struct Engine *engine, struct PwmGenerator *pwmGen,
    struct Encoder *encoder, struct Command *command, u32 gpioBaseAddress, u32 position)
{
  // define Engine properties
  engine->pwmGen          = pwmGen;
  engine->encoder         = encoder;
  engine->gpioBaseAddress = gpioBaseAddress;
  engine->position        = position;

  // start 3 pwm timer (tmr1,tmr2,tmr3)
  StartPwmGenerator(engine->pwmGen);

  SetEncoderToZeroPosition(pwmGen, encoder);
}

void SetEncoderToZeroPosition(struct PwmGenerator *pwmGen, struct Encoder encoder)
{
  // turn torot to zero position
  SetPwmDS(pwmGen->APhasePwmBaseAddress, (u16)(MAX_DS_VALUE >> 1));
  usleep(100); // turn rotor waiting

  // set encoder zero position
  ResetEncoder(encoder);
  SetPwmDS(pwmGen->APhasePwmBaseAddress, (u16)(0x00));
}
