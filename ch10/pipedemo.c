#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int len,i,apipe[2];
    char buf[BUFSIZ];
//创建管道
    if(pipe(apipe) == -1){
        perror("could not make pipe");
        exit(1);
    }
    printf("Got a pipe! It is file descriptors: { %d    %d}\n",apipe[0],apipe[1]);//apipe[0]为读管道的文件描述符，apipe[1]为写管道的文件描述符，也就是说0是管道的输出，1是管道的输入

    while (fgets(buf,BUFSIZ,stdin))//从stdin读取到buf
    {
        len = strlen(buf);
        if(write(apipe[1],buf,len) != len){//将buf写入管道
            perror("writing to pipe");
            break;
        }

        for(i = 0;i < len;++i)//覆盖buf中读入的值
            buf[i] = 'X';

        len = read(apipe[0],buf,BUFSIZ);//从管道中读到buf
        if(len == -1){
            perror("reading from pipe");
            break;
        }

        if(write(1,buf,len) != len){//将buf输出到stdout
            perror("writing to stdout");
            break;
        }
    }
}