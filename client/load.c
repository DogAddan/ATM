#include "load.h"

//登录
void load()
{
	Msg msg = {};
	char buf[1024] = {};
	//输入帐号
	in_account(&msg.acc);
	//输入密码
	in_password(&msg.acc);
	//更新信息
	up_msg(&msg,LOAD,0);
	//数据发送至服务端
	send(sockfd,&msg,sizeof(Msg),0);
	//接受服务端数据
	recv(sockfd,&buf,sizeof(buf),0);
	//显示服务端数据
	puts(buf);
	//按任意键继续
	getch();
	//登录功能选择
	chose_load(buf);
}

void cancellation()
{
	Msg msg = {};
	//更新信息
	up_msg(&msg,EXIT,0);
	//数据发送至服务端
	send(sockfd,&msg,sizeof(Msg),0);
}
