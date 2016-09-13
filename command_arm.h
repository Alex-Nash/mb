#ifndef __COMMAND_H
#define __COMMAND_H

#define ENG_POSITION_LEFT         0x00
#define ENG_POSITION_RIGHT        0x01

#define ENG_DIRECTION_BACK        0x00
#define ENG_DIRECTION_FORWARD     0x01

#define ENG_DISABLE               0x00
#define ENG_ENABLE                0x01

#define MUTEX_UNLOCK              0x00
#define MUTEX_LOCK                0x01


#define MEM_MUTEX       0x00
#define MEM_OFFSET_ENG_LEFT    0x5
#define MEM_OFFSET_ENG_RIGHT   0x11
#define MEM_OFFSET_ENG_EN      0x04
#define MEM_OFFSET_ENG_DIR     0x08
#define MEM_OFFSET_ENG_TORQ    0x0C

struct Command
{
  //u32 dashBoardBaseAddress;
  //u32 wathDogTimer
  char position;
  unsigned int mutex;          // 0x01 - lock    ; 0x00 - unlock
  unsigned int enable;         // 0x01 - Enable  ; 0x00 - Disable
  unsigned int direction;      // 0x01 - Forward ; 0x00 - Back
  unsigned int torq;
};

Command* GetCommand(struct Engine *engine, Command *command);


#endif
