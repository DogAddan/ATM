#include "creacc.h"

/*
	功能：创建ID，并保存
	参数：acc:账户结构体
	返回值：失败返回-1；成功返回0
*/
int create_accid(Account* acc)
{
	//打开ID储存文件
	puts("正在创建用户文件...");
	int fd = open("./dat/id.dat",O_RDWR|O_CREAT,0644);
	if(fd < 0)
	{
		perror("open");
		return -1;
	}
	//获取ID数量
	int count = 0;
	char buf[10] = {};
	while(read(fd,buf,sizeof(int)))
	{
		count++;
	}
	//创建账户ID
	puts("正在创建用户ID...");
	int account = 20190000+count;
	acc->account = account;
	printf("[creacc]%d\n",acc->account);
	puts("创建用户ID成功");
	//储存账户ID
	puts("正在储存用户ID...");
	lseek(fd,0,SEEK_END);
	write(fd,&acc->account,sizeof(int));
	puts("储存用户ID成功");
	//关闭文件
	close(fd);
	return 0;
}
/*
	功能：创建账户，保存账户信息
	参数：acc:账户结构体
	返回值：失败返回-1；成功返回0
*/
int save_account(Account* acc)
{
	//创建用户信息文件
	char str[20] = {};
	sprintf(str,"./dat/%d",acc->account);
	int fd = open(str,O_WRONLY|O_CREAT,0644);
	if(fd < 0)
	{
		perror("open");
		return -1;
	}
	//保存用户信息
	write(fd,acc,sizeof(Account));
	puts("储存用户信息成功");
	//关闭文件
	close(fd);
	return 0;
}

void creacc(int sockfd,Account* msg_acc)
{	
	//创建ID
	if(create_accid(msg_acc))return;
	//创建及保存账户
	if(save_account(msg_acc))return; 
	//将用户信息转化为字符串
	char str[1024] = {};
	sprintf(str,"账号:%d\n姓名:%s\n余额:%.2lf￥",msg_acc->account,msg_acc->name,msg_acc->money);
	//返回信息
	msgback(sockfd,str);	
}
