#include <stdio.h>
#include "header_file/socket_definitions.h"
#include "header_file/registration_system.h"
#include "header_file/client_app.h"

#define MAX_POCET_POUZIVATELOV 20


int main() {
    REGISTRATION_SYSTEM reg;
    SOCKET soket;
    create_connection(&soket, 11112);
    pthread_t threads[MAX_POCET_POUZIVATELOV];
    pthread_t thread_new_users;
    pthread_create(&thread_new_users, NULL, server_handle_new_users, (void *)&soket);


    pthread_join(thread_new_users, NULL);
#undef CHARACTERS
#undef MAX_POCET_POUZIVATELOV
    return 0;
}
