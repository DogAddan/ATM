#include "menu.h"

//显示菜单
void menu(int mode)
{
	system("clear");
	if(1 == mode)
	{
		puts("[1]开户[2]销户");
		puts("[3]登录[4]解锁");
	}
	else if(2 == mode)
	{
		puts("[1]存款[2]取款");
		puts("[3]转账[4]查询");
		puts("[5]修改密码");
	}
	puts("--------------");
}
