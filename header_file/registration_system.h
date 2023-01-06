//
// Created by slavi on 4. 1. 2023.
//

#ifndef SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_H
#define SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_H
#include "../header_file/user.h"
#include "socket_definitions.h"
#include "registration_system_responses.h"

#define CAPACITY 30
#define BUFFER 150
typedef struct registration_system {
    USER users_[CAPACITY];
    COMPONENT components_[CAPACITY];
    TOKEN * active_users_[CAPACITY];
    unsigned int number_of_components;
    unsigned int number_of_users_;
    double sales;
} REGISTRATION_SYSTEM;

//void registration_system_init(REGISTRATION_SYSTEM *rs);
void * registration_system_start(void * data);
USER* add_user(REGISTRATION_SYSTEM *rs, USER *us); //adding existing user
USER* remove_user(REGISTRATION_SYSTEM *rs, USER *us); // removing existing user (only from reg.system)
void print_users(const REGISTRATION_SYSTEM *rs); // prints users in the registration system
void print_components(const REGISTRATION_SYSTEM *rs);
_Bool registrate_user(REGISTRATION_SYSTEM *rs); // create new user
_Bool delete_user(REGISTRATION_SYSTEM *rs); //complete delete of user
USER * find_user(REGISTRATION_SYSTEM *rs); // finds the user in the registration system
COMPONENT * find_component(REGISTRATION_SYSTEM  *rs);
void reg_sys_to_string(REGISTRATION_SYSTEM *rs); // prints details about the registration system
COMPONENT* add_component(REGISTRATION_SYSTEM *rs, COMPONENT *cp); // adding component
COMPONENT* remove_component(REGISTRATION_SYSTEM *rs, COMPONENT *cp);  // removing component
_Bool registrate_component(REGISTRATION_SYSTEM *rs);
void buy_item_for_user(REGISTRATION_SYSTEM *rs,USER *us,COMPONENT *cp);
void remove_item_from_user(REGISTRATION_SYSTEM *rs,USER *us,COMPONENT *cp);
void charge_credit_for_user(REGISTRATION_SYSTEM *rs, USER *us);
#endif //SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_H
