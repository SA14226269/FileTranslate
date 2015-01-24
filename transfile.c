#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>


#include "transfile.h"
#include "conn.h"

 


//define Thread control struct
typedef struct ThreadArg   
{
        char *file_name;     //file name 
        int  fd;             //socket in new thread
        int  offset;         //file original address offset   
        int  size;           //size of file in this thread 
}threadArg;  
 
static void pthread_recv(threadArg *args);
static void pthread_send(threadArg *args);

/* prepare to send file */
void send_File(int sockfd,int file_size,int pthread_num,char *file_name)
{
        struct sockaddr_in client;
        int addrlen;
        struct ThreadArg targs[MAX_THREAD];
	pthread_t tids[MAX_THREAD];
        int blocksize;
        int i;
        
        addrlen = sizeof(struct sockaddr_in);
        printf("*********************\n");
        /* recieve client request */
        /* file size of each pthread */ 
        blocksize = file_size / pthread_num;        
	for(i=0;i<pthread_num;i++)
        {	
	        if(-1 == (targs[i].fd = accept(sockfd,(struct sockaddr*)&client,&addrlen)))
                {
                	printf(" Accept failed: creat new pthread%dfail\n",i);
                	exit(1);
        	}
         
        	/* initialize every pthread */
       		targs[i].file_name = file_name;
        	targs[i].offset = blocksize * i; 
        	targs[i].size = blocksize;  
		if(i == pthread_num-1)   /* the last pthread */
		{
            		targs[i].size += (file_size % pthread_num);
        	}
                printf("%d\n",targs[i].fd);
                printf("%d\n",targs[i].size);
        	/* send pthread */
        	pthread_create(&tids[i], NULL, (void *)pthread_send, (void *)&targs[i]);   
        }

        /* pthread close */
        for(i=0;i<pthread_num;i++)
        {   
        	pthread_join(tids[i],NULL);
        }
}
/* pthread_send file */
static void pthread_send(threadArg *targ)
{
        FILE *fp;
        int len;
        char sendBuf[MAXSIZE];
        char respBuf[MAXSIZE];
        printf("******%dstart\n",targ->fd);
        printf("filename:%s\n",targ->file_name);
        /* open  file */
	fp = fopen(targ->file_name,"rb+");
        if(-1 == fseek(fp,targ->offset,SEEK_SET))   /* find location of reading */
        {
                printf("pthread Error: fseek\n");
        	exit(1);
        }

        /* wait for client request start */
        while(recv(targ->fd,respBuf,MAXSIZE,0) != 4);
	
        while((len = fread(sendBuf,1,MAXSIZE,fp))>=0)   /* read 4096B to buf */
        {
                /* test whether this part has no data */
        	if(targ->size <=0)
       		{
            		break;
       		}
        
                /* send one part of file */
       		if(-1 == send(targ->fd,sendBuf,len,0))
       		{
           		printf("Send file faild.\n");
           		close(targ->fd);
           		exit(1);
        	}
                /* calculate remaind */
                targ->size -= len;
                /* wait for server request next */
                while(recv(targ->fd,respBuf,MAXSIZE,0) != 4);
    	}

        send(targ->fd,"finish this part",16,0); /* tell server this part send over" */

        fclose(fp);
        close(targ->fd);
        pthread_exit(NULL);
}


/* prepare to recv file */
void recv_File(int file_size,int pthread_num,char *file_name)
{
    	threadArg targs[MAX_THREAD];
    	pthread_t tids[MAX_THREAD];
    	int blocksize;
    	int i;
 
    	/* size of each pthread should write */ 
    	blocksize = file_size / pthread_num;
	
        for(i=0;i<pthread_num;i++)
    	{   
        	/* initialize information for pthread */
		targs[i].fd = client_Init();
		targs[i].file_name = file_name;
        	targs[i].offset = blocksize * i; 
        	targs[i].size = blocksize;
        	if(i == pthread_num-1)        /* the last pthread */
        	{
            		targs[i].size += (file_size % pthread_num);
        	}
                printf("%d\n",targs[i].size);
        	pthread_create(&tids[i], NULL, (void *)pthread_recv, (void *)&targs[i]);   
    	}       

    	/* close pthread */
    	for(i=0;i<pthread_num;i++)
    	{   
        	pthread_join(tids[i],NULL);   
    	}
}

/* pthread_recv file */

static void pthread_recv(threadArg *targ)
{
    	FILE *fp;
    	int len;
    	char recvBuf[MAXSIZE];
	
        printf("******%dstart\n",targ->fd);
    	/* open output file */
    	fp = fopen(targ->file_name,"wb+");
   	if(-1 == fseek(fp,targ->offset,SEEK_SET))   /* find location of writting */
        {
        	printf("pthread Error: fseek\n");
		exit(1);
    	}
    	send(targ->fd,"next",4,0);
    	while(1)
        {
        	while((len = recv(targ->fd,recvBuf,MAXSIZE,0))<=0);
               
        	if( 0 == strcmp(recvBuf,"finish this part"))					 /* if receive finish */
                {
			printf("get!\n");            		
			break;
		}
	        fwrite(recvBuf,1,len,fp);
                 
	        /* request for next */
		send(targ->fd,"next",4,0);
   	}
        printf("this recv pthread end\n");
    	fclose(fp);
    	close(targ->fd);
        pthread_exit(NULL);
}


