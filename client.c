
#include<sys/types.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdio.h>
#include<time.h>

#define SERVER_PORT 5000
 
int main()
{       
        time_t t_start,t_end;
        int sockfd;
        struct sockaddr_in server_addr;             
        sockfd = socket(AF_INET,SOCK_STREAM,0);
		char sendBuf[1024] = "\0";
		char recvBuf[1024] = "\0";
        bzero(&server_addr,sizeof(struct sockaddr_in));
        server_addr.sin_family=AF_INET;
        server_addr.sin_port = htons(SERVER_PORT);
        inet_aton("127.0.0.1",&server_addr.sin_addr);

 
    
        if(-1 == connect(sockfd,(struct sockaddr *)&server_addr, sizeof(struct sockaddr)))
		{
				printf("error connect!");
               // exit(1);  
		}
	
		recv(sockfd,recvBuf,10,0);
        printf("%c%c%c%c\n",recvBuf[0],recvBuf[1],recvBuf[2],recvBuf[3]);
        
		FILE *fd = fopen("hehe.file", "wb+");
        t_start=time(NULL);
	
        while(1)
		{
       
				if(-1 == recv(sockfd,recvBuf,1024,0))
                break;
				fwrite(recvBuf,1,1024,fd);
				//printf("ooo\n");
				send(sockfd,"ok",2,0);
          
        }
        t_end=time(NULL);
        printf("共用时%.0fs\n",difftime(t_end,t_start));
        fclose(fd);
        
        close(sockfd);
        return 0;
}




