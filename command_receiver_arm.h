#ifndef COMMAND_RECEIVER_ARM_H
#define COMMAND_RECEIVER_ARM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#include "cos_arm.h"
#include "command_arm.h"
#include "axi_bram_arm.h"


#if defined(DEBUG)
 #define DEBUG_PRINT(fmt, args...) printf("DEBUG: %d:%s(): " fmt "\n", \
    __LINE__, __func__, ##args)
#else
 #define DEBUG_PRINT(fmt, args...)
#endif

#define PORT        3490 // the port client will be connecting to

#define CMDSIZE     8 // number of bytes for commands

#define LEFT        0x10 // value for cmd: select left motor
#define RIGHT       0x11 // value for cmd: select right motor

#define START       0x1 // cmd1 for test
#define STOP        0x2 // cmd2 for test

#define REVERS      0x3

#define STOP_SERVER 0xFF // stop server

#endif // DEBUG_H
