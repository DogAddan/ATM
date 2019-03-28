#ifndef CLIENT_H
#define CLIENT_H

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
#define M_OPEN 	'1'
#define M_DES  	'2'
#define M_LOAD 	'3'
#define M_ULOCK '4'
#define M_SAVE 	'1'
#define M_DRAW  '2'
#define M_TRAN 	'3'
#define M_QUERY '4'
#define M_MODI	'5'

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



//输入姓名
void in_name(Account* acc);
//输入身份证号
void in_id(Account* acc);
//输入帐号
void in_account(Account* acc);
//输入密码
void in_password(Account* acc);
//输入金额
void in_money(Account* acc,char* str);
//更新信息
void up_msg(Msg* msg,long msgtyp,int flag);

#endif //CLIENT_H
