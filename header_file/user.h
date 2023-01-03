//
// Created by Filip on 29. 12. 2022.
//

#ifndef SEMESTRALNA_PRACA_UDSP_USER_H
#define SEMESTRALNA_PRACA_UDSP_USER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define USER_NAME_LENGTH 50
#define USER_PASSWORD_LENGTH 20
#define USER_EMAIL_LENGTH 70

typedef struct user {
    char user_email_[USER_EMAIL_LENGTH];
    char first_name_[USER_NAME_LENGTH];
    char last_name_[USER_NAME_LENGTH];
    char username_[USER_NAME_LENGTH];
    char password_[USER_PASSWORD_LENGTH];
    int id_;
} USER;

_Bool compare_users(const USER *us1, const USER *us2);
char* user_to_string(const USER *us, char *dest);
void recharge_credit(USER *us, double value);


#endif //SEMESTRALNA_PRACA_UDSP_USER_H
