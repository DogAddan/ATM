#include "ulock.h"

//解锁
void ulock()
{	
	Msg msg = {};
	char buf[1024] = {};
	//输入帐号
	in_account(&msg.acc);
	//输入身份证号
	in_id(&msg.acc);
	//更新信息标志
	up_msg(&msg,ULOCK,0);
	//数据发送至服务端
	send(sockfd,&msg,sizeof(Msg),0);
	//接受服务端数据
	recv(sockfd,&buf,sizeof(buf),0);
	//显示服务端数据
	puts(buf);
	//按任意键
	rand_key_exit();
}
