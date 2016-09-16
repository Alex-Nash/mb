/*
** server.c -- a stream socket server for xilinx linux
*/
#define DEBUG

#include "comand_receiver_arm.h"

#define BACKLOG 0      // how many pending connections queue will hold


// function to handle cmd
int handle_cmd(char *cmd)
{
  char command_str[7];

  printf("CMD: %s\n", cmd);

  memcpy(command_arm, cmd, 7);
  printf("command_str: %s\n", command_str);

  struct Command command;
  ParseCommand(&command, command_str);

  printf(" position: %c\n", command.position);
  printf("direction: %lu\n", command.direction);
  printf("     torq: %lu\n", command.torq);

  SendCommand(&command);
  return 0;
}


void sigchld_handler(int s)
{
    while(wait(NULL) > 0);
}


int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr,"usage: server port\n");
        exit(1);
    }

    int sockfd;  // listen on sock_fd
    struct sockaddr_in my_addr;    // my address information
    struct sigaction sa;
    int yes = 1;
    int port;

    port = atoi(argv[1]);

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        DEBUG_PRINT("socket");
		exit(1);
    }

    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        DEBUG_PRINT("setsockopt");
		exit(1);
    }

    my_addr.sin_family = AF_INET;         // host byte order
    my_addr.sin_port = htons(port);       // short, network byte order
    my_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
    memset(&(my_addr.sin_zero), '\0', 8); // zero the rest of the struct

    if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        DEBUG_PRINT("bind");
		exit(1);
    }

    if(listen(sockfd, SOMAXCONN) == -1) {
        DEBUG_PRINT("listen");
		exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if(sigaction(SIGCHLD, &sa, NULL) == -1) {
        DEBUG_PRINT("sigaction");
		exit(1);
    }

    // Set cos array
    if (SetCosArray() < 0)
      printf("Command recever: error set cos array\n");

    // main accept() only one connection
    while(1)
    {
        int client_fd; // new connection or reset of connetction
        struct sockaddr_in their_addr; // connector's address information
        int sin_size;

        printf("Wait for connection...\n");

        sin_size = sizeof(struct sockaddr_in);
        if((client_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
            DEBUG_PRINT("accept");
            continue;
        }

        printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));

        int numbytes;
        char cmd[CMDSIZE];

        while(1)
        {

            if((numbytes = recv(client_fd, cmd, CMDSIZE, 0)) == -1) {
                DEBUG_PRINT("recv");
                break;
            }

            if(numbytes == 0) {
                DEBUG_PRINT("connection lost");
                break;
            }

            if(handle_cmd(cmd) == -1)
            {
                DEBUG_PRINT("bad cmd");
                break;
            }

        }

        close(client_fd);
    }

    return 0;
}
