#include "modi.h"

void modi(int sockfd,int fd,Account* msg_acc)
{
	//读取账户文件信息
	Account file_acc = {};
	read_acc(fd,&file_acc,"modi");
	//进行修改密码
	modi_acc(sockfd,&file_acc,msg_acc,fd,MODI,"modi");
	//返回信息
	msgback(sockfd,"密码修改成功!");
}
