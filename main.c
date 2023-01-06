#include <stdio.h>
#include "header_file/socket_definitions.h"
#include "header_file/registration_system.h"
#include "header_file/client_app.h"

#define MAX_POCET_POUZIVATELOV 20


int main() {
    REGISTRATION_SYSTEM reg;
    SOCKET soket;
    create_connection(&soket, 11111);
    pthread_t threads[MAX_POCET_POUZIVATELOV];
    server_handle_new_users(&soket);

    client_start_app();

#undef CHARACTERS
#undef MAX_POCET_POUZIVATELOV
    return 0;
}
