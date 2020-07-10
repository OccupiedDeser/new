/**************************************************************** 
    > Author: Deser
    > e-Mail: yongk202@163.com
    > Date: 2020-07-10 Fri 00:51:25
    > LastEditors: Deser
    > LastEditTime: 2020-07-10 Fri 01:45:13
 ****************************************************************/
#include "head.h"

int server_port = 0;
char server_ip[20] = { 0 };
int team = -1;
char name[20] = { 0 };
char log_msg[512] = { 0 };
char buff[512] = "12345abcd";
char* conf = "./football.conf";
int sockfd = -1;

int main(int argc, char** argv)
{
    int opt;
    struct LogRequest request; //HERE
    struct LogResponse response; //HERE
    memset(&request, 0, sizeof(request));
    memset(&response, 0, sizeof(response));
    while ((opt = getopt(argc, argv, "h:p:t:m:n:")) != -1) {
        switch (opt) {
        case 't':
            request.team = atoi(optarg); //HERE
            break;
        case 'h':
            strcpy(server_ip, optarg);
            break;
        case 'p':
            server_port = atoi(optarg);
            break;
        case 'm':
            strcpy(request.msg, optarg); //HERE
            break;
        case 'n':
            strcpy(request.name, optarg); //HERE
            break;
        default:
            fprintf(stderr, "Usage : %s [-hptmn]!\n", argv[0]);
            exit(1);
        }
    }

    if (!server_port)
        server_port = atoi(get_conf_value(conf, "SERVERPORT"));
    if (!request.team)
        request.team = atoi(get_conf_value(conf, "TEAM")); //HERE
    if (!strlen(server_ip))
        strcpy(server_ip, get_conf_value(conf, "SERVERIP"));
    if (!strlen(request.name))
        strcpy(request.name, get_conf_value(conf, "NAME")); //HERE
    if (!strlen(request.msg))
        strcpy(request.msg, get_conf_value(conf, "LOGMSG")); //HERE

    DBG("<" GREEN "Conf Show" NONE "> : server_ip = %s, port = %d, team = %s, name = %s\n%s",
        server_ip, server_port, request.team ? "BLUE" : "RED", request.name, request.msg);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    server.sin_addr.s_addr = inet_addr(server_ip);

    socklen_t len = sizeof(server);

    if ((sockfd = socket_udp()) < 0) {
        perror("socket_udp()");
        exit(1);
    }

    sendto(sockfd, (void*)&request, sizeof(request), 0, (struct sockaddr*)&server, len); //HERE
    /**********************************以下为需要实现的内容************************/
    //上一行已经发送request，接下来要等待response
    //使用select实现，等待5秒，如果5秒内还没收到数据，则判定为服务端不在线，退出程序
    /*
    	实现细节（伪代码）
    	fd_set rfds;
    	fd_ZERO rfds；
    	FD_SET sockfd  TO  rfds
    	struct timeval tv
    	tv.tv_sec 为5
    	tv.tv_usec = 0
    	
    	select blocked，判断是否有文件就绪
    	
    	判断返回值为0， 没有就绪的，就退出，
    	返回这为非零，说明sockfd一定就绪，接受信息到response
    	判断response大小是否合法，type是否为1，如果不合法，或type为1，则服务端拒绝接入，答应response.msg
    	
    	*/
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(sockfd, &rfds);
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    //调用connect连接到服务端，相当于建立“连接”

    //发送一信息给服务端，查看从反应堆的，do_work是否返回

    int ret = select(sockfd + 1, &rfds, NULL, NULL, &tv);

    if (ret < 0) {
        perror("select()");
        exit(1);
    }
    if (ret == 0) {
        DBG("<" BLUE "Select Return" NONE "> : Time Out!.\n");
        perror("select()");
        exit(1);
    }

    DBG("<" BLUE "Select Return" NONE "> : select return success %d fds.\n", ret);
    int nrecv = recvfrom(sockfd, (void*)&response, sizeof(response), 0, (struct sockaddr*)&server, &len);
    if (nrecv >= 512 || response.type) {
        fprintf(stderr, "recvfrom()");
    }
    ret = connect(sockfd, (struct sockaddr*)&server, len);
    if (ret < 0) {
        perror("connect()");
    }
    DBG("<" L_BLUE "Connect" NONE "> : Connect Success.\n");

    send(sockfd, buff, strlen(buff), 0);
    bzero(buff, sizeof(buff));
    while (recv(sockfd, buff, sizeof(buff), 0) > 0) {
        DBG("<" L_RED "Server Info" NONE "> : %s\b", buff);
    }

    return 0;
}