//
// Created by slavi on 5. 1. 2023.
//
#include "../header_file/computer_component.h"

void component_init(COMPONENT * cp) {
    memset(cp->manufacturer_,0,strlen(cp->manufacturer_));
    memset(cp->type_,0,strlen(cp->type_));
    memset(cp->model_,0,strlen(cp->model_));
    cp->year_of_production_ = 0;
    cp->price_ = 0;
}

_Bool compare_components(const COMPONENT *cp1, const COMPONENT *cp2){
    return strcmp(cp1->manufacturer_,cp2->manufacturer_) == 0 &&
            strcmp(cp1->type_,cp2->type_) == 0 &&
            strcmp(cp1->model_,cp2->model_) == 0 &&
            cp1->price_ == cp2->price_ &&
            cp1->year_of_production_ == cp2->year_of_production_;
}


char* component_to_string(const COMPONENT *cp, char *dest) {
    sprintf(dest, "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|\n"
                  " [Type]:  %s      \n"
                  " [Brand]: %s      \n"
                  " [Name]:  %s      \n"
                  " [Year]:  %d      \n"
                  " [Price]: %.2f€   \n"
                  "|___________________|\n"
            , cp->type_,cp->manufacturer_,cp->model_,cp->year_of_production_, cp->price_);
    return dest;
}

_Bool component_compare_by_price(const COMPONENT *cp1, const COMPONENT *cp2){
    return cp1->price_ > cp2->price_;
}

_Bool component_compare_by_name(const COMPONENT *cp1, const COMPONENT *cp2){
    return strcmp(cp1->model_, cp2->model_) > 0;
}

_Bool component_compare_by_year(const COMPONENT *cp1, const COMPONENT *cp2){
    return cp1->year_of_production_ > cp2->year_of_production_;
}

_Bool component_contains_key(const COMPONENT *cp1, char *keyword){
    char dest[BUFFER] = {0};
    component_to_string(cp1, dest);
    for (int i = 0; dest[i] != '\0'; i++) {
        dest[i] = tolower(dest[i]);
    }
    return strstr(dest, keyword) != NULL;
}