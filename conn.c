#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "conn.h"

#define PORT 5000
#define IPADDRESS "127.0.0.1"

/* create a socket connect in server */
// get socket define 
int server_Init(void)
{
        int sockfd;                  
        struct sockaddr_in serveraddr;
        int opt = SO_REUSEADDR;
    
        if(-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
        {
                printf("socket define error.\n");
        	exit(1);
        } 
	
    
        setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR, &opt, sizeof(opt));
	
        bzero(&serveraddr,sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serveraddr.sin_port = htons(PORT);
	
        if(-1 == bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)))
        {
        	printf("bind error!\n");
        	exit(1);
        }

        return sockfd;
}


/* create a socket connect in client */
//get client point socket define
int client_Init(void)
{
        struct sockaddr_in server;
        int sockfd;

        if(-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
        {
        	printf("Create socket error.\n");
        	exit(1);
        }

    
        bzero(&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);
        if(-1 == (inet_aton(IPADDRESS,&server.sin_addr)))
        {
        	printf("set server address failed.\n");
        	close(sockfd);
        	exit(1);
        }
    
        if(-1 == (connect(sockfd,(struct sockaddr *)&server,sizeof(server))))
        {
        	printf("Connect failed.\n");
        	close(sockfd);
        	exit(1);
        }

        return sockfd;
}
