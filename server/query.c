#include "query.h"

void quacc(int sockfd,int fd)
{
	//读取账户文件信息
	Account file_acc = {};
	read_acc(fd,&file_acc,"query");
	//将用户信息转化为字符串
	char str[1024] = {};
	sprintf(str,"账号:%d\n姓名:%s\n余额:%.2lf￥",file_acc.account,file_acc.name,file_acc.money);
	//返回信息
	msgback(sockfd,str);
}
