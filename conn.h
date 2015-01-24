#ifndef CONN_H
#define CONN_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* create a socket connect : server point */
int server_Init(void);

/* create a socket connect : client point */
int client_Init(void);


#endif
