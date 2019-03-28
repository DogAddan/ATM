#include "func_select.h"

//功能选择
void chose()
{
	switch(getch())
	{
		//按1进入开户功能
		case M_OPEN:create_account();break;
		//按2进入销户功能
		case M_DES:destory_account();break;
		//按3进入登录功能
		case M_LOAD:load();break;
		//按4进入解锁功能
		case M_ULOCK:ulock();break;
		//按q退出
		case 'q':exit(0);break;
	}
}

//登录功能
void chose_load(char* buf)
{
	if(strcmp("登录成功!",buf))return;
	while(1)
	{
		menu(2);
		switch(getch())
		{
			//按1进入存款功能
			case M_SAVE:deposit();break;
			//按2进入取款功能
			case M_DRAW:draw();break;
			//按3进入转账功能
			case M_TRAN:trans_account();break;
			//按4进入查询功能
			case M_QUERY:quacc();break;
			//按5进入修改密码功能
			case M_MODI:modi_pass();break;
			//按q退出
			case 'q':cancellation();return;
		}
	}
}
