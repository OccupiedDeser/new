/**************************************************************** 
    > Author: Deser
    > e-Mail: yongk202@163.com
    > Date: 2020-07-09 Thu 21:43:10
    > LastEditors: Deser
    > LastEditTime: 2020-07-10 Fri 01:30:40
 ****************************************************************/
#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

struct task_queue{
    int sum;
    int epollfd;
    struct User **team;
    int head, tail;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

void task_queue_init(struct task_queue *taskQueue, int sum, int epollfd);
void task_queue_push(struct task_queue *taskQueue, struct User* user);
struct User* task_queue_pop(struct task_queue* taskQueue);
void * thread_run(void* arg);
#endif