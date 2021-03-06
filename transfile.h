#ifndef TRANSFILE_H
#define TRANSFILE_H
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define MAX_THREAD 1
#define MAXSIZE 4096
/* send file */
void send_File(int listenfd,int file_size,int pthread_num,char *file_name);

/* recv file */
void recv_File(int file_size,int pthread_num,char *file_name);

#endif
