#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
/*
方法一：close then open来进行文件重定向
理解需要以下知识：
    stdin文件描述符是0
    stdout文件描述符是1
    stderr文件描述符是2
    Unix假设文件描述符已经被打开，可以分别进行读、写和写操作
    通常通过shell命令行运行系统工具时，stdin、stdout和stderr连接在终端上
    最低可用文件描述符原则：当打开文件时，为此文件安排的描述符总是此数组中最低可用位置的索引


因此，如果想要重定位标准输入到文件，只需先关闭0，在打开文件，此时该文件的描述符就是0，也就是文件
方法二：open,close,dup,close        dup(fd)返回一个新的文件描述符连接与fd相同的文件
方法三：open,dup2,close
                    dup uses the lowest-numbered unused descriptor for the new descriptor.
                    dup2 makes newfd be the copy of oldfd, closing newfd first if necessary.  在此例中newfd是0也就是stdin,oldfd是文件   相当于close(0)并dup(fd)，在0已经被用于与如终端连接时，会先关闭

在shell中执行程序步骤实际是fork,exec,wait
    因此在shell中用命令重定向，实际上是在fork之后到exec之前这段时间将子进程的IO重定向，虽然子进程的代码数据都被所要执行的程序替代，但是文件描述符会保留下来，打开的文件既不是程序也不是
    代码，它们属于进程的属性。
    简单来说就是文件描述符通过exec调用传递，且不会被改变，shell使用进程通过产生子进程和子进程调用exec之间的时间间隔来重定向标准输入输出到文件。
*/
int main(){
    int fd;
    char line[100];

    fgets(line,100,stdin);printf("%s",line);

    close(0);
    fd = open("/etc/passwd",O_RDONLY);
    if(fd != 0){
        fprintf(stderr,"Could not open data as fd 0\n");
    }

    fgets(line,100,stdin);printf("%s",line);
}