#include "command.h"


/*
* Write command to ram
* Return
*/
int SendCommand(Command *command)
{
  // while Mutex is lock , waiting ... then  lock mutex
  while (mutex_trylock())  {  };

  // Write command to RAM
  struct bram_rw_data command_data;
  command_data.size = 3;
  if (command->position == 'l')
    command_data.offset = MEM_OFFSET_ENG_LEFT;
  else
    command_data.offset = MEM_OFFSET_ENG_RIGHT;

  unsigned int mem_command[3];
  mem_command[0] = command->enable;
  mem_command[1] = command->direction;
  mem_command[2] = (unsigned int)(0xFFFF * command->torq/100.0);
  command_data.data = mem_command;
  if (ioctl(mem_file, AXI_BRAM_WRITE, &command_data))
    return -1;
  //Set wathDogTimer
  setWathDogTimer();
  //unlock mutex
  mutex_unlock();

  return 0;

}

int CommandParser(Command *command, char *str)
{
  unsigned int tmp_torq;

  if (strlen(str)>6)
  return -1;


  if (str[0] == 'r' || str[0] == 'l')
    command->position = (char)str[0];
  else
    return -1;

  if (str[2] == '-' || str[2] == '+')
  {
    if (str[2] == '-')
      command->direction = (unsigned int)ENG_DIRECTION_BACK);
    else
      command->direction = (unsigned int)ENG_DIRECTION_FORWARD);
    }
  }
  else
    return -1;


  char torq_buff[4];
  memcpy(torq_buff, &str[3],(strlen(str)-2);
  tmp_torq = atoi(torq_buff);
  if (tmp_torq < 0 || tmp_torq > 100)
    return -1;

  command->torq = (unsigned int)tmp_torq;
  command->enable = (unsigned int)ENG_ENABLE;

  return 0;
}

int SetWatchDogTimer()
{
  struct bram_rw_data rw_data;
  rw_data.size = 1;
  rw_data.offset = WD_TIMER_OFFSET;
  rw_data.data = 0xFFFFFFFF;
  if (ioctl(mem_file, AXI_BRAM_WRITE, &rw_data))
    return -1;
}

int mutex_trylock()
{
  struct bram_rw_data rw_data;
  rw_data.size = 1;
  rw_data.offset = MEM_MUTEX;
  rw_data.data = 1;
  if (ioctl(mem_file, AXI_BRAM_READ, &rw_data))
    return -1;
  if (rw_data.data == 1)
    return -1;

  rw_data = 1;
  if (ioctl(mem_file, AXI_BRAM_WRITE, &rw_data))
    return -1;

  return 1;
}

int mutex_unlock()
{
  struct bram_rw_data rw_data;
  rw_data.size = 1;
  rw_data.offset = MEM_MUTEX;
  rw_data.data = 0;
  if (ioctl(mem_file, AXI_BRAM_WRITE, &rw_data))
    return -1;

  return 1;
}

int SetCosArray (void)
{
  double Delta;
  u32 i;

  struct bram_rw_data rw_data;
  rw_data.size = 1;
  rw_data.offset = 0;
  rw_data.data = 0;

  Delta = 2.0 * M_PI / MAX_ANGLE_VALUE;

  for (i=0; i < MAX_ANGLE_VALUE; i++)
  {
    rw_data.data = (unsigned int)((0xFFFFFFFF)/2 * (cos(i * Delta) + 1)));
    if (ioctl(mem_file, AXI_BRAM_WRITE, &rw_data))
      return -1;
  }
  return 0;

}
