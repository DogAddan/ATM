#include "draw.h"

void draw(int sockfd,int fd,Account* msg_acc)
{
	//读取账户文件信息
	Account file_acc = {};
	read_acc(fd,&file_acc,"draw");
	//进行取款
	if(modi_acc(sockfd,&file_acc,msg_acc,fd,DRAW,"draw"))return;
	//拼接返回信息字符串
	char str[1024] = {};
	sprintf(str,"取款成功!余额:%.2lf￥",file_acc.money);
	//返回信息
	msgback(sockfd,str);
}
