#include "draw.h"

//取款
void draw()
{
	Msg msg = {};
	char buf[1024] = {};
	//输入取款金额
	in_money(&msg.acc,"取款");
	//更新信息标志
	up_msg(&msg,DRAW,0);
	//数据发送至服务端
	send(sockfd,&msg,sizeof(Msg),0);
	//接受服务端数据
	recv(sockfd,&buf,sizeof(buf),0);
	//显示服务端数据
	puts(buf);
	//按任意键
	rand_key_exit();
}
