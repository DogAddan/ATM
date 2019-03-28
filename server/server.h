#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getch.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>
#include <wait.h>
#include <unistd.h>
#include "tools.h"

//默认密码
#define DEFAULTPASS "000000"

typedef struct sockaddr SockAddr;
int fd[5];
int sockfd;

enum
{
	//错误类型
	ERR_ACC,ERR_PASS,ERR_ID,ERR_MONEY,ERR_HAVEMONEY,
	//用户状态
	NORMAL,ONE_LOCK,TWO_LOCK,LOCK,LOADING,
	//功能类型
	CREACC,DESTORY,LOAD,ULOCK,DEPOSIT,DRAW,QUERY,TRANS,MODI,EXIT,
};

typedef struct Fd
{
	char addr[20];
	int fd;
	int index;
}Fd;

typedef struct Account
{
	//账号
	int account;
	//姓名
	char name[20];
	//身份证号
	char id[19];
	//密码
	char password[15];
	//金额
	double money;
	//状态标志
	int flag;
}Account;

typedef struct Msg
{
	//消息类型
	long type;
	//账户信息
	Account acc;
}Msg;

//打开账户文件，判断帐号
int is_account(int sockfd,Account* acc,int* fd,char* str);
//读取账户信息
void read_acc(int fd,Account* acc,char* str);
//写入更新账户信息
void write_acc(int fd,Account* acc,char* str);
//判断密码
int is_password(int sockfd,Account* file_acc,Account* msg_acc,int fd,char* str);
//修改账户信息
int modi_acc(int sockfd,Account* file_acc,Account* msg_acc,int fd,int mode,char* str);
//返回信息
void msgback(int sockfd,char* str);

#endif //SERVER_H
