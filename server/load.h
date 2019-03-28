#ifndef LOAD_H
#define LOAD_H

#include "server.h"
#include "query.h"
#include "deposit.h"
#include "draw.h"
#include "trans.h"
#include "modi.h"

//登录
void load(int sockfd,Account* msg_acc);
#endif //LOAD_H
