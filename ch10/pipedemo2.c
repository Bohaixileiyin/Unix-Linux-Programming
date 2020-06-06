#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define CHILD_MESS  "I want a cookie\n"
#define PAR_MESS    "testing..\n"
#define oops(m,x)       {perror(m);exit(x);}

int main(){
    int     pipefd[2];
    int     len;
    char    buf[BUFSIZ];
    int     read_len;

    if(pipe(pipefd) == -1)
        oops("cannot get a pipe",1);
    
    switch (fork())
    {
        case -1://创建子进程失败
            oops("cannot fork",2);
        
        case 0:
            len = strlen(CHILD_MESS);
            while (1)//子进程一直在这个死循环，每五秒向管道写入一次
            {
                if(write(pipefd[1],CHILD_MESS,len) != len)
                    oops("write",3);
                
                sleep(5);
            }

        default:
            len = strlen(PAR_MESS);
            while (1)//父进程一直在这个死循环，每秒写入并读取管道一次
            {
                if(write(pipefd[1],PAR_MESS,len) != len)
                    oops("write",4);

                sleep(1);
                read_len = read(pipefd[0],buf,BUFSIZ);
                if(read_len <= 0)
                    break;
                write(1,buf,read_len);
            }
    }
}