#ifndef COMMAND_ARM_H
#define COMMAND_ARM_H

#include <stdio.h>
#include <string.h>


#include "axi_bram_arm.h"

#define TORQ_MASK Ox0FFF
#define DIR_MASK  0xF000


#define MEM_OFFSET_DASHBOARD   (0x600 >> 2)
#define MEM_OFFSET_COMMAND     (MEM_OFFSET_DASHBOARD + 0x04)



#define ENG_DIRECTION_REVERSE     0x00
#define ENG_DIRECTION_FORWARD     0x01

#define ENG_DISABLE               0x00
#define ENG_ENABLE                0x01

#define MUTEX_UNLOCK              0x00
#define MUTEX_LOCK                0x01



struct Command
{
  char position;
  uint16_t enable;                 // 0x01 - Enable  ; 0x00 - Disable
  uint16_t direction;              // 0x01 - Forward ; 0x00 - Back
  uint16_t torq;		       // 0x0000..0xFFFF
};

int SendCommand(struct Command *command);
int ParseCommand(struct Command *command, char *str);

#endif
