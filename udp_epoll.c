#include "head.h"

int udp_connect(struct sockaddr_in* client)
{
    int sockfd;
    if ((sockfd = socket_udp()) < 0) {
        perror("socket_udp");
        return -1;
    }

    if (connect(sockfd, (struct sockaddr*)client, sizeof(struct sockaddr)) < 0) {
        perror("connect()");
        return -1;
    }
    return sockfd;
}

int udp_aaccept(int fd, struct User* user)
{
    int new_fd, ret;
    struct sockaddr_in client;
    struct LogRequest request;
    struct LogResponse response;
    bzero(&request, sizeof(request));
    bzero(&response, sizeof(response));
    socklen_t len = sizeof(client);

    ret = recvfrom(fd, (void*)&request, sizeof(request), 0, (struct sockaddr*)&client, &len);
    if (ret != sizeof(request)) {
        response.type = 1;
        strcpy(response.msg, "Login failed with Data errors!");
        sendto(fd, (void*)&response, sizeof(response), 0, (struct sockaddr*)&client, len);
        return -1;
    }

    // if (check_online(&request)) {
    //     response.type = 1;
    //     strcpy(response.msg, "You're already login!");
    //     sendto(fd, (void*)&response, sizeof(response), 0, (struct sockaddr*)&client, len);
    //     return -1;
    // }

    response.type = 0;
    strcpy(response.msg, "Login Success. Enjoy yourself");
    sendto(fd, (void*)&response, sizeof(response), 0, (struct sockaddr*)&client, len);

    if (request.team) {
        DBG(GREEN "Info" NONE " : " BLUE "%s longin on %s:%d <%s>\n", request.name, inet_ntoa(client.sin_addr), ntohs(client.sin_port), request.msg);
    } else {
        DBG(GREEN "Info" NONE " : " RED "%s longin on %s:%d <%s>\n", request.name, inet_ntoa(client.sin_addr), ntohs(client.sin_port), request.msg);
    }

    strcpy(user->name, request.name);
    user->team = request.team;
    new_fd = udp_connect(&client);
    user->fd = new_fd;
    return new_fd;
}