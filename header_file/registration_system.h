//
// Created by slavi on 4. 1. 2023.
//

#ifndef SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_H
#define SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_H
#include "user.h"
#define CAPACITY 30
typedef struct registration_system {
    USER users_[CAPACITY];
    unsigned int number_of_users_;
    double earnings;
} REGISTRATION_SYSTEM;

REGISTRATION_SYSTEM add_user(); //adding existing user
REGISTRATION_SYSTEM remove_user(); // removing existing user
void print_users(const REGISTRATION_SYSTEM *rs);
_Bool create_user(REGISTRATION_SYSTEM *rs); // create new user
_Bool delete_user(REGISTRATION_SYSTEM *rs);
void reg_sys_to_string(REGISTRATION_SYSTEM *rs);

#endif //SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_H
