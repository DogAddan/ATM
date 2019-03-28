#include "load.h"

/*
	功能：判断密码,读取账户信息，记录密码错误次数(登录用)
	参数：sockfd:socket对象ID;msg:消息结构体指针;acc:账户结构体指针;fd:文件指示符指针;
	返回值：失败返回-1；成功返回0
*/
int is_password_load(int sockfd,Account* file_acc,Account* msg_acc,int fd,char* str)
{
	//判断是否锁定
	if(LOCK == file_acc->flag)
	{
		printf("[%s]账户锁定\n",str);
		//返回信息
		msgback(sockfd,"账户已被锁定,请自行解锁!");
		//关闭文件
		close(fd);
		return -1;
	}
	//判断密码
	if(strcmp(msg_acc->password,file_acc->password))
	{
		printf("[%s]密码错误\n",str);
		file_acc->flag++;
		int num = LOCK-file_acc->flag-1;
		//文件移至首位
		lseek(fd,0,SEEK_SET);
		//更新文件信息
		write(fd,file_acc,sizeof(Account));
		//拼接返回信息字符串
		char backstr[1024] = {};
		sprintf(backstr,"密码错误，还能输错%d次！",num);
		if(0 == num)strcpy(backstr,"账户已被锁定,请自行解锁!");
		//返回信息
		msgback(sockfd,backstr);
		//关闭文件
		close(fd);
		return -1;
	}
	return 0;
}

//登录
void load(int sockfd,Account* msg_acc)
{
	int fd = 0;
	Account file_acc = {};
	//判断帐号
	if(is_account(sockfd,msg_acc,&fd,"load"))return;
	//读取账户文件信息
	read_acc(fd,&file_acc,"load");
	//判断密码
	if(is_password_load(sockfd,&file_acc,msg_acc,fd,"load"))return;
	//返回信息
	msgback(sockfd,"登录成功!");
	//登录功能选择
	while(true)
	{
		Msg msg = {};
		if(recv(sockfd,&msg,sizeof(Msg),0)<=0)break;
		if(EXIT == msg.type)break;
		switch(msg.type)
		{
			case DEPOSIT:deposit(sockfd,fd,&msg.acc);break;
			case DRAW   :draw(sockfd,fd,&msg.acc);break;
			case QUERY  :quacc(sockfd,fd);break;
			case TRANS  :trans(sockfd,fd,&msg.acc);break;
			case MODI   :modi(sockfd,fd,&msg.acc);break;
		}
	}
	//更新用户状态
    file_acc.flag = NORMAL;
    write_acc(fd,&file_acc,"load");
	//显示用户退出信息
	printf("账户ID:%d退出!\n",file_acc.account);
	//关闭文件
	close(fd);
}
