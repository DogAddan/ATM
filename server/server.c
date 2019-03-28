#include "server.h"

/*
	功能：打开账户文件，判断帐号
	参数：sockfd:socket对象ID；msg:消息结构体指针；fd:文件指示符指针；argv:进程名
	返回值：失败返回-1；成功返回0
*/
int is_account(int sockfd,Account* acc,int* fd,char* str)
{
	//打开用户文件
	char accfile[20] = {};
	printf("[%s]正在打开账户文件...\n",str);
	sprintf(accfile,"./dat/%d",acc->account);
	*fd = open(accfile,O_RDWR);
	//判断文件是否存在
	if(*fd < 0)
	{
		printf("[%s]打开失败,账号不存在!\n",str);
		//返回信息
		msgback(sockfd,"账号不存在!");
		return -1;
	}
	//读取账户信息
    read_acc(*fd,acc,str);
    //判断账号是否登录
    if (LOADING == acc->flag)
    {
        //关闭文件
		close(*fd);
        printf("[%s]账号已经登录!\n",str);
        //返回信息
		msgback(sockfd,"账号已经登录!");
        return -1;
    }
    //更新用户状态
    acc->flag = LOADING;
    write_acc(*fd,acc,str);
	printf("[%s]打开成功,账号存在!\n",str);
	return 0;
}

/*
	功能：读取账户信息
	参数：fd:文件指示符指针；
*/
void read_acc(int fd,Account* acc,char* str)
{
	printf("[%s]正在读取用户信息...\n",str);
	//文件移至首位
	lseek(fd,0,SEEK_SET);
	//读取文件
	read(fd,acc,sizeof(Account));
	printf("[%s]读取完毕!\n",str);
}

/*
	功能：写入更新账户信息
	参数：fd:文件指示符指针；
*/
void write_acc(int fd,Account* acc,char* str)
{
    printf("[%s]正在写入文件...\n",str);
	//文件移至首位
	lseek(fd,0,SEEK_SET);
	//更新文件信息
	write(fd,acc,sizeof(Account));
	printf("[%s]账户信息更新成功！\n",str);
}

/*
	功能：判断密码
	参数：sockfd:socket对象ID;acc:账户结构体的指针;msg_acc:消息中的用户结构体的指针;fd:文件指示符指针;
	返回值：失败返回-1；成功返回0
*/
int is_password(int sockfd,Account* file_acc,Account* msg_acc,int fd,char* str)
{
	//判断密码
	if(strcmp(msg_acc->password,file_acc->password))
	{
		//关闭文件
		close(fd);
		printf("[%s]密码错误!\n",str);
		//返回信息
		msgback(sockfd,"密码错误！");
		return -1;
	}
	printf("[%s]密码正确!\n",str);
	return 0;
}

/*
	功能：修改用户信息,更新账户数据
	参数：sockfd:socket对象ID;acc:账户结构体指针;fd:文件指示符指针;mode:修改模式
	返回值：失败返回-1；成功返回0
*/
int modi_acc(int sockfd,Account* file_acc,Account* msg_acc,int fd,int mode,char* str)
{
	if(DEPOSIT == mode)
	{
		//进行存款
		printf("[%s]正在存款...\n",str);
		file_acc->money += msg_acc->money;
		printf("[%s]存款成功!\n",str);
	}
	else if(DRAW == mode)
	{
		if(file_acc->money < msg_acc->money)
		{
			//返回信息
			msgback(sockfd,"余额不足!");
			return -1;
		}
		//取款操作
		file_acc->money -= msg_acc->money;
	}
	else if(MODI == mode)
	{
		//密码修改
		strcpy(file_acc->password,msg_acc->password);
	}
	else if(ULOCK == mode)
	{
		//初始化状态
		file_acc->flag = NORMAL;
		//初始化密码
		strcpy(file_acc->password,DEFAULTPASS);
		printf("[%s]%s\n",str,file_acc->password);
	}
	//写入文件
	write_acc(fd,file_acc,str);
	return 0;
}

/*
	功能：返回信息
	参数：sockfd:socket对象ID；str:返回消息字符串
*/
void msgback(int sockfd,char* backstr)
{
	char buf[1024] = {};
	strcpy(buf,backstr);
	//返回信息
	send(sockfd,&buf,strlen(buf)+1,0);
	puts("返回信息成功!");
}
