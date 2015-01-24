#include<stdlib.h>
#include<sys/types.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<pthread.h>

#define SERVER_PORT 5005

 struct filepage{
    unsigned int num;
    char buf[1024];
};

int serverfd;

struct sockaddr_in servaddr;
int data_len = 1024;

int main()
{
	int n;
        
        int i = 0;
	char recvBuf[1024]="\0";
	char sendBuf[1024]="\0";
        
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	serverfd = socket(PF_INET, SOCK_DGRAM, 0);

	if(bind(serverfd, (struct sockaddr*)&servaddr, sizeof(struct sockaddr_in))<0)
	{
		printf("bind fail\n");
		exit(1);
	}
 
	struct sockaddr_in clientAddr;
	int len = sizeof(clientAddr);
	//测试
        n = recvfrom(serverfd, recvBuf, data_len, 0, (struct sockaddr*)&clientAddr, &len);
	if(n < 0)
	{
		printf("recv fial");
	}
	printf("%s\n", recvBuf);
	
        FILE *fd = fopen("hello.txt", "r");
	struct filepage p;
         
	while(fgets(sendBuf, 1024, fd) > 0)
	{      
               memset(&p,0,sizeof(struct filepage));
	       p.num = i;
               strcpy(p.buf,sendBuf);
               char buffer[sizeof(struct filepage)];
               memset(buffer,0,sizeof(buffer));
               memcpy(buffer,&p,sizeof(struct filepage));
		
               sendto(serverfd,buffer,sizeof(buffer),0,(struct sockaddr*)&clientAddr, len);
             //  unsigned int t=0;
              // int tt=0; 
              // tt= recvfrom(serverfd,&t,sizeof(int),0,(struct sockaddr*)&clientAddr, &len);
              // printf("*****%d",t);
             //  if(t!=-1)
              // {   
              //     int temp = (int *)recvBuf;
              //     fseek(fd,temp,SEEK_SET);
              //     i = temp ;
             //  }
               i++; 
		
	}
       
return 0;
}


