//
// Created by Filip on 29. 12. 2022.
//
#include "../header_file/socket_definitions.h"

char *endMsg = ":end";

void data_init(DATA *data, const char* userName, const int socket) {
    data->socket = socket;
    data->stop = 0;
    data->state = 0;
    data->userName[USER_LENGTH] = '\0';
    strncpy(data->userName, userName, USER_LENGTH);
    pthread_mutex_init(&data->mutex, NULL);
}

void data_destroy(DATA *data) {
    pthread_mutex_destroy(&data->mutex);
}

void data_stop(DATA *data) {
    pthread_mutex_lock(&data->mutex);
    data->stop = 1;
    pthread_mutex_unlock(&data->mutex);
}

int data_isStopped(DATA *data) {
    int stop;
    pthread_mutex_lock(&data->mutex);
    stop = data->stop;
    pthread_mutex_unlock(&data->mutex);
    return stop;
}

int send_message(DATA * data, TOKEN * token) {
    data->state = write(data->socket, token, sizeof (TOKEN));
    printf("Sending message: n = [%d]\n",data->state);

    if (data->state < 0) {
        perror("[-]Error writing to socket");
        return 5;
    }
    return 0;
}

int read_message(DATA * data, TOKEN * token) {
    data->state = read(data->socket, token, sizeof (TOKEN));
    printf("Message received: n = [%d]\n",data->state);
    if (data->state < 0) {
        perror("[-]Error reading from socket");
        return 6;
    }
    return 0;
}

void printError(char *str) {
    if (errno != 0) {
        perror(str);
    }
    else {
        fprintf(stderr, "%s\n", str);
    }
    exit(EXIT_FAILURE);
}
