#ifndef TOOLS_H
#define TOOLS_H

#include "client.h"

//清除输入输出缓冲区
void clear_stdin(void);
//限制输入
char* get_str(char* str,size_t size);
//限制输入,上限删除
char* get_str_del(char* str,size_t size,size_t mode);
//判断字符串是否全为数字
bool is_all_num(char* str);
//创建socket对象
int create_socket(int* sockfd);
//准备通信地址
struct sockaddr_in* init_socket(struct sockaddr_in* addr,int port,char* ip_addr);
//连接
int connect_socket(int sockfd,struct sockaddr_in* addr);
//按任意键退出
void rand_key_exit(void);
//
void loading();

#endif //TOOLS_H
