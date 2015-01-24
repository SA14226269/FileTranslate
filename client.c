
#include<sys/types.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

#define SERVER_PORT 5005
 struct filepage{
    int num;
    char buf[1024];
};
int main()
{
	int clientfd;

	char sendBuf[1024] = "\0";
	char recvBuf[1024] = "\0";
        
	int n;
	struct sockaddr_in serveraddr;
	
	clientfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(clientfd < 0)
	{
		printf("error!\n");
	}
	bzero(&serveraddr, sizeof(struct sockaddr_in));
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(SERVER_PORT);
	printf("This is a client!\n");
	
	int len = sizeof(serveraddr);
      //测试
	n = sendto(clientfd, "Hello", 5, 0, (struct sockaddr *)&serveraddr, len);
	

	FILE *fd = fopen("hehe.txt", "a+");
	int i = 0;
	int size = 1024 *1024;
	struct filepage p;
	while(i < size)
        {       
                char rec[sizeof (struct filepage)];
                memset(rec,0,sizeof(rec));
		recvfrom(clientfd, rec, sizeof(rec), 0, (struct sockaddr *)&serveraddr, &len);
                memset(&p,0,sizeof(struct filepage));
                memcpy(&p,rec,sizeof(struct filepage));
                strcpy(recvBuf,p.buf);
                if(p.num != i)
               {
                  printf("error");
                   sendto(clientfd,&p.num,sizeof(unsigned int),0,(struct sockaddr*)&serveraddr,len);
              }
	     //   else
                fputs(p.buf, fd);
                
                printf("********%d\n",p.num);
		i++;
		//sendto(clientfd,"i",10,0,(Struct sockaddr*)&serveraddr,len);
	}
	fclose(fd);
	printf("finished\n");
        return 0;
}




