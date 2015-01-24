#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include "transfile.h"
#include "conn.h"


#define file_name "1g.file"

int main()
{
    	struct sockaddr_in client_addr;   
    	int pthread_num = MAX_THREAD;
   	int file_size=1073741824;   
    	int listenfd = server_Init();
    	listen(listenfd,10);    
    	printf(" waiting for client connect \n");
        time_t t_start,t_end;
        t_start=time(NULL);
  
    	//  send file 
    	send_File(listenfd,file_size,pthread_num,file_name);
      
        close(listenfd);
        printf("send finish!\n");
        t_end=time(NULL);
        printf("共用时%.0fs\n",difftime(t_end,t_start)); 
	
    return 0;
}

