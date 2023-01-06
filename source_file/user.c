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
    sprintf(dest, "User: %s %s, username:  %s, id: %d, credit: %lf€  \n",us->first_name_,us->last_name_,us->username_,us->id_, us->credit_);
    return dest;
}

void recharge_credit(USER *us, double value) {
    if(value > 0) {
        us->credit_ += value;
        printf("Credit of the user %s %s, was increased by %.2f€ \n",us->first_name_,us->last_name_,value);
        printf("The user %s %s has credit %.2f€\n",us->first_name_,us->last_name_,us->credit_);
    } else {
        printf("Top-up credit must be greater than 0 euros!\n");
    }
}

void print_owned_components(const USER *us) {
    if (us->number_of_owned_components_ <= 0) {
        printf("User does not own any components!\n");
        return;
    }
    char tmpStr[BUFFER];
    printf("List of components of user %s (%s %s) \n", us->username_,us->first_name_,us->last_name_);
    for (int i = 0; i < us->number_of_owned_components_; ++i) {
        printf("%s\n", component_to_string(&us->owned_components_[i], tmpStr));
    }
}

COMPONENT * add_component_to_user(USER *us, COMPONENT *cp) {
    for (int i = 0; i < us->number_of_owned_components_; i++) {
        if (compare_components(cp, &us->owned_components_[i])){
            return &us->owned_components_[i];
        }

    }
    if (us->number_of_owned_components_ >= USER_MAX_COMPONENTS || us->credit_ < cp->price) {
        printf("User %s (%s %s) reached maximum capacity of owned items or does not have enough credit on the account!\n",us->username_,us->first_name_,us->last_name_);
        return NULL;
    }
    us->owned_components_[us->number_of_owned_components_] = * cp;
    us->number_of_owned_components_++;
    us->credit_ -= cp->price;
    printf("User has bought the component\nmanufacturer: %s \ntype: %s\nmodel: %s\nyear: %d\nprice: %.2f €\n\n",
           cp->manufacturer,cp->type,cp->model,cp->year_of_production,cp->price);
    printf("Remaining credit of user %s (%s %s) is %.2f € \n",us->username_,us->first_name_,us->last_name_,us->credit_);
    return &us->owned_components_[us->number_of_owned_components_-1];

}

COMPONENT * remove_component_from_user(USER *us, COMPONENT *cp) {
    if (us->number_of_owned_components_ == 0) {
        printf("User %s (%s %s)does not own any components!\n",us->username_,us->first_name_,us->last_name_);
        return false;
    }
    for(int i = 0; i < us->number_of_owned_components_; i++) {
        if(compare_components(&us->owned_components_[i], cp)){
            *cp = us->owned_components_[i];
            us->owned_components_[i] = us->owned_components_[us->number_of_owned_components_ - 1];
            us->owned_components_[us->number_of_owned_components_ - 1] = us->owned_components_[us->number_of_owned_components_ + 1];
            us->number_of_owned_components_--;
        }
    }
    printf("User %s (%s %s) now does not own this component: %s %s %s\n",us->username_,us->first_name_,us->last_name_,cp->manufacturer,cp->type,cp->model);

    for (int i = 0; i < us->number_of_owned_components_; i++) {
        if (!compare_components(cp, &us->owned_components_[i])){
            return &us->owned_components_[i];
        }
        printf("Component is not registrated\n");
    }
}

COMPONENT * find_owned_component(USER *us) {
    char tmp_manufacturer[CHARACTERS];
    char tmp_type[CHARACTERS];
    char tmp_model[CHARACTERS];
    int tmp_year;
    printf("Manufacturer: \n");
    scanf("%s", tmp_manufacturer);
    printf("Type: \n");
    scanf("%s", tmp_type);
    printf("Model: \n");
    scanf("%s", tmp_model);
    printf("Year: \n");
    scanf("%d", &tmp_year);

    for (int i = 0; i < us->number_of_owned_components_; i++) {
        if(strcmp(us->owned_components_[i].manufacturer, tmp_manufacturer) == 0 && us->owned_components_[i].year_of_production == tmp_year &&
           strcmp(us->owned_components_[i].type, tmp_type) == 0 &&
           strcmp(us->owned_components_[i].model, tmp_model) == 0) {
            return &us->owned_components_[i];
        }
    }
    printf("The user does not own this component! \n");
    return NULL;
}

