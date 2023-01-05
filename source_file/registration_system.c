//
// Created by slavi on 4. 1. 2023.
//
#include "../header_file/registration_system.h"

USER* add_user(REGISTRATION_SYSTEM *rs, USER *us) {
    if (rs->number_of_users_ >= CAPACITY) {
        printf("Maximum capacity has been reached!\n");
        return NULL;
    }
    for (int i = 0; i < rs->number_of_users_; i++) {
        if (compare_users(us, &rs->users_[i])){
            return &rs->users_[i];
        }
    }
    rs->users_[rs->number_of_users_] = * us;
    rs->number_of_users_++;
    printf("User: %s %s , username: %s, user email: %s password: %s , ID: %d has been added to the registration system!\n",
           us->first_name_,us->last_name_,us->username_,us->user_email_,us->password_,us->id_);
    return &rs->users_[rs->number_of_users_-1];

}

USER* remove_user(REGISTRATION_SYSTEM *rs, USER *us) {
    if (rs->number_of_users_ == 0) {
        printf("There are not any users in the system!\n");
        return false;
    }

    for(int i = 0; i < rs->number_of_users_; i++) {
        if(compare_users(&rs->users_[i], us)){
            *us = rs->users_[i];
            rs->users_[i] = rs->users_[rs->number_of_users_ - 1];
            rs->users_[rs->number_of_users_ - 1] = rs->users_[rs->number_of_users_ + 1];
            rs->number_of_users_--;
        }
    }
    printf("User: %s %s , username: %s, user email: %s password: %s , ID: %d has been removed from the registration system!\n",
           us->first_name_,us->last_name_,us->username_,us->user_email_,us->password_,us->id_);

    for (int i = 0; i < rs->number_of_users_; i++) {
        if (!compare_users(us, &rs->users_[i])){
            return &rs->users_[i];
        }
        printf("User is not in the registration system\n");
    }
}


void print_users(const REGISTRATION_SYSTEM *rs) {
    if (rs->number_of_users_ <= 0) {
        printf("There are not any users in the system!\n");
    }
    char tmpStr[BUFFER];
    for (int i = 0; i < rs->number_of_users_; i++) {
        user_to_string(&rs->users_[i], tmpStr);
        printf("%s", tmpStr);
    }
}

_Bool create_user(REGISTRATION_SYSTEM *rs) {
    USER tmp_user;
    char tmp_first_name[USER_NAME_LENGTH];
    char tmp_last_name[USER_NAME_LENGTH];
    char tmp_username[USER_NAME_LENGTH];
    char tmp_email[USER_EMAIL_LENGTH];
    char tmp_password[USER_PASSWORD_LENGTH];
    int tmp_id;

    printf("Creating the user...\n");

    printf("Enter a first name:\n");
    scanf("%s",tmp_first_name);
    strcpy(tmp_user.first_name_, tmp_first_name);

    printf("Enter a last name: \n");
    scanf("%s",tmp_last_name);
    strcpy(tmp_user.last_name_, tmp_last_name);

    printf("Enter a username: \n");
    scanf("%s",tmp_username);
    strcpy(tmp_user.username_, tmp_username);

    printf("Enter an email: \n");
    scanf("%s",tmp_email);
    strcpy(tmp_user.user_email_, tmp_email);

    printf("Enter the password: \n");
    scanf("%s",tmp_password);
    strcpy(tmp_user.password_, tmp_password);

    printf("Enter the ID of user: \n");
    scanf("%d",&tmp_id);
    tmp_user.id_ = tmp_id;

    if(add_user(rs,&tmp_user)){
        return true;
    }
    return false;
}

USER * find_user(REGISTRATION_SYSTEM *rs) {
    char tmp_first_name[USER_NAME_LENGTH];
    char tmp_last_name[USER_NAME_LENGTH];
    int tmp_id;

    printf("Finding the user...\n");

    printf("First name:\n");
    scanf("%s",tmp_first_name);

    printf("Last name: \n");
    scanf("%s",tmp_last_name);

    printf("ID of user: \n");
    scanf("%d",&tmp_id);

    for (int i = 0; i < rs->number_of_users_; i++) {
        if(strcmp(rs->users_[i].first_name_, tmp_first_name) == 0 && rs->users_[i].id_ == tmp_id &&
           strcmp(rs->users_[i].last_name_, tmp_last_name) == 0 ) {
            return &rs->users_[i];

        }
    }
    printf("This user is not in the system! \n");
    return NULL;
}

_Bool delete_user(REGISTRATION_SYSTEM *rs) {
    USER *tmp_user = find_user(rs);
    if(tmp_user == NULL){
        printf("Incorrect parameters!\n");
        return false;
    }
    remove_user(rs,tmp_user);
    return true;
}

void reg_sys_to_string(REGISTRATION_SYSTEM *rs){
    printf("Registration system has %d users and the capacity is %d\n"
           "",rs->number_of_users_,CAPACITY);
}

void * registration_system_start(void * data) {

}