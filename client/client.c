#include "client.h"

//输入姓名
void in_name(Account* acc)
{
	char str[20] = {};
	printf("输入姓名:");
	get_str(str,20);
	strcpy(acc->name,str);
}

//输入身份证号
void in_id(Account* acc)
{
	char str[19] = {};
	printf("输入身份证:");
	get_str_del(str,19,1);
	strcpy(acc->id,str);
}

//输入帐号
void in_account(Account* acc)
{
	char str[9] = {};
	printf("输入帐号:");
	get_str_del(str,9,1);
	acc->account = atoi(str);
}

//输入密码
void in_password(Account* acc)
{
	char str[15] = {};
	printf("输入密码:");
	get_str_del(str,15,2);
	strcpy(acc->password,str);
}

//输入金额
void in_money(Account* acc,char* str)
{
	char in_str[20] = {};
	printf("输入%s金额:",str);
	get_str_del(in_str,20,1);
	acc->money = atof(in_str);
}

//更新信息
void up_msg(Msg* msg,long msgtyp,int flag)
{
	//更新消息类型
	msg->type = msgtyp;
	//消息标志
	msg->acc.flag = flag;
}
