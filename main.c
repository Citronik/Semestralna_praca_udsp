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


    pthread_t thread_user1, thread_user2;
    pthread_create(&thread_user1, NULL, client_start_app, NULL);
    pthread_create(&thread_user2, NULL, client_start_app, NULL);
    //client_start_app();

    pthread_join(thread_user1, NULL);
    pthread_join(thread_user2, NULL);



    /*USER * user = malloc(sizeof(USER));
    user_init(user);
    user_set_first_name(user, "Jozko");
    user_set_last_name(user, "Hron");
    user_set_username(user, "hronko");
    user_set_password(user, "hronko1");
    TOKEN * token = malloc(sizeof(TOKEN));
    user_to_token(user, token);
    printf("%s\n", token->content_);*/

#undef CHARACTERS
#undef MAX_POCET_POUZIVATELOV
    return 0;
}
