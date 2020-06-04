#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFERSIZE 4096

int main(int ac,char *av[]){
    if(ac != 3){
        printf("参数有误");
        return 0;
    }
    int fs = open(*++av,O_RDONLY);
    //long sizet = lseek(fs,0,SEEK_END);

    int fd = creat(*++av,0644);
    int wchars;
    char buf[BUFFERSIZE];
    while((wchars = read(fs,buf,BUFFERSIZE)) > 0)
        if(write(fd,buf,wchars) != wchars)
            {
                printf("error");
                return 0;
            }
    return 0;
}