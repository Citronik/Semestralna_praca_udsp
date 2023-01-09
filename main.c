#include "header_file/registration_system.h"
#define MAX_POCET_POUZIVATELOV 20


int main() {
    // reg system init
    reg_sys_ = calloc(1, sizeof(REGISTRATION_SYSTEM));
    registration_system_init(reg_sys_);
    USER * user = malloc(sizeof(USER));
    user_init(user);
    user_set_username(user, "asd");
    user_set_first_name(user, "asd");
    user_set_last_name(user, "asd");
    user_set_password(user, "asd");
    user->id_ = 6452694;
    user->credit_ = 1000;
    add_user(reg_sys_, user, NULL);
    SOCKET soket;
    //soket.reg = reg;
    create_connection(&soket, 11112);
    //pthread_t threads[MAX_POCET_POUZIVATELOV];
    pthread_t thread_new_users;
    pthread_create(&thread_new_users, NULL, server_handle_new_users, (void *)&soket);

    pthread_join(thread_new_users, NULL);
    //free(reg);
    //reg =NULL;

#undef SYSTEM_RESPONSE_AUTH_SUC
#undef CHARACTERS
#undef MAX_POCET_POUZIVATELOV
    return 0;
}
