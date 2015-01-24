#include<stdlib.h>
#include<sys/types.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<pthread.h>
#include<stdio.h>
#include<time.h>

#define SERVER_PORT 5000





int main()
{
        
		time_t t_start,t_end;
		int sockfd,new_fd;
        int sin_size;
        struct sockaddr_in server_addr;
        sockfd = socket(AF_INET,SOCK_STREAM,0);
		char sendBuf[1024] = "\0";
		char recvBuf[1024] = "\0";
        bzero(&server_addr,sizeof(struct sockaddr_in));
        server_addr.sin_family=AF_INET;
        server_addr.sin_port = htons(SERVER_PORT);
        inet_aton("127.0.0.1",&server_addr.sin_addr);



        if(-1 == bind(sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr)))
		{
                printf("bind error,exit");
                exit(1);
		}
        listen(sockfd,10);
        struct sockaddr_in clientaddr;
        sin_size=sizeof(struct sockaddr_in);   
		new_fd = accept(sockfd,(struct sockaddr *)&clientaddr,&sin_size);
		if(new_fd == -1)
		{
                printf("connect error,exit");
				exit(1);
        }
		send(new_fd,"haha",4,0);
        
        
     
	
        FILE *fd = fopen("1g_file.file", "rb+");
	
        t_start=time(NULL);
		while(fread(sendBuf, 1,1024, fd) > 0)
		{      
				send(new_fd,sendBuf,1024,0);
				recv(new_fd,recvBuf,1024,0);
              //printf("%c%c\n",recvBuf[0],recvBuf[1]);	
		}
        t_end=time(NULL);
        printf("共用时%.0fs\n",difftime(t_end,t_start));
        fclose(fd); 
        printf("send over");
        
        close(sockfd);
        return 0;
}



