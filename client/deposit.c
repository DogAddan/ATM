#include "deposit.h"

void deposit()
{
	Msg msg = {};
	char buf[1024] = {};
	//输入存款金额
	in_money(&msg.acc,"存款");
	//更新信息
	up_msg(&msg,DEPOSIT,0);
	//数据发送至服务端
	send(sockfd,&msg,sizeof(Msg),0);
	//接受服务端数据
	recv(sockfd,&buf,sizeof(buf),0);
	//显示服务端数据
	puts(buf);
	//按任意键
	rand_key_exit();
}
