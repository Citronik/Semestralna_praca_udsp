//
// Created by Filip on 5. 1. 2023.
//

#ifndef SEMESTRALNA_PRACA_UDSP_TOKEN_H
#define SEMESTRALNA_PRACA_UDSP_TOKEN_H

#define CONTENT_LENGTH 500
//#define USER_ID_LENGTH 50
#include <string.h>
#include "user.h"

typedef struct token{
    char content_[CONTENT_LENGTH];
    char response_[CONTENT_LENGTH];
    //char user_id_[USER_ID_LENGTH];
    int user_id_;
    int service_type_;
    int response_status_;
} TOKEN;

void token_init(TOKEN * token);
_Bool token_compare(TOKEN * token1, TOKEN * token2);
_Bool token_is_active(TOKEN * token);
_Bool user_to_token(USER* user, TOKEN * token);
_Bool token_to_user(USER* user, TOKEN * token);
_Bool token_login_details(USER* user, TOKEN * token);


#endif //SEMESTRALNA_PRACA_UDSP_TOKEN_H
