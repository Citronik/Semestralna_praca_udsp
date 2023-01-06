//
// Created by Filip on 29. 12. 2022.
//

#ifndef SEMESTRALNA_PRACA_UDSP_SOCKET_DEFINITIONS_H
#define SEMESTRALNA_PRACA_UDSP_SOCKET_DEFINITIONS_H

#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include "socket.h"


#ifdef	__cplusplus
extern "C" {
#endif

#define USER_LENGTH 10
#define MAX_POCET_POUZIVATELOV 20
#include "registration_system.h"
#include "token.h"


extern char *endMsg;

typedef struct data {
    char userName[USER_LENGTH + 1];
    pthread_mutex_t mutex;
    int socket;
    int state;
    int stop;
} DATA;

void data_init(DATA *data, const char* userName, const int socket);
void data_destroy(DATA *data);
void data_stop(DATA *data);
int data_isStopped(DATA *data);
void *data_readData(void *data);
void *data_writeData(void *data);
int create_connection(SOCKET * soket, int sietoveNastavenia);
void * server_handle_new_users(void * datas);
int send_message(DATA * data, TOKEN * token);
int read_message(DATA * data, TOKEN * token);
int client_socket_started(SOCKET * soket, char * hostname, int port);

void printError(char *str);

#ifdef	__cplusplus
}
#endif

#endif //SEMESTRALNA_PRACA_UDSP_SOCKET_DEFINITIONS_H
