//
// Created by slavi on 4. 1. 2023.
//

#ifndef SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_H
#define SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_H
#include "../header_file/user.h"
#define CAPACITY 30
#define BUFFER 150
typedef struct registration_system {
    USER users_[CAPACITY];
    unsigned int number_of_users_;
    //double earnings;
} REGISTRATION_SYSTEM;

USER* add_user(REGISTRATION_SYSTEM *rs, USER *us); //adding existing user
USER* remove_user(REGISTRATION_SYSTEM *rs, USER *us); // removing existing user (only from reg.system)
void print_users(const REGISTRATION_SYSTEM *rs); // prints users in the registration system
_Bool create_user(REGISTRATION_SYSTEM *rs); // create new user
_Bool delete_user(REGISTRATION_SYSTEM *rs); //complete delete of user
USER * find_user(REGISTRATION_SYSTEM *rs); // finds the user in the registration system
void reg_sys_to_string(REGISTRATION_SYSTEM *rs); // prints details about the registration system

#endif //SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_H
