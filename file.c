#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{   
    int i=0;
    int j=0;
    char a[1024]="\0";
    FILE *fp = fopen("hello.txt","wt+");
    while(i<1024*1024){
    for(j=0;j<1024;j++){
     a[j] = 'a';
     //printf("%d\n",a[j]);
     fputc(a[j],fp);
    }
    i++;
   
}
    fclose(fp);
return 0;
}
