#include "trans.h"

//转账
void trans_account()
{
	Msg msg = {};
	char buf[1024] = {};
	//输入帐号
	in_account(&msg.acc);
	//输入转账金额
	in_money(&msg.acc,"转账");
	//更新信息标志
	up_msg(&msg,TRANS,0);
	//数据发送至服务端
	send(sockfd,&msg,sizeof(Msg),0);
	//接受服务端数据
	recv(sockfd,&buf,sizeof(buf),0);
	//显示服务端数据
	puts(buf);
	//按任意键
	rand_key_exit();
}

