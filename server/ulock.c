#include "ulock.h"

/*
	功能：判断身份证号,读取账户信息
	参数：sockfd:socket对象ID;acc:账户结构体指针;fd:文件指示符指针;
	返回值：失败返回-1；成功返回0
*/
int is_id(int sockfd,Account* file_acc,Account* msg_acc,int fd,char* str)
{
	//判断身份证号
    printf("[%s]正在验证身份证号...\n",str);
	if(strcmp(file_acc->id,msg_acc->id))
	{
	    //关闭文件
		close(fd);
		printf("[%s]身份证号错误!\n",str);
		//返回信息
		msgback(sockfd,"身份证号错误!");
		return -1;
	}
    printf("[%s]身份证号正确!\n",str);
	return 0;
}

void ulock(int sockfd,Account* msg_acc)
{
	int fd = 0;
	Account file_acc = {};
	//判断帐号
	if(is_account(sockfd,msg_acc,&fd,"ulock"))return;
	//读取账户文件信息
	read_acc(fd,&file_acc,"ulock");
    //判断身份证号
    if(is_id(sockfd,&file_acc,msg_acc,fd,"ulock"))return;
    //进行解锁
    modi_acc(sockfd,&file_acc,msg_acc,fd,ULOCK,"ulock");
    //返回信息
    msgback(sockfd,"解锁成功!");
}
