//
// Created by Filip on 29. 12. 2022.
//

#ifndef SEMESTRALNA_PRACA_UDSP_SOCKET_DEFINITIONS_H
#define SEMESTRALNA_PRACA_UDSP_SOCKET_DEFINITIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <netdb.h>
#include "token.h"
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "socket.h"


#define USER_LENGTH 10
#define MAX_POCET_POUZIVATELOV 20

extern char *endMsg;

typedef struct data {
    //REGISTRATION_SYSTEM * reg;
    char userName[USER_LENGTH + 1];
    pthread_mutex_t mutex;
    int socket;
    size_t state;
    int stop;
} DATA;

void data_init(DATA *data, const char* userName, const int socket);
void data_destroy(DATA *data);
void data_stop(DATA *data);
int data_isStopped(DATA *data);
void *data_readData(void *data);
void *data_writeData(void *data);
int create_connection(SOCKET * soket, int sietoveNastavenia);
int send_message(DATA * data, TOKEN * token);
int read_message(DATA * data, TOKEN * token);
int client_socket_started(SOCKET * soket, char * hostname, int port);

void printError(char *str);

#ifdef	__cplusplus
}
#endif

#endif
