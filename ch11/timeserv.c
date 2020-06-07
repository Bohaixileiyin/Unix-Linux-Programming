#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define PORTNUM 13000
#define HOSTLEN 256
#define oops(msg)   {perror(msg);exit(1);}

int main(int ac,char* av[]){
    struct  sockaddr_in saddr;
    struct  hostent *hp;
    char    hostname[HOSTLEN];
    int sock_id,sock_fd;
    FILE    *sock_fp;
    char    *ctime();
    time_t  thetime;
    /*
    第一步：向内核申请socket
    */
   sock_id = socket(PF_INET,SOCK_STREAM,0);
   if(sock_id == -1)
        oops("socket");
    /*
    第二步：将地址绑定到socket，地址就是host,port
    */
   bzero((void *)&saddr,sizeof(saddr));//清空结构体

   gethostname(hostname,HOSTLEN);
   hp = gethostbyname(hostname);
//打印出hostname    本地为qinjun-N15-17RD
   printf("%s\n",hostname);
//注意如果不加换行符就不会打印到窗口，因为主循环不会自动结束
/*
　　　　　　 原因：在标准IO函数中（printf)，是有缓冲区的,printf的缓冲区为行缓存，如果想要将缓冲区的内容送入内存，需要满足行缓存的条件：
　　　　　　　　1. 行缓存条件：好几个条件（任意满足一个条件即可）
　　　　　　　　　　(1) 输入输出函数有换行符 ‘\n’
　　　　　　　　　　(2) 程序自然结束（程序中无while（1）或_exit）
　　　　　　　　　　(3) 行满：1024个字节
　　　　　　　　　　(4) 关闭文件fclose
　　　　　　　　　　(5) 强制刷新缓存：fflush（stdout）
*/
   bcopy((void*)hp -> h_addr_list[0],(void*)&saddr.sin_addr,hp -> h_length);
   saddr.sin_port = htons(PORTNUM);
   saddr.sin_family = AF_INET;

   if(bind(sock_id,(struct sockaddr*)&saddr,sizeof(saddr)) != 0)
        oops("binds");
    /*
   第三步： 允许在socket上接受Qsize = 1的请求
    */
   if(listen(sock_id,1) != 0)
        oops("listen");
    /*
    主循环：accept(),write(),close()
    */
   while (1)
   {
       sock_fd = accept(sock_id,NULL,NULL);
       printf("Wow!got a call!\n");
       if(sock_fd == -1)
            oops("accept");
        
        sock_fp = fdopen(sock_fd,"w");
        if(sock_fp == NULL)
            oops("fdopen");

        thetime = time(NULL);

        fprintf(sock_fp,"The time here is ..");
        fprintf(sock_fp,"%s",ctime(&thetime));
        fclose(sock_fp);
   }
   
}