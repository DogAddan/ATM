#include "client.h"
#include "menu.h"
#include "func_select.h"

int main()
{
	//创建socket对象
	if(create_socket(&sockfd))return -1;
	//准备通信地址
	struct sockaddr_in addr = {};
	init_socket(&addr,3003,"127.0.0.1");
	//连接
	if(connect_socket(sockfd,&addr))return -1;
	
	while(1)
	{
		//显示菜单
		menu(1);
		//功能选择
		chose();
	}
}
