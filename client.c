#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h> 
#include <time.h>
#include <netinet/in.h>
#include <unistd.h> 

#include "transfile.h"
#include "conn.h"

int main()
{        
	int pthread_num = MAX_THREAD;
	char file_name[]="hehe.file";				//file to recv
	int file_size=1073741824;
	//int fd = client_Init();
        time_t t_start,t_end;
        t_start=time(NULL);
        recv_File(file_size,pthread_num,file_name);		 // recv file 
        printf("finish\n");
	t_end=time(NULL);
        printf("共用时%.0fs\n",difftime(t_end,t_start));
        //close(fd);
        
        return 0;
}


