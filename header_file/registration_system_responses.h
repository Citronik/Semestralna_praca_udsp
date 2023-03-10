//
// Created by Filip on 6. 1. 2023.
//

#include "token.h"

#ifndef SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_RESPONSES_H
#define SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_RESPONSES_H

#define SYSTEM_RESPONSE_INIT 0
#define SYSTEM_RESPONSE_INIT_STATE 1
#define SYSTEM_RESPONSE_AUTH_SUC 2
#define SYSTEM_RESPONSE_REG 3
#define SYSTEM_RESPONSE_REG_UNSUC 4
#define SYSTEM_RESPONSE_USR_ALREADY_REG 5
#define SYSTEM_RESPONSE_REG_SUC 6
#define SYSTEM_RESPONSE_USR_LOGOUT 7
#define SYSTEM_RESPONSE_ITEM_NOT_FOUND 8
#define SYSTEM_RESPONSE_USER_NOT_FOUND 9
#define SYSTEM_RESPONSE_SUC_OPERATION 10
#define SYSTEM_RESPONSE_UNSUC_OPERATION 11


#define SYSTEM_RESPONSE_SUCCESSFUL 200
#define SYSTEM_RESPONSE_UNAUTH 404
#define SYSTEM_RESPONSE_SERVER_ERR 500

static char * system_message_initial = "You were succesfully connested to the server";
static char * system_message_auth_suc = "You were succesfully authorized";
static char * system_message_unauth = "Unauthorized activity";
static char * system_message_no = "Wrong username and password";
static char * system_message_reg_succ = "User was succesfully registered";
static char * system_message_user_logout = "User was succesfully legged out";
static char * system_message_max_capacity_exceed = "Maximum capacity has been reached!";
static char * system_message_item_not_found = "Item you searched for is not in the system!";
static char * system_message_user_not_found = "User not found!";
static char * system_message_suc_operation = "Succesfull Operation";
static char * system_message_unsuc_operation = "Operation failed, you dont have enought credit or reached maximal capacity of your components";


void system_set_message(TOKEN * token, int message_type);

#endif //SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_RESPONSES_H
