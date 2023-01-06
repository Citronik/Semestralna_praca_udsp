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
    printf("User: %s %s , username: %s, password: %s, ID: %d credit: %lf €, has been added to the registration system!\n",
           us->first_name_,us->last_name_,us->username_,us->password_,us->id_, us->credit_);
    us->number_of_owned_components_ = 0;
    return &rs->users_[rs->number_of_users_-1];

}

COMPONENT* add_component(REGISTRATION_SYSTEM *rs, COMPONENT *cp) {
    if (rs->number_of_components >= CAPACITY) {
        printf("Maximum capacity has been reached!\n");
        return NULL;
    }
    for (int i = 0; i < rs->number_of_components; i++) {
        if (compare_components(cp, &rs->components_[i])){
            return &rs->components_[i];
        }
    }
    rs->components_[rs->number_of_components] = * cp;
    rs->number_of_users_++;
    printf("Adding the component: \n");
    printf("Manufacturer: %s , type: %s, model: %s, year: %d, price: %lf\n",
           cp->manufacturer_,cp->type_,cp->model_,cp->year_of_production_,cp->price_);
    return &rs->components_[rs->number_of_components-1];
}

COMPONENT* remove_component(REGISTRATION_SYSTEM *rs, COMPONENT *cp){
    if (rs->number_of_components == 0) {
        printf("There are not any computer components in the system!\n");
        return false;
    }

    for(int i = 0; i < rs->number_of_components; i++) {
        if(compare_components(&rs->components_[i], cp)){
            *cp = rs->components_[i];
            rs->components_[i] = rs->components_[rs->number_of_components - 1];
            rs->components_[rs->number_of_components - 1] = rs->components_[rs->number_of_components + 1];
            rs->number_of_components--;
        }
    }
    printf("Removing the component: \n");
    printf("Manufacturer: %s , type: %s, model: %s, year: %d, price: %lf\n",
           cp->manufacturer_,cp->type_,cp->model_,cp->year_of_production_,cp->price_);

    for (int i = 0; i < rs->number_of_users_; i++) {
        if (!compare_components(cp, &rs->components_[i])){
            return &rs->components_[i];
        }
        printf("Component is not in the registration system\n");
    }
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
    printf("User: %s %s , username: %s, password: %s, ID: %d credit: %lf €, has been removed from the registration system!\n",
           us->first_name_,us->last_name_,us->username_,us->password_,us->id_, us->credit_);

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

void print_components(const REGISTRATION_SYSTEM *rs) {
    if (rs->number_of_components <= 0) {
        printf("There are not any users in the system!\n");
    }
    char tmpStr[BUFFER];
    for (int i = 0; i < rs->number_of_components; i++) {
        component_to_string(&rs->components_[i], tmpStr);
        printf("%s", tmpStr);
    }
}

_Bool registrate_user(REGISTRATION_SYSTEM *rs) {
    USER tmp_user;
    char tmp_first_name[USER_NAME_LENGTH];
    char tmp_last_name[USER_NAME_LENGTH];
    char tmp_username[USER_NAME_LENGTH];
    char tmp_password[USER_PASSWORD_LENGTH];
    int tmp_id;
    double tmp_credit;

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

    printf("Enter the password: \n");
    scanf("%s",tmp_password);
    strcpy(tmp_user.password_, tmp_password);

    printf("Enter the ID of user: \n");
    scanf("%d",&tmp_id);
    tmp_user.id_ = tmp_id;

    printf("Set default credit for the user: \n");
    scanf("%lf",&tmp_credit);
    tmp_user.id_ = tmp_credit;

    if(add_user(rs,&tmp_user)){
        return true;
    }
    return false;
}

_Bool registrate_component(REGISTRATION_SYSTEM *rs) {
    COMPONENT tmp_component;
    char tmp_manufacturer[CHARACTERS];
    char tmp_type[CHARACTERS];
    char tmp_model[CHARACTERS];
    int tmp_year;
    double tmp_price;

    printf("Registration of the component...\n");

    printf("Enter a manufacturer:\n");
    scanf("%s",tmp_manufacturer);
    strcpy(tmp_component.manufacturer_, tmp_manufacturer);

    printf("Enter a type of component: \n");
    scanf("%s",tmp_type);
    strcpy(tmp_component.type_, tmp_type);

    printf("Enter a model: \n");
    scanf("%s",tmp_model);
    strcpy(tmp_component.model_, tmp_model);

    printf("Enter the year of production: \n");
    scanf("%d",&tmp_year);
    tmp_component.year_of_production_ = tmp_year;


    printf("Set price for the component: \n");
    scanf("%lf",&tmp_price);
    tmp_component.price_ = tmp_price;

    if(add_component(rs,&tmp_component)){
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

COMPONENT * find_component(REGISTRATION_SYSTEM  * rs) {
    char tmp_manufacturer[CHARACTERS];
    char tmp_type[CHARACTERS];
    char tmp_model[CHARACTERS];
    int tmp_year;

    printf("Finding the component...\n");

    printf("Manufacturer:\n");
    scanf("%s",tmp_manufacturer);

    printf("Type of hardware: \n");
    scanf("%s",tmp_type);

    printf("Model: \n");
    scanf("%s",tmp_model);

    printf("Year of production: \n");
    scanf("%d",&tmp_year);

    for (int i = 0; i < rs->number_of_users_; i++) {
        if(strcmp(rs->components_[i].manufacturer_, tmp_manufacturer) == 0 && rs->components_[i].year_of_production_ == tmp_year &&
           strcmp(rs->components_[i].type_, tmp_type) == 0 &&
           strcmp(rs->components_[i].model_, tmp_model) == 0) {
            return &rs->components_[i];

        }
    }
    printf("This component is not in the system! \n");
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

void buy_item_for_user(REGISTRATION_SYSTEM *rs,USER *us,COMPONENT *cp){
    int index = 0;
    for (int i = 0; i < rs->number_of_users_; i++) {
        if (compare_users(us, &rs->users_[i])) {
            index = i;
        }
    }
    add_component_to_user(&rs->users_[index], cp);
    rs->sales += cp->price_;
}


void remove_item_from_user(REGISTRATION_SYSTEM *rs,USER *us,COMPONENT *cp){
    int index = 0;
    for (int i = 0; i < rs->number_of_users_; i++) {
        if (compare_users(us, &rs->users_[i])) {
            index = i;
        }
    }
    remove_component_from_user(&rs->users_[index], cp);
}

void charge_credit_for_user(REGISTRATION_SYSTEM *rs, USER *us){
    int index = 0;
    for (int i = 0; i < rs->number_of_users_; i++) {
        if (compare_users(us, &rs->users_[i])) {
            index = i;
        }
    }
    double tmp;
    printf("Select value of credit which you want to charge to user %s (%s %s)\n", us->username_, us->first_name_,us->last_name_);
    scanf("%lf", &tmp);
    recharge_credit(&rs->users_[index], tmp);
}


void * registration_system_start(void * data) {
    DATA * datas = (DATA *)data;
    TOKEN * token = calloc(1,sizeof (TOKEN));
    token_init(token);
    system_set_message(token, token->response_status_);
    send_message(datas, token);
    read_message(datas, token);
}