//
// Created by Filip on 29. 12. 2022.
//
#include "../header_file/socket_definitions.h"


int create_connection(SOCKET * soket, int network_port) {

    bzero((char*)&soket->serv_addr, sizeof(soket->serv_addr));
    soket->serv_addr.sin_family = AF_INET;
    soket->serv_addr.sin_addr.s_addr = INADDR_ANY;
    soket->serv_addr.sin_port = htons(network_port);

    soket->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (soket->sockfd < 0)
    {
        perror("[-]Error creating socket");
        return 1;
    }

    if (bind(soket->sockfd, (struct sockaddr*)&soket->serv_addr, sizeof(soket->serv_addr)) < 0)
    {
        perror("[-]Error binding socket address");
        return 2;
    }

    listen(soket->sockfd, 5);
    soket->cli_len = sizeof(soket->cli_addr);
    printf("Socket opened on port: %d \n", network_port);
    return 0;
}
