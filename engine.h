#ifndef __ENGINE_H
#define __ENGINE_H

#include "pwm.h"
#include "encoder.h"
#include "sincos.h"
#include "gpio.h"
#include "command.h"
#include "xbram.h"

#define ENG_POSITION_LEFT         0x00
#define ENG_POSITION_RIGHT        0x01

#define ENG_DIRECTION_BACK        0x00
#define ENG_DIRECTION_FORWARD     0x01


#define MEM_MUTEX       0x00
#define MEM_ENG_LEFT    0x10
#define MEM_ENG_RIGHT   0x20
#define MEM_ENG_EN      0x04
#define MEM_ENG_DIR     0x08
#define MEM_ENG_TORQ    0x0C

struct Engine
{
  struct PwmGenerator *pwmGen;
  struct Encoder *encoder;
  u32 gpioBaseAddress;
  u8 position;                // 0x00 - Left; 0x01 - Right;
};

struct Command
{
  u32 dashBoardBaseAddress;
  u32 mutex;          // 0x01 - lock    ; 0x00 - unlock
  u32 enable;         // 0x01 - Enable  ; 0x00 - Disable
  u32 direction;      // 0x01 - Forward ; 0x00 - Back
  u32 torq;
};

void StartExecuteCommand (struct Engine *engine, struct Command command);

/*
* Read command from ram and init struct Command
* Return pointer to the struct Command
*/
Command* GetCommand(struct Engine *engine, Command *command);

/*
* Init struct Command
*/
void  InitCommand(struct Command *command, u32 dashBoardBaseAddress);

void InitEngine(struct Engine *engine, struct PwmGenerator *pwmGen,
    struct Encoder *encoder, struct Command *command, u32 gpioBaseAddress, u32 position);

void SetEncoderToZeroPosition(struct PwmGenerator *pwmGen, struct Encoder encoder);

#endif
