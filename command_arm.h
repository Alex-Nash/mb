#ifndef __COMMAND_H
#define __COMMAND_H

#include <math.h>

#define MEM_OFFSET_DASHBOARD      (0x1000 >> 2)

#define MEM_MUTEX              (MEM_OFFSET_DASHBOARD + 0x00)
#define MEM_OFFSET_ENG_LEFT    (MEM_OFFSET_DASHBOARD + 0x05)
#define MEM_OFFSET_ENG_RIGHT   (MEM_OFFSET_DASHBOARD + 0x11)
/*#define MEM_OFFSET_ENG_EN      0x04
#define MEM_OFFSET_ENG_DIR     0x08
#define MEM_OFFSET_ENG_TORQ    0x0C*/



#define ENG_DIRECTION_BACK        0x00
#define ENG_DIRECTION_FORWARD     0x01

#define ENG_DISABLE               0x00
#define ENG_ENABLE                0x01

#define MUTEX_UNLOCK              0x00
#define MUTEX_LOCK                0x01




struct Command
{
  char position;
  unsigned int enable;         // 0x01 - Enable  ; 0x00 - Disable
  unsigned int direction;      // 0x01 - Forward ; 0x00 - Back
  unsigned int torq;
};


/*
* Write command to ram
* Return
*/
int SendCommand(Command *command);

int CommandParser(Command *command, char *str);

int SetWatchDogTimer();

int mutex_trylock();

int mutex_unlock();

int SetCosArray (void);


#endif
