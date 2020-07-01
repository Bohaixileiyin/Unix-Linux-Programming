#include "csapp.h"
//#include <linux/limits.h>
//fd2应该是4，在命令行下运行也确实是4，但是在vscode里运行变成了6，不明白为什么
//进入/proc/进程号/fd目录下发现打开了很多文件描述符，而命令行运行是只有需要用的描述符
//以后多学一些调试技巧、gdb应该能弄明白

//推测可能是vscode启动bash时打开了一些文件描述符，在执行程序时作为子进程继承了
int main(){
    int fd1,fd2;

    fd1 = Open("foo.txt", O_RDONLY, 0);
    printf("fd1 = %d\n", fd1);

    fd2 = Open("bar.txt", O_RDONLY, 0);
    printf("/proc/%d/fd/%d\n", getpid(), fd2);
    printf("fd2 = %d\n", fd2);
    Close(fd2);

    fd2 = Open("baz.txt", O_RDONLY, 0);
    printf("fd2 = %d\n", fd2);
    
}