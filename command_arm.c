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
  if (command->position == "l")
    command_data.offset = MEM_OFFSET_ENG_LEFT;
  else
    command_data.offset = MEM_OFFSET_ENG_RIGHT;

  unsigned int mem_command[3];
  mem_command[0] = command->enable;
  mem_command[1] = command->direction;
  mem_command[2] = (unsigned long)(0xFFFF * command->torq/100.0);
  command_data.data = mem_command;
  if (ioctl(mem_file, AXI_BRAM_WRITE, &command_data))
    return -1;
  //Set wathDogTimer
  setWathDogTimer();
  //unlock mutex
  mutex_unlock();

  return 0;

}

int setWathDogTimer();
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
