/**************************************************************** 
    > Author: Deser
    > e-Mail: yongk202@163.com
    > Date: 2020-07-09 Thu 16:06:36
    > LastEditors: Deser
    > LastEditTime: 2020-07-10 Fri 01:31:31
 ****************************************************************/
/*************************************************************************
	> File Name: head.h
	> Author: suyelu 
	> Mail: suyelu@126.com
	> Created Time: Mon 06 Jul 2020 04:35:00 PM CST
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H
#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "color.h"
#include "common.h"
#include "datatype.h"
#include "store_score.h"
#include "sub_reactor.h"
#include "thread_pool.h"
#include "udp_client.h"
#include "udp_server.h"
#include "udp_epoll.h"
#endif
