//
// Created by Filip on 29. 12. 2022.
//

#ifndef SEMESTRALNA_PRACA_UDSP_USER_H
#define SEMESTRALNA_PRACA_UDSP_USER_H

#define USER_NAME_LENGTH 50
#define USER_PASSWORD_LENGTH 20
#define USER_EMAIL_LENGTH 70

typedef struct user {
    char user_email_[USER_EMAIL_LENGTH];
    char first_name_[USER_NAME_LENGTH];
    char last_name_[USER_NAME_LENGTH];
    char password_[USER_PASSWORD_LENGTH];
    int id_;
} USER;


#endif //SEMESTRALNA_PRACA_UDSP_USER_H
