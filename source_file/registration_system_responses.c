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
        default:
            token->response_status_ = 404;
            token->response_;
            break;
    }
}