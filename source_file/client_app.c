//
// Created by Filip on 6. 1. 2023.
//
#include "../header_file/client_app.h"
#include "../header_file/socket_definitions.h"

void * client_start_app() {
    TOKEN * token = malloc(sizeof(TOKEN));
    token_init(token);
    SOCKET soket;
    client_socket_started(&soket, "127.0.0.1", 11112);
    DATA data;
    data.socket = soket.newsockfd;
    read_message(&data, token);
    printf("%s\n",token->response_);

}