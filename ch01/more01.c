/* more01.c -version 0.1 of more
 * read and print 24lines then pause for a few special commands
 */
#include <stdlib.h>
#include <stdio.h>
#define PAGELEN 24//每页24行
#define LINELEN 512
void do_more(FILE *);
int see_more();
int main(int ac,char *av[]){//ac是命令行参数个数，av[i]存放第i个命令行参数字符串的首地址
FILE *fp;
if(ac == 1){
	do_more(stdin);//如果没有参数，就从标准输入读取数据
	}
else
	while(--ac)
		printf("第 %d 个参数是 %s\n",ac,av[ac]);
		if((fp = fopen(* ++av,"r")) != NULL){//av是av数组的首地址，*av相当于取出第一个参数(字符串)的首地址，当做字符串传给fopen
																				//数组名与数组的首地址是等价的(因为大多数表达式中会发生隐式类型转换，见C++primer P143)
																				//字符串字面值(如"hello"")实际上是由常量字符组成的数组，也就是说它的返回值为首元素地址
		do_more(fp);
		fclose(fp);}
		else
			exit(1);
return 0;
}
void do_more(FILE *fp)
/*
 * read PAGELEN lines,then call see_more() for further instruction
 */
{
char line[LINELEN];
int num_of_lines = 0;
int see_more(),reply;
while(fgets(line,LINELEN,fp)){
	if(num_of_lines == PAGELEN){
		reply = see_more();//获得需要继续输出几行
		if(reply == 0)
			break;
		num_of_lines -= reply;
	}
	if(fputs(line,stdout) == EOF)//输出一行内容
		exit(1);
	num_of_lines++;

}
}
int see_more()
/*
 * print message,wait for response,return # of lines to advance
 * q means no,space means yes,CR means one line
 */
{
int c;
printf("\033[7m more? \033[m");
while((c=getchar()) != EOF){
	if(c == 'q')
		return 0;
	if(c == ' ')
		return PAGELEN;
	if(c == '\n')
		return 1;
}
return 0;
}



