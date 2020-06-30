#include "csapp.h"

int main(){
    int fd1,fd2;

    fd1 = Open("foo.txt", O_RDONLY, 0);
    Close(fd1);
    fd2 = Open("baz.txt", O_RDONLY, 0);
    printf("fd2 = %d\n", fd2);
    exit(0);
}
//cc ex10.1.c csapp.c -o ex10.1 -lpthread编译csapp.c时貌似有多线程函数，因此要加-lpthread
//./ex10.1
//fd2 = 3