//
// Created by Filip on 5. 1. 2023.
//

#ifndef SEMESTRALNA_PRACA_UDSP_SOCKET_H
#define SEMESTRALNA_PRACA_UDSP_SOCKET_H


#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

typedef struct socket{
    int sockfd, newsockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
} SOCKET;

#endif //SEMESTRALNA_PRACA_UDSP_SOCKET_H
