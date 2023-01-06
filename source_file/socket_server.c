//
// Created by Filip on 29. 12. 2022.
//
#include "../header_file/socket_definitions.h"
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

int create_connection(SOCKET * soket, int network_port) {

    bzero((char*)&soket->serv_addr, sizeof(soket->serv_addr));
    soket->serv_addr.sin_family = AF_INET;
    soket->serv_addr.sin_addr.s_addr = INADDR_ANY;
    soket->serv_addr.sin_port = htons(network_port);

    soket->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (soket->sockfd < 0)
    {
        perror("Error creating socket");
        return 1;
    }

    if (bind(soket->sockfd, (struct sockaddr*)&soket->serv_addr, sizeof(soket->serv_addr)) < 0)
    {
        perror("Error binding socket address");
        return 2;
    }

    listen(soket->sockfd, 5);
    soket->cli_len = sizeof(soket->cli_addr);
    printf("Socket opened on port: %d \n", network_port);
    return 0;
}

void * server_handle_new_users(void * datas) {
    int number_of_users = 0;
    SOCKET * soket = (SOCKET* )datas;
    pthread_t thread[MAX_POCET_POUZIVATELOV];
    while (number_of_users <= MAX_POCET_POUZIVATELOV) {
        soket->newsockfd = accept(soket->sockfd, (struct sockaddr*)&soket->cli_addr, &soket->cli_len);
        if (soket->newsockfd < 0)
        {
            perror("ERROR on accept");
            exit(1);
        }
        DATA data;
        data.socket = soket->newsockfd;
        pthread_create(&thread[number_of_users], NULL, registration_system_start, (void *)&data);
        printf("User succesfully connected: %d \n", data.socket);
        ++number_of_users;
    }
}

/*
void server_socket_start() {
    int port = 11111;

    int sockfd, ret;
    struct sockaddr_in serverAddr;

    int newSocket;
    struct sockaddr_in newAddr;

    socklen_t addr_size;

    char buffer[1024];
    pid_t childpid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        printf("[-]Error in connection.\n");
        exit(1);
    }
    printf("[+]Server Socket is created.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(ret < 0){
        printf("[-]Error in binding.\n");
        exit(1);
    }
    printf("[+]Bind to port %d\n", 4444);

    if(listen(sockfd, 10) == 0){
        printf("[+]Listening....\n");
    }else{
        printf("[-]Error in binding.\n");
    }


    while(1){
        newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
        if(newSocket < 0){
            exit(1);
        }
        printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

        if((childpid = fork()) == 0){
            close(sockfd);

            while(1){
                recv(newSocket, buffer, 1024, 0);
                if(strcmp(buffer, ":exit") == 0){
                    printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                    break;
                }else{
                    printf("Client: %s\n", buffer);
                    send(newSocket, buffer, strlen(buffer), 0);
                    bzero(buffer, sizeof(buffer));
                }
            }
        }

    }

    close(newSocket);

}
*/
