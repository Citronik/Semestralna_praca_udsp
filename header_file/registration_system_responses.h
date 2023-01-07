//
// Created by Filip on 6. 1. 2023.
//

#include "token.h"

#ifndef SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_RESPONSES_H
#define SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_RESPONSES_H

#define SYSTEM_RESPONSE_AUTH_SUC 2

static char * system_message_initial = "You were succesfully connested to the server";
static char * system_message_auth_suc = "You were succesfully authorized";
static char * system_message_unauth = "Unauthorized activity";
static char * system_message_no = "Wrong username and password";


void system_set_message(TOKEN * token, int message_type);

#endif //SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_RESPONSES_H
