//
// Created by Filip on 29. 12. 2022.
//

#ifndef SEMESTRALNA_PRACA_UDSP_USER_H
#define SEMESTRALNA_PRACA_UDSP_USER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "computer_component.h"

#define USER_NAME_LENGTH 50
#define USER_PASSWORD_LENGTH 20
#define USER_MAX_COMPONENTS 10

typedef struct user {
    char first_name_[USER_NAME_LENGTH];
    char last_name_[USER_NAME_LENGTH];
    char username_[USER_NAME_LENGTH];
    char password_[USER_PASSWORD_LENGTH];
    COMPONENT owned_components_[USER_MAX_COMPONENTS];
    int number_of_owned_components_;
    double credit_;
    int id_;
} USER;

_Bool compare_users(const USER *us1, const USER *us2);
char* user_to_string(const USER *us, char *dest);
void recharge_credit(USER *us, double value);
void user_set_first_name(USER *us, char * first_name);
void user_set_last_name(USER *us, char * last_name);
void user_set_username(USER *us, char * username);
void user_set_password(USER *us, char * password);
COMPONENT * remove_component_from_user(USER *us, int component_id);
COMPONENT * add_component_to_user(USER *us, COMPONENT *cp);
void user_init(USER * user);
#endif //SEMESTRALNA_PRACA_UDSP_USER_H
