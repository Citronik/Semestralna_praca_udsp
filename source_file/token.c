//
// Created by Filip on 5. 1. 2023.
//
#include "../header_file/token.h"

void token_init(TOKEN * token){
    token->content_;
    memset(token->content_,0,CONTENT_LENGTH);
    token->response_;
    memset(token->response_,0,CONTENT_LENGTH);
    token->service_type_ = 0;
    token->user_id_ = 0;
    token->response_status_ = 0;
}

_Bool token_compare(TOKEN * token1, TOKEN * token2){
    printf("Comparing tokens : %d  %d", token1->user_id_, token2->user_id_);
    return token1->user_id_ == token2->user_id_;
}

_Bool token_is_active(TOKEN * token){
    return token->service_type_ != 0;
}

_Bool token_to_user(USER* user, TOKEN * token){
    size_t offset = 0;
    strncpy(user->first_name_, (token->content_+offset), USER_NAME_LENGTH);
    offset += USER_NAME_LENGTH;
    strncpy(user->last_name_, (token->content_+offset), USER_NAME_LENGTH);
    offset += USER_NAME_LENGTH;
    strncpy(user->username_, (token->content_+offset), USER_NAME_LENGTH);
    offset += USER_NAME_LENGTH;
    strncpy(user->password_, (token->content_+offset), USER_PASSWORD_LENGTH);
    offset += USER_PASSWORD_LENGTH;
    return true;
}

_Bool token_login_details(USER* user, TOKEN * token){
    strncpy(user->username_, token->content_, USER_NAME_LENGTH);
    strncpy(user->password_, token->content_+USER_NAME_LENGTH, USER_PASSWORD_LENGTH);
    return strlen(user->username_) > 0 && strlen(user->password_) > 0;
}

_Bool user_to_token(USER* user, TOKEN * token) {
    size_t offset = 0;
    strncpy((token->content_+offset), user->first_name_, USER_NAME_LENGTH);
    offset += USER_NAME_LENGTH;
    strncpy((token->content_+offset), user->last_name_, USER_NAME_LENGTH);
    offset += USER_NAME_LENGTH;
    strncpy((token->content_+offset), user->username_, USER_NAME_LENGTH);
    offset += USER_NAME_LENGTH;
    strncpy((token->content_+offset), user->password_, USER_PASSWORD_LENGTH);
    offset += USER_PASSWORD_LENGTH;
    return true;
}