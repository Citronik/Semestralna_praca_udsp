//
// Created by Filip on 6. 1. 2023.
//
#include "../header_file/registration_system_responses.h"

void system_set_message(TOKEN * token, int message_type){
    switch (message_type) {
        case 0:
            token->response_status_ = 200;
            strcpy(token->response_, system_message_initial);
            break;
        case 1:
            token->response_status_ = 200;
            strcpy(token->response_, system_message_initial);
            break;
        case 2:
            token->response_status_ = 200;
            token->service_type_ = SYSTEM_RESPONSE_AUTH_SUC;
            strcpy(token->response_, system_message_auth_suc);
            break;
        default:
            token->response_status_ = 404;
            strcpy(token->response_, system_message_unauth);
            strcpy(token->content_, system_message_unauth);
            break;
    }
}