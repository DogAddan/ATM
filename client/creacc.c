#include "creacc.h"

//开户
void create_account()
{
	Msg msg = {};
	char buf[1024] = {};
	//输入姓名
	in_name(&msg.acc);
	//输入身份证号
	in_id(&msg.acc);
	//输入密码
	in_password(&msg.acc);
	//输入初始的开户金额
	in_money(&msg.acc,"开户");
	//更新信息标志
	up_msg(&msg,CREACC,NORMAL);
	//数据发送至服务端
	send(sockfd,&msg,sizeof(Msg),0);
	//接受服务端数据
	recv(sockfd,&buf,sizeof(buf),0);
	//显示服务端数据
	puts(buf);
	//按任意键
	rand_key_exit();
}
