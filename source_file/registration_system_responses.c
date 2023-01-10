//
// Created by Filip on 6. 1. 2023.
//
#include "../header_file/registration_system_responses.h"

void system_set_message(TOKEN * token, int message_type){
    switch (message_type) {
        case SYSTEM_RESPONSE_INIT:
            token->response_status_ = SYSTEM_RESPONSE_SUCCESSFUL;
            strcpy(token->response_, system_message_initial);
            break;
        case SYSTEM_RESPONSE_INIT_STATE:
            token->response_status_ = SYSTEM_RESPONSE_SUCCESSFUL;
            strcpy(token->response_, system_message_initial);
            break;
        case SYSTEM_RESPONSE_AUTH_SUC:
            token->response_status_ = SYSTEM_RESPONSE_SUCCESSFUL;
            token->service_type_ = SYSTEM_RESPONSE_AUTH_SUC;
            strcpy(token->response_, system_message_auth_suc);
            break;
        case SYSTEM_RESPONSE_REG:
            token->response_status_ = SYSTEM_RESPONSE_SUCCESSFUL;
            token->service_type_ = SYSTEM_RESPONSE_AUTH_SUC;
            strcpy(token->response_, system_message_auth_suc);
            break;
        case SYSTEM_RESPONSE_REG_UNSUC:
            token->response_status_ = SYSTEM_RESPONSE_SERVER_ERR;
            token->service_type_ = SYSTEM_RESPONSE_REG;
            strcpy(token->response_, system_message_max_capacity_exceed);
            break;
        case SYSTEM_RESPONSE_USR_ALREADY_REG:
            token->response_status_ = SYSTEM_RESPONSE_UNAUTH;
            token->service_type_ = SYSTEM_RESPONSE_REG;
            strcpy(token->response_, system_message_max_capacity_exceed);
            break;
        case SYSTEM_RESPONSE_REG_SUC:
            token->response_status_ = SYSTEM_RESPONSE_SUCCESSFUL;
            token->service_type_ = SYSTEM_RESPONSE_REG;
            strcpy(token->response_, system_message_reg_succ);
            break;
        case SYSTEM_RESPONSE_USR_LOGOUT:
            token->response_status_ = SYSTEM_RESPONSE_SUCCESSFUL;
            token->service_type_ = SYSTEM_RESPONSE_INIT_STATE;
            token->user_id_ = SYSTEM_RESPONSE_INIT;
            strcpy(token->response_, system_message_user_logout);
            break;
        case SYSTEM_RESPONSE_ITEM_NOT_FOUND:
            token->response_status_ = SYSTEM_RESPONSE_UNAUTH;
            token->service_type_ = SYSTEM_RESPONSE_INIT_STATE;
            strcpy(token->response_, system_message_item_not_found);
            break;
        case SYSTEM_RESPONSE_USER_NOT_FOUND:
            token->response_status_ = SYSTEM_RESPONSE_UNAUTH;
            token->service_type_ = SYSTEM_RESPONSE_INIT_STATE;
            strcpy(token->response_, system_message_user_not_found);
            break;
        case SYSTEM_RESPONSE_SUC_OPERATION:
            token->response_status_ = SYSTEM_RESPONSE_SUCCESSFUL;
            token->service_type_ = SYSTEM_RESPONSE_INIT_STATE;
            strcpy(token->response_, system_message_suc_operation);
            break;
        case SYSTEM_RESPONSE_UNSUC_OPERATION:
            token->response_status_ = SYSTEM_RESPONSE_UNAUTH;
            token->service_type_ = SYSTEM_RESPONSE_INIT_STATE;
            strcpy(token->response_, system_message_unsuc_operation);
            break;
        default:
            token->response_status_ = SYSTEM_RESPONSE_UNAUTH;
            strcpy(token->response_, system_message_unauth);
            strcpy(token->content_, system_message_unauth);
            break;
    }
}