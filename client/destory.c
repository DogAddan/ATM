#include "destory.h"

//销户
void destory_account()
{
	Msg msg = {};
	char buf[1024] = {};
	//输入帐号
	in_account(&msg.acc);
	//输入密码
	in_password(&msg.acc);
	//更新信息标志
	up_msg(&msg,DESTORY,0);
	//数据发送至服务端
	send(sockfd,&msg,sizeof(Msg),0);
	//接受服务端数据
	recv(sockfd,&buf,sizeof(buf),0);
	//显示服务端数据
	puts(buf);
	//按任意键
	rand_key_exit();
}
