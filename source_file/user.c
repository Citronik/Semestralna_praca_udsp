//
// Created by Filip on 29. 12. 2022.
//
#include "../header_file/user.h"

void user_init(USER * user) {
    memset(user->first_name_,0,strlen(user->first_name_));
    memset(user->last_name_,0,strlen(user->last_name_));
    memset(user->password_,0,strlen(user->password_));
    memset(user->username_,0,strlen(user->username_));
    user->credit_ = 0;
    user->id_ = 0;
    user->number_of_owned_components_ = 0;
    for (int i = 0; i < USER_MAX_COMPONENTS; ++i) {
        component_init(&(user->owned_components_[i]));
    }
}

_Bool compare_users(const USER *us1, const USER *us2){
    return strcmp(us1->username_, us2->username_) == 0;
}

COMPONENT * add_component_to_user(USER *us, COMPONENT *cp) {
    for (int i = 0; i < us->number_of_owned_components_; i++) {
        if (compare_components(cp, &us->owned_components_[i])){
            printf("%s  %.2f\n", cp->model_, cp->price_);
            return &us->owned_components_[i];
        }
    }
    printf("%s  %.2f\n", cp->model_, cp->price_);
    printf("%s  %d  %.2f\n", us->username_, us->number_of_owned_components_, us->credit_);
    if (us->number_of_owned_components_ >= USER_MAX_COMPONENTS || us->credit_ < cp->price_) {
        printf("User %s (%s %s) reached maximum capacity %d of owned items or does not have enough credit %.2f on the account!\n"
               ,us->username_,us->first_name_,us->last_name_, us->number_of_owned_components_, us->credit_);
        return NULL;
    }
    us->owned_components_[us->number_of_owned_components_] = * cp;
    us->number_of_owned_components_++;
    us->credit_ -= cp->price_;
    printf("User has bought the component\nmanufacturer: %s \ntype: %s\nmodel: %s\nyear: %d\nprice: %.2f €\n\n",
           cp->manufacturer_,cp->type_,cp->model_,cp->year_of_production_,cp->price_);
    printf("Remaining credit of user %s (%s %s) is %.2f € \n",us->username_,us->first_name_,us->last_name_,us->credit_);
    return &us->owned_components_[us->number_of_owned_components_-1];

}

COMPONENT * remove_component_from_user(USER *us, int component_id) {
    if (component_id < 0 || component_id >= us->number_of_owned_components_) {
        printf("[-]USER %s COMPONENT %d NOT FOUND!\n", us->username_, component_id);
        return NULL;
    }
    printf("[+]USER %s COMPONENT %s FOUND!\n", us->username_, us->owned_components_[component_id].model_);

    if (component_id != us->number_of_owned_components_-1){
        printf("%s\n", us->owned_components_[component_id+1].model_);
        memcpy(&us->owned_components_[component_id], &us->owned_components_[component_id+1]
               ,((us->number_of_owned_components_-1)-component_id)*sizeof(COMPONENT));
    }
    --us->number_of_owned_components_;
    return &us->owned_components_[component_id];
}


char* user_to_string(const USER *us, char *dest) {
    sprintf(dest, "User: %s %s, username:  %s, id: %d, credit: %.2f€  \n",us->first_name_,us->last_name_,us->username_,us->id_, us->credit_);
    return dest;
}

void recharge_credit(USER *us, double value) {
    if(value > 0) {
        us->credit_ += value;
        printf("Credit of the user %s %s, was increased by %.2f€ \n",us->first_name_,us->last_name_,value);
        printf("The user %s has credit %.2f€\n",us->username_,us->credit_);
    } else {
        printf("Top-up credit must be greater than 0 euros!\n");
    }
}

void user_set_first_name(USER *us, char * first_name) {
    if (strlen(first_name) <=0 || strlen(first_name) > USER_NAME_LENGTH) {
        printf("Invalid data!\n");
        exit(1);
    }

    strcpy(us->first_name_, first_name);
}

void user_set_last_name(USER *us, char * last_name) {
    if (strlen(last_name) <=0 || strlen(last_name) > USER_NAME_LENGTH) {
        printf("Invalid data!\n");
        exit(1);
    }
    strcpy(us->last_name_, last_name);
}

void user_set_username(USER *us, char * username) {
    if (strlen(username) <=0 || strlen(username) > USER_NAME_LENGTH) {
        printf("Invalid data!\n");
        exit(1);
    }
    strcpy(us->username_, username);
}

void user_set_password(USER *us, char * password) {
    if (strlen(password) <=0 || strlen(password) > USER_PASSWORD_LENGTH) {
        printf("Invalid data!\n");
        exit(1);
    }
    strcpy(us->password_, password);
}