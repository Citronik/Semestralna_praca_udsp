//
// Created by Filip on 5. 1. 2023.
//

#ifndef SEMESTRALNA_PRACA_UDSP_TOKEN_H
#define SEMESTRALNA_PRACA_UDSP_TOKEN_H

#define CONTENT_LENGTH 200
//#define USER_ID_LENGTH 50
#include <string.h>

typedef struct token{
    char content_[CONTENT_LENGTH];
    //char user_id_[USER_ID_LENGTH];
    int user_id_;
    int service_type_;
} TOKEN;

void token_init(TOKEN * token);


#undef VELKOST_SPRAVY
#endif //SEMESTRALNA_PRACA_UDSP_TOKEN_H
