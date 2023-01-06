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
    return token1->user_id_ == token2->user_id_;
}