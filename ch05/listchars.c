#include <stdio.h>

int main(){
    int c,n = 0;
    while((c = getchar()) != 'Q')
        printf("char %3d is %c code %d\n",n++,c,c);
}
/*
输出如下：
hello
char   0 is h code 104
char   1 is e code 101
char   2 is l code 108
char   3 is l code 108
char   4 is o code 111
char   5 is 
 code 10
 说明了
    1.进程在用户输入回车以后才接受数据      因为在回车前显示器除了输入的字符没有任何输出
    2.进程将用户输入的回车（ASCII码13）看做换行（ASCII码10）处理
    3.进程发送换行符，显示器最终显示的其实是回车加换行

究其原因是因为不能简单的将显示器看作一个文件。它与后台程序之间隔了一个显示器驱动程序，就是这个驱动程序将用户输入的/r转为/n发给后台，又把后台输出的/n转为/r/n输出到显示器上
*/