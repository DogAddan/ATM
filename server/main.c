#include "server.h"
#include "load.h"
#include "creacc.h"
#include "ulock.h"
#include "destory.h"

//捕获终止信号
void sigint(int signum)
{
	for(int i=0;i<5;i++)
	{
		close(fd[i]);
	}
	close(sockfd);
	puts("服务器关闭！");
	exit(0);
}

void* start(void* arg)
{
	Fd* mfd = arg;
	Fd fds = *mfd;
	printf("连接成功！\n");
	Msg msg = {};
	while(true)
	{
		if(recv(fds.fd,&msg,sizeof(Msg),0)<=0)break;
		switch(msg.type)
		{
			case CREACC :creacc(fds.fd,&msg.acc);break;
			case DESTORY:destory(fds.fd,&msg.acc);break;
			case LOAD   :load(fds.fd,&msg.acc);break;
			case ULOCK  :ulock(fds.fd,&msg.acc);break;
		}
	}
	printf("客户端退出！\n");
	//关闭线程
	pthread_exit(NULL);
}

int main()
{
	signal(SIGINT,sigint);
	//创建socket对象
	if(create_socket(&sockfd))return -1;
	//准备通信地址
	struct sockaddr_in addr = {};
	init_socket(&addr,3003,"127.0.0.1");
	//绑定socket对象与通信地址
	socklen_t len = sizeof(addr);
	if(bind(sockfd,(SockAddr*)&addr,len) < 0)
	{
		perror("bind");
		return -1;
	}
	//位置监听socket对象
	listen(sockfd,10);
	while(true)
	{
		//等待链接
		struct sockaddr_in from_addr;
		int accfd = accept(sockfd,(SockAddr*)&from_addr,&len);
		if(accfd < 0)
		{
			perror("accept");
			return -1;
		}
		//创建连接的信息
		Fd mfd = {};
		char ipaddr[20] = {};
		strcpy(ipaddr,inet_ntoa(from_addr.sin_addr));
		strcpy(mfd.addr,ipaddr);
		mfd.fd = accfd;
		//创建线程
		pthread_t pid;
		pthread_create(&pid,NULL,start,&mfd);
		//更新连接指示符数组
		for(int i=0;i<5;i++)
		{
			if(0 == fd[i])
			{
				fd[i] = accfd;
				break;
			}
		}
	}
}

