//
// Created by slavi on 4. 1. 2023.
//
#ifndef SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_H
#define SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_H

/*#ifdef	__cplusplus
extern "C" {
#endif*/

#include "user.h"
#include "token.h"
#include "socket_definitions.h"
#include "../header_file/registration_system_responses.h"

#define CAPACITY 30
#define BUFFER 150 // we use this for reading from file
typedef struct registration_system {
    USER users_[CAPACITY];
    COMPONENT components_[CAPACITY];
    TOKEN * active_users_[CAPACITY];
    unsigned int number_of_components;
    unsigned int number_of_users_;
    unsigned int number_of_active_users_;
    double sales;
} REGISTRATION_SYSTEM;

REGISTRATION_SYSTEM * reg_sys_;

pthread_mutex_t mut_component_ = PTHREAD_MUTEX_INITIALIZER
, mut_user_ = PTHREAD_MUTEX_INITIALIZER
, mut_token_ = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond_us_occupied_ = PTHREAD_COND_INITIALIZER
, cond_us_open_ = PTHREAD_COND_INITIALIZER
, cond_com_occupied_=PTHREAD_COND_INITIALIZER
, cond_com_open_=PTHREAD_COND_INITIALIZER
, cond_tok_occupied_=PTHREAD_COND_INITIALIZER
, cond_tok_open_=PTHREAD_COND_INITIALIZER;

void registration_system_init(REGISTRATION_SYSTEM *rs);
void * registration_system_start(void * data);
USER* add_user(REGISTRATION_SYSTEM *rs, USER *us, TOKEN *token); //adding existing user
USER* remove_user(REGISTRATION_SYSTEM *rs, USER *us); //removing existing user (only from reg.system)
void print_users(const REGISTRATION_SYSTEM *rs); //prints users in the registration system
void print_components(const REGISTRATION_SYSTEM *rs);
_Bool registrate_user(REGISTRATION_SYSTEM *rs); //create new user
_Bool delete_user(REGISTRATION_SYSTEM *rs); //complete delete of user
USER * find_user(REGISTRATION_SYSTEM *rs, int user_id); //finds the user in the registration system
COMPONENT * find_component(REGISTRATION_SYSTEM  *rs, int component_id);
void reg_sys_to_string(REGISTRATION_SYSTEM *rs); // prints details about the registration system
COMPONENT* add_component(REGISTRATION_SYSTEM *rs, COMPONENT *cp); //adding component
COMPONENT* remove_component(REGISTRATION_SYSTEM *rs, COMPONENT *cp);  //removing component
_Bool registrate_component(REGISTRATION_SYSTEM *rs);
void buy_item_for_user(REGISTRATION_SYSTEM *rs,USER *us,COMPONENT *cp);
void remove_item_from_user(REGISTRATION_SYSTEM *rs,USER *us,COMPONENT *cp);
void charge_credit_for_user(REGISTRATION_SYSTEM *rs, USER *us);
_Bool load_users_from_file(REGISTRATION_SYSTEM *rs, const char *file_name);
_Bool load_components_from_file(REGISTRATION_SYSTEM *rs, const char *file_name);
void registration_system_login(DATA *data, TOKEN *token);
TOKEN *  registration_system_authentificate(REGISTRATION_SYSTEM *reg, USER *user);
USER * registration_system_find_by_username_pass(REGISTRATION_SYSTEM *reg, char * username, char * pass);
void * server_handle_new_users(void * datas);
void registration_system_registration(DATA *data, TOKEN *token);
void registration_system_print_all_components(REGISTRATION_SYSTEM * reg, DATA *data, TOKEN *token);
void registration_system_logout_user(REGISTRATION_SYSTEM * reg, DATA *data, TOKEN *token);
void registration_system_deauthorize(REGISTRATION_SYSTEM * reg, DATA *data, TOKEN *token);
void registration_system_sort_components(REGISTRATION_SYSTEM * reg, DATA *data, TOKEN *token);
void registration_system_find_components(REGISTRATION_SYSTEM * reg, DATA *data, TOKEN *token);
void registration_system_print_user_components(REGISTRATION_SYSTEM * reg, DATA *data, TOKEN *token);
void write_user_to_file(USER * us, const char* file_name);
void write_component_to_file(COMPONENT * cp, const char* file_name);
void registration_system_buy_component(REGISTRATION_SYSTEM * reg, DATA *data, TOKEN *token);
_Bool registration_system_return_component(REGISTRATION_SYSTEM * reg, DATA *data, TOKEN *token);
//COMPONENT * registration_system_find_components_with_keyword(REGISTRATION_SYSTEM *reg, char * keyword);
/*
#ifdef	__cplusplus
}
#endif
*/

void registration_system_init(REGISTRATION_SYSTEM *rs){
    rs->number_of_users_ = 0;
    rs->number_of_components = 0;
    rs->number_of_active_users_ = 0;
    memset(rs->users_, 0, CAPACITY);
    memset(rs->components_, 0, CAPACITY);
    memset(rs->active_users_, 0, CAPACITY);
    rs->sales = 0;
    load_users_from_file(rs, "../source_file/users");
    load_components_from_file(rs, "../source_file/components");

}

USER* add_user(REGISTRATION_SYSTEM *rs, USER *us, TOKEN *token) {
    if (rs->number_of_users_ >= CAPACITY) {
        system_set_message(token, 4);
        printf("Maximum capacity has been reached!\n");
        return NULL;
    }
    for (int i = 0; i < rs->number_of_users_; i++) {
        if (compare_users(us, &rs->users_[i])){
            system_set_message(token, 5);
            printf("User already in system!\n");
            return &rs->users_[i];
        }
    }
    us->id_ = 1000000 + rand() % (10000000-1000000);
    rs->users_[rs->number_of_users_] = * us;
    rs->number_of_users_++;
    printf("User: %s %s , username: %s, password: %s, ID: %d credit: %.2f €, has been added to the registration system!\n",
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
    rs->number_of_components++;
    printf("Adding the component: \n");
    printf("Manufacturer: %s , type: %s, model: %s, year: %d, price: %.2f\n",
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
        printf("There are not any components in the system!\n");
    }
    char tmpStr[BUFFER];
    for (int i = 0; i < rs->number_of_components; i++) {
        component_to_string(&rs->components_[i], tmpStr);
        printf("%s", tmpStr);
    }
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

USER * find_user(REGISTRATION_SYSTEM *rs, int user_id) {
    for (int i = 0; i < rs->number_of_users_; ++i) {
        if (rs->users_[i].id_ == user_id) {
            printf("[+]USER: %d FOUND\n", user_id);
            return &rs->users_[i];
        }
    }
    printf("[-]USER: %d NOT FOUND\n", user_id);
    return NULL;
}

COMPONENT * find_component(REGISTRATION_SYSTEM  * rs, int component_id) {
    if (component_id < 0 || component_id >= rs->number_of_components){
        printf("[-]COMPONENT: %d NOT FOUND\n", component_id);
        return NULL;
    }
    printf("[+]COMPONENT: %d FOUND\n", component_id);
    return &rs->components_[component_id];
}


_Bool delete_user(REGISTRATION_SYSTEM *rs) {
    USER *tmp_user = find_user(rs, 100);
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


/*void remove_item_from_user(REGISTRATION_SYSTEM *rs,USER *us,COMPONENT *cp){
    int index = 0;
    for (int i = 0; i < rs->number_of_users_; i++) {
        if (compare_users(us, &rs->users_[i])) {
            index = i;
        }
    }
    remove_component_from_user(&rs->users_[index], cp);
}*/

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


_Bool load_users_from_file(REGISTRATION_SYSTEM *rs, const char *file_name) {
    FILE * f = fopen(file_name, "rt");
    if (f == NULL){
        perror("The file does not exist!\n");
        false;
    }

    char line[BUFFER];
    while (!feof(f) && rs->number_of_components != CAPACITY){
        if(fgets(line,BUFFER,f)>0){
            USER tmp_user = {0};
            char * p1 = strchr(line, ' ');
            strncpy(tmp_user.first_name_, line, p1 - line);
            tmp_user.first_name_[p1-line] = '\0';
            p1++;
            char * p2 = strchr(p1, ' ');
            strncpy(tmp_user.last_name_, p1, p2 - p1);
            tmp_user.last_name_[p2-p1] = '\0';
            p2++;
            char * p3 = strchr(p2, ' ');
            strncpy(tmp_user.username_, p2, p3 - p2);
            tmp_user.username_[p3-p2] = '\0';
            p3++;
            char * p4 = strchr(p3, ' ');
            strncpy(tmp_user.password_,p3, p4 - p3);
            tmp_user.password_[p4-p3] = '\0';
            tmp_user.id_ = (int)atoi(p4);
            char * p5 = strchr(p4, ' ');
            tmp_user.credit_ = atof(p5);
            add_user(rs, &tmp_user, NULL);
        }
    }
    fclose(f);
    return true;
}

_Bool load_components_from_file(REGISTRATION_SYSTEM *rs, const char *file_name) {
    FILE * f = fopen(file_name, "rt");
    if (f == NULL){
        perror("The file does not exist!\n");
        false;
    }

    char line[BUFFER];
    while (!feof(f) && rs->number_of_components != CAPACITY){
        if(fgets(line,BUFFER,f)>0){
            COMPONENT tmp_component = {0};
            char * p1 = strchr(line, ' ');
            strncpy(tmp_component.manufacturer_, line, p1 - line);
            tmp_component.manufacturer_[p1-line] = '\0';
            p1++;
            char * p2 = strchr(p1, ' ');
            strncpy(tmp_component.type_, p1, p2 - p1);
            tmp_component.type_[p2-p1] = '\0';
            p2++;
            char * p3 = strchr(p2, ' ');
            strncpy(tmp_component.model_, p2, p3 - p2);
            tmp_component.model_[p3-p2] = '\0';
            tmp_component.year_of_production_ = (int)atoi(p3);
            p3++;
            char * p4 = strchr(p3, ' ');
            tmp_component.price_ = atof(p4);
            add_component(rs, &tmp_component);
        }
    }
    fclose(f);
    return true;
}

void write_user_to_file(USER * us, const char* file_name) {
    FILE * f = fopen(file_name, "a");
    if (f == NULL){
        perror("The file does not exist!\n");
        false;
    }
    fprintf(f,"%s %s %s %s %d %2.f",us->first_name_,us->last_name_,us->username_,us->password_,us->id_,us->credit_);
    fclose(f);
}
void write_component_to_file(COMPONENT * cp, const char* file_name) {
    FILE * f = fopen(file_name, "a");
    if (f == NULL){
        perror("The file does not exist!\n");
        false;
    }
    fprintf(f,"%s %s %s %d %2.f",cp->manufacturer_,cp->type_,cp->model_,cp->year_of_production_,cp->price_);
    fclose(f);
}



USER * registration_system_find_by_username_pass(REGISTRATION_SYSTEM *reg, char * username, char * pass){
    if (strlen(username) <= 0 || strlen(pass) <= 0){
        printf("[-]Wrong data!\n");
        return NULL;
    }
    for (int i = 0; i < reg->number_of_users_; ++i) {
        if (strcmp(username, reg->users_[i].username_) == 0 & strcmp(pass, reg->users_[i].password_) == 0){
            printf("[+]User found %d\n", reg->users_[i].id_);
            return &reg->users_[i];
        }
    }
    printf("[-]Cannot find the User\n");
    return NULL;
}

TOKEN * registration_system_authentificate(REGISTRATION_SYSTEM * reg, USER * user) {
    USER * user_found = registration_system_find_by_username_pass(reg, user->username_, user->password_);
    if (user_found == NULL){
        return NULL;
    }
    TOKEN * active_user_token = NULL;
    for (int i = 0; i < reg->number_of_active_users_; ++i) {
        if (user_found->id_ == reg->active_users_[i]->user_id_) {
            active_user_token = reg->active_users_[i];
            system_set_message(active_user_token, 2);
            break;
        }
    }
    if (active_user_token == NULL) {
        active_user_token = (TOKEN * ) malloc(sizeof(TOKEN));
        token_init(active_user_token);
        active_user_token->user_id_ = user_found->id_;
        system_set_message(active_user_token, 2);
    }
    memcpy(user, user_found, sizeof(USER));
    return active_user_token;
}

void registration_system_login(DATA *data, TOKEN *token) {
    USER * user = (USER * ) malloc(sizeof(USER));
    user_init(user);
    token_login_details(user, token);
    TOKEN * tmp_token = registration_system_authentificate(reg_sys_, user);
    if (tmp_token == NULL) {
        printf("[-]Unable to authorize\n");
        system_set_message(token, 404);
        user_init(user);

    } else {
        memcpy(token, tmp_token, sizeof(TOKEN));
        printf("user id: %d - %s \n", user->id_, user->first_name_);
    }
    send_message(data, token);
    printf("user id: %d - %s \n", user->id_, user->first_name_);
    data->state = write(data->socket, user, sizeof (USER));
    free(user);
    user = NULL;
}

void registration_system_registration(DATA *data, TOKEN *token){
    printf("%s\n", token->content_);
    USER * user = malloc(sizeof(USER));
    user_init(user);
    data->state = read(data->socket, user, sizeof (USER));
    USER * tmp_user = add_user(reg_sys_, user, token);
    data->state = write(data->socket, tmp_user, sizeof (USER));
    system_set_message(token, 6);
    TOKEN * active_token = registration_system_authentificate(reg_sys_, tmp_user);
    send_message(data, active_token);
}

void registration_system_print_all_components(REGISTRATION_SYSTEM * reg, DATA *data, TOKEN *token){
    int index_of_component = 0;
    printf("Number of components %d\n", reg->number_of_components);
    system_set_message(token, SYSTEM_RESPONSE_AUTH_SUC);
    //pthread_mutex_lock(&mut_component_);
    while (index_of_component < reg->number_of_components) {
        token->response_status_ = reg->number_of_components;
        token->service_type_ = index_of_component;
        component_to_string(&reg->components_[index_of_component], token->content_);
        send_message(data, token);
        ++index_of_component;
    }
    //pthread_mutex_unlock(&mut_component_);
    token->service_type_ = index_of_component;
    strcpy(token->response_, "END");
    send_message(data, token);
    printf("All components are printed\n");
}

void registration_system_deauthorize(REGISTRATION_SYSTEM * reg, DATA *data, TOKEN *token){
    TOKEN * tmp_token = NULL;
    int index = RAND_MAX;
    for (int i = 0; i < reg->number_of_active_users_; ++i) {
        if (token_compare(reg->active_users_[i], token)){
            tmp_token = reg->active_users_[i];
            index = i;
        }
    }
    if (tmp_token == NULL){
        system_set_message(token, 404);
        send_message(data, token);
        return;
    }
    token->user_id_ = 0;
    if (index < reg->number_of_active_users_) {
        printf("Editing active users\n");
        memcpy(tmp_token,tmp_token+sizeof(TOKEN),reg->number_of_active_users_-index* sizeof(TOKEN));
    }
    --reg->number_of_active_users_;
    system_set_message(token, SYSTEM_RESPONSE_USR_LOGOUT);
    send_message(data, token);
}

void registration_system_logout_user(REGISTRATION_SYSTEM * reg, DATA * data, TOKEN * token){
    USER tmp_user;
    data->state = read(data->socket, &tmp_user, sizeof (USER));
    registration_system_deauthorize(reg, data, token);
    USER new_user = {0};
    printf("Sending new user\n");
    data->state = write(data->socket, &new_user, sizeof (USER));
    system_set_message(token, SYSTEM_RESPONSE_USR_LOGOUT);
    send_message(data, token);
}

void registration_system_sort_components(REGISTRATION_SYSTEM * reg, DATA *data, TOKEN *token){
    _Bool (*function_to_sort_components)(const COMPONENT *, const COMPONENT *);
    switch (token->response_status_) {
        case 1:
            function_to_sort_components = component_compare_by_price;
            break;
        case 2:
            function_to_sort_components = component_compare_by_name;
            break;
        case 3:
            function_to_sort_components = component_compare_by_year;
            break;
    }
    int min_index = 0;
    for(int i = 0; i < reg->number_of_components - 1; i++) {
        min_index = i;
        for(int j = i + 1; j < reg->number_of_components; j++) {
            if(function_to_sort_components(&reg->components_[i], &reg->components_[j])) {
                min_index = j;
            }
        }
        if(min_index != i)
        {
            COMPONENT temp;
            memcpy(&temp, &reg->components_[i], sizeof(COMPONENT));
            memcpy(&reg->components_[i], &reg->components_[min_index], sizeof(COMPONENT));
            memcpy(&reg->components_[min_index], &temp, sizeof(COMPONENT));
        }
    }
}

void registration_system_find_components(REGISTRATION_SYSTEM * reg, DATA *data, TOKEN *token){
    //registration_system_find_components_with_keyword(reg, token->content_);
    int number_of_comp = 0;
    COMPONENT *tmp_components[CAPACITY];
    for (int i = 0; i < reg->number_of_components; ++i) {
        if (component_contains_key(&reg->components_[i], token->content_)){
            tmp_components[number_of_comp] = &reg->components_[i];
            ++number_of_comp;
        }
    }
    int index_of_component = 0;
    printf("Number of searched components: %d\n", number_of_comp);
    system_set_message(token, SYSTEM_RESPONSE_AUTH_SUC);
    //pthread_mutex_lock(&mut_component_);
    while (index_of_component < number_of_comp) {
        token->response_status_ = number_of_comp;
        token->service_type_ = index_of_component;
        component_to_string(tmp_components[index_of_component], token->content_);
        send_message(data, token);
        ++index_of_component;
    }
    //pthread_mutex_unlock(&mut_component_);
    token->service_type_ = index_of_component;
    strcpy(token->response_, "END");
    send_message(data, token);
    printf("All searched components are printed\n");
}

void registration_system_print_user_components(REGISTRATION_SYSTEM * reg, DATA *data, TOKEN *token){
    USER * tmp_user = find_user(reg, token->user_id_);
    system_set_message(token, SYSTEM_RESPONSE_AUTH_SUC);
    if (tmp_user == NULL) {
        system_set_message(token, SYSTEM_RESPONSE_UNAUTH);
    }
    send_message(data,token);
    if (token->response_status_ == SYSTEM_RESPONSE_SUCCESSFUL){
        data->state = write(data->socket, tmp_user, sizeof (USER));
    }

}

void registration_system_buy_component(REGISTRATION_SYSTEM * reg, DATA *data, TOKEN *token){
    USER * tmp_user = find_user(reg, token->user_id_);
    int component_id = token->response_status_;
    system_set_message(token, SYSTEM_RESPONSE_SUC_OPERATION);
    if (tmp_user == NULL){
        printf("[-]USER: %d NOT FOUND!\n", token->user_id_);
        system_set_message(token, SYSTEM_RESPONSE_USER_NOT_FOUND);
    }
    COMPONENT * tmp_component = find_component(reg, component_id);
    if (tmp_component == NULL){
        printf("[-]COMPO: %d NOT FOUND!\n", token->user_id_);
        system_set_message(token, SYSTEM_RESPONSE_ITEM_NOT_FOUND);
    }
    COMPONENT * added_component = NULL;
    if (token->response_status_ != SYSTEM_RESPONSE_UNAUTH){
        added_component = add_component_to_user(tmp_user, tmp_component);
        system_set_message(token, SYSTEM_RESPONSE_SUC_OPERATION);
    }
    if (token->response_status_ == SYSTEM_RESPONSE_UNAUTH) {
        system_set_message(token, SYSTEM_RESPONSE_UNSUC_OPERATION);
    }
    send_message(data, token);
    if (added_component != NULL){
        printf("[+]COMPO: %d SUCCESFULLY ADDED TO USER: %d!\n"
                    , token->response_status_, token->user_id_);
            data->state = write(data->socket, tmp_user, sizeof (USER));
    }
}

_Bool registration_system_return_component(REGISTRATION_SYSTEM * reg, DATA *data, TOKEN *token){
    USER * tmp_user = find_user(reg, token->user_id_);
    int component_id = token->response_status_;
    system_set_message(token, SYSTEM_RESPONSE_SUC_OPERATION);
    if (tmp_user == NULL) {
        system_set_message(token, SYSTEM_RESPONSE_USER_NOT_FOUND);
        send_message(data, token);
        return false;
    }
    COMPONENT * removed_component = remove_component_from_user(tmp_user, component_id);
    if (removed_component == NULL){
        system_set_message(token, SYSTEM_RESPONSE_ITEM_NOT_FOUND);
        send_message(data, token);
        return false;
    }
    send_message(data, token);
    data->state = write(data->socket, tmp_user, sizeof (USER));
    return true;
}

void * registration_system_start(void * data) {
    DATA * datas = (DATA *)data;
    TOKEN * token = calloc(1,sizeof (TOKEN));
    token_init(token);
    system_set_message(token, token->response_status_);
    send_message(datas, token);
    do {
        printf("waiting for client\n");
        read_message(datas, token);
        switch (token->service_type_) {
            case 1:
                //registration create user account and after registration login created user
                printf("[+]Registration proceed\n");
                registration_system_registration(datas, token);
                break;
            case 2:
                //login user will send username and password system will try to ensure user exist and then login to system
                printf("[+]Login proceed\n");
                registration_system_login(datas, token);
                break;
            case 3:
                //DISPLAY COMPONENTS
                printf("[+]DISPLAYING ALL COMPONENTS\n");
                registration_system_print_all_components(reg_sys_, datas, token);
                break;
            case 4:
                //SORT COMPONENTS
                printf("[+]SORTING COMPONENTS\n");
                registration_system_sort_components(reg_sys_, datas, token);
                break;
            case 5:
                //BUY COMPONENT
                printf("[+]BUYING COMPONENT\n");
                registration_system_buy_component(reg_sys_, datas, token);
                break;
            case 6:
                //RETURN COMPONENT
                printf("[+]RETURNING COMPONENT\n");
                registration_system_return_component(reg_sys_, datas, token);
                break;
            case 7:
                //DISPLAY YOUR COMPONENTS
                printf("[+]DISPLAYING YOUR COMPONENTS\n");
                registration_system_print_user_components(reg_sys_, datas, token);
                break;
            case 8:
                //FIND COMPONENTS
                printf("[+]SEARCHING FOR COMPONENTS\n");
                registration_system_find_components(reg_sys_, datas, token);
                break;
            case 9:
                //LOGOUT
                printf("[+]LOGOUT USER\n");
                registration_system_logout_user(reg_sys_, datas, token);
                break;
            case 10:
                //TOP UP CREDIT
                printf("[+]TOP UP CREDIT\n");

                break;
            case 0:
                //EXIT
                printf("[+]USER ENDING SESSION\n");
                break;
            default:
                //warning message
                printf("[+]Wrong key\n");
                break;
        }
    } while(token_is_active(token));

    free(token);
    token = NULL;
}

void * server_handle_new_users(void * datas) {
    int number_of_users = 0;
    SOCKET * soket = (SOCKET* )datas;
    pthread_t thread[MAX_POCET_POUZIVATELOV];
    while (number_of_users <= MAX_POCET_POUZIVATELOV) {
        soket->newsockfd = accept(soket->sockfd, (struct sockaddr*)&soket->cli_addr, &soket->cli_len);
        if (soket->newsockfd < 0)
        {
            perror("[-]ERROR on accept");
            //exit(1);
        }
        DATA data;
        data.socket = soket->newsockfd;
        pthread_create(&thread[number_of_users], NULL, registration_system_start, (void *)&data);
        printf("[+]User succesfully connected: %d \n", data.socket);
        ++number_of_users;
    }
}

#endif //SEMESTRALNA_PRACA_UDSP_REGISTRATION_SYSTEM_H
