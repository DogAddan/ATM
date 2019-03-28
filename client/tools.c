#include "tools.h"

//清除输入输出缓冲区
void clear_stdin(void)
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;
}
//限制输入
char* get_str(char* str,size_t size)
{
	if(NULL == str) return str;

	clear_stdin();
	fgets(str,size,stdin);
	if(size-1 == strlen(str))
	{
		if('\n' == str[size-2])
				str[size-2] = '\0';
		else
			clear_stdin();
	}
	else
		str[strlen(str)-1] = '\0';

	return str;
}
//限制输入,上限删除
char* get_str_del(char* str,size_t size,size_t mode)
{
	if(NULL == str) return str;

	clear_stdin();
	for(int i=0;i<size;i++)
	{
		str[i] =getch();
		if('\n' == str[i])
		{
			if(0 == i)
			{
				i--;
				continue;
			}
			str[i] = '\0';
			printf("\n");
			break;
		}
		else if(127 == str[i])
		{
			str[i] = '\0';
			if(0 == i)
			{
				i--;
				continue;
			}
			printf("\b \b");
			i-=2;
			continue;
		}
		else
		{
			if(1 == mode)
			{
				printf("%c",str[i]);
			}
			else if(2 == mode)
			{
				printf("*");
			}
		}
		if(i == size-1)
		{
			printf("\b \b");
			i--;
		}
	}
	return str;
}
//判断字符串是否全为数字
bool is_all_num(char* str)
{
	for(int i=0;str[i];i++)
	{
		if(str[i]<'0'||str[i]>'9')return false;
	}
	return true;
}
//创建socket对象
int create_socket(int* sockfd)
{
	*sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
		perror("socket");
		return -1;
	}
	return 0;
}
//准备通信地址
struct sockaddr_in* init_socket(struct sockaddr_in* addr,int port,char* ip_addr)
{
	addr->sin_family = AF_INET;
	addr->sin_port = htons(port);
	addr->sin_addr.s_addr = inet_addr(ip_addr);
	return addr;
}
//连接
int connect_socket(int sockfd,struct sockaddr_in* addr)
{
	if(connect(sockfd,(struct sockaddr*)addr,sizeof(*addr)) < 0)
	{
		perror("connet");
		return -1;
	}
	return 0;
}
//按任意键退出
void rand_key_exit()
{
	printf("按任意键退出！");
	getch();
}
//进度条
void loading()
{
    for(int i=0;i<10;i++)
    {
        usleep(500000);
        printf("▇");
        fflush(stdout);
    }
}
