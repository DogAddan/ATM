#include "deposit.h"

void deposit(int sockfd,int fd,Account* msg_acc)
{
	//读取账户文件信息
	Account file_acc = {};
	read_acc(fd,&file_acc,"deposit");
	//进行存款
	modi_acc(sockfd,&file_acc,msg_acc,fd,DEPOSIT,"deposit");
	//拼接返回信息字符串
	char str[1024] = {};
	sprintf(str,"存款成功!余额:%.2lf￥",file_acc.money);
	//返回信息
	msgback(sockfd,str);
}
