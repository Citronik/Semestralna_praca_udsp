
//
// Created by Filip on 29. 12. 2022.
//
#include "../header_file/socket_definitions.h"

int client_socket_started(SOCKET * soket, char * hostname, int port) {

    //ziskanie adresy a portu servera <netdb.h>
    struct hostent *server = gethostbyname(hostname);
    if (server == NULL) {
        printError("[-]Server is unreachable.");
    }

    if (port <= 0) {
        printError("[-]Port must be an integer and bigger than zero.");
    }

    //vytvorenie socketu <sys/socket.h>
    soket->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (soket->sockfd < 0) {
        printError("[-]Error - socket.");
    }

    bzero((char*)&soket->serv_addr, sizeof(soket->serv_addr));
    soket->serv_addr.sin_family = AF_INET;
    soket->serv_addr.sin_addr.s_addr = INADDR_ANY;
    soket->serv_addr.sin_port = htons(port);

    //definovanie adresy servera <arpa/inet.h>
    struct sockaddr_in serverAddress;
    bzero((char *)&serverAddress, sizeof(serverAddress));

    if (connect(soket->sockfd,(struct sockaddr *)&soket->serv_addr, sizeof(soket->serv_addr)) < 0) {
        printError("[-]Error - connect.");
    }
    soket->newsockfd = soket->sockfd;

    return (EXIT_SUCCESS);
}
