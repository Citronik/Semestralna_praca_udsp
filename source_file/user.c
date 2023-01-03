//
// Created by Filip on 29. 12. 2022.
//
#include "../header_file/user.h"


_Bool compare_users(const USER *us1, const USER *us2){
    if (strcmp(us1->first_name_,us2->first_name_) == 0){
        return true;
    }
    if (strcmp(us1->last_name_,us2->last_name_) == 0 && (us1->id_ == us2->id_)){
        return true;
    }
    return false;
}


char* user_to_string(const USER *us, char *dest) {
    sprintf(dest, "User: %s %s, username:  %s, email: %s, id: %d  \n",us->first_name_,us->last_name_,us->username_,us->user_email_,us->id_);
    return dest;
}



void recharge_credit(USER *us, double value) {
    if(value > 0) {
        us->credit += value;
        printf("Credit of the user %s %s, was increased by %.2f€ \n",us->name,us->surname,value);
        printf("The user %s %s has credit %.2f€\n",us->name,us->surname,us->credit);
    } else {
        printf("Top-up credit must be greater than 0 euros!\n");
    }

} //toto neviem ci budeme potrebovat este