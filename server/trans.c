#include "trans.h"

void trans(int sockfd,int fd,Account* msg_acc)
{
    int transed_fd = 0;
	Account transed_file_acc = {};
	Account file_acc = {};
	//判断帐号
	if(is_account(sockfd,msg_acc,&transed_fd,"trans"))return;
	//读取账户文件信息
	read_acc(fd,&file_acc,"trans");
    //进行取款
	if(modi_acc(sockfd,&file_acc,msg_acc,fd,DRAW,"trans"))return;
	//读取账户文件信息
	read_acc(transed_fd,&transed_file_acc,"trans");
	//进行存款
	modi_acc(sockfd,&transed_file_acc,msg_acc,transed_fd,DEPOSIT,"trans");
	//关闭文件
	close(transed_fd);
	//拼接返回信息字符串
	char str[1024] = {};
	sprintf(str,"转账成功!余额:%.2lf￥",file_acc.money);
	//返回信息
	msgback(sockfd,str);
}
