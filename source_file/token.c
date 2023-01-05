//
// Created by Filip on 5. 1. 2023.
//



#include "../header_file/token.h"

void token_init(TOKEN * token){
    token->content_;
    memset(token->content_,0,CONTENT_LENGTH);
    token->service_type_ = 0;
    token->user_id_ = 0;
}