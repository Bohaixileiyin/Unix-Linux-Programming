#include <stdio.h>
#include <ctype.h>
int main(){
    int c;
    while((c = getchar()) != EOF){
        if(c == 'z')
            c = 'a';
        else if(islower(c))
            c++;
        putchar(c);
    }
}
//stty -icanon;./rorate                            关闭规范模式没有缓冲直接送给程序
//stty -icanon -echo;./rorate               关闭回显模式输入的字符不会打印在终端上
//stty icanon echo                                  重新开启规范模式和回显模式