//
// Created by Filip on 5. 1. 2023.
//

#ifndef SEMESTRALNA_PRACA_UDSP_TOKEN_H
#define SEMESTRALNA_PRACA_UDSP_TOKEN_H

#define CONTENT_LENGTH 500
//#define USER_ID_LENGTH 50
#include <string.h>

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


#undef VELKOST_SPRAVY
#endif //SEMESTRALNA_PRACA_UDSP_TOKEN_H
