#include <stdio.h>
#include <signal.h>
#include <unistd.h>
//捕获信号
//对信号的三种处理方式：默认、忽略、捕获
int main(){
    void    f(int);
    int     i;
    signal(SIGINT,f);
    for (int i = 0; i < 5; i++)
    {
        printf("hello\n");
        sleep(1);
    }
}
void    f(int   signum){
    printf("OUCH! \n");
}