#include "destory.h"

/*
	功能：销户
	参数：sockfd:socket对象ID;acc:账户结构体指针;
	返回值：失败返回-1；成功返回0
*/
int des_account(int sockfd,Account* acc,char* str)
{
	//判断账户余额是否为0
	if(acc->money > 0)
	{
		printf("[%s]账户内仍有余额，无法销户\n",str);
		//返回信息
		msgback(sockfd,"账户内仍有余额，无法销户!");
		return -1;
	}
	//删除账户文件
    printf("[%s]正在删除账户信息文件...\n",str);
	char file_path[20] = {};
	sprintf(file_path,"./dat/%d",acc->account);
	unlink(file_path);
    printf("[%s]删除账户信息文件成功!\n",str);
	return 0;
}

void destory(int sockfd,Account* msg_acc)
{
	int fd = 0;
	Account file_acc = {};
	//判断帐号
	if(is_account(sockfd,msg_acc,&fd,"destory"))return;
	//读取账户文件信息
	read_acc(fd,&file_acc,"destory");
    //判断密码
    if(is_password(sockfd,&file_acc,msg_acc,fd,"destory"))return;
    //销户
    if(des_account(sockfd,&file_acc,"destory"))return;
    //返回信息
    msgback(sockfd,"销户成功!");
}
