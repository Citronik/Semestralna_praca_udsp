//
// Created by slavi on 5. 1. 2023.
//
#include "../header_file/computer_component.h"

_Bool compare_components(const COMPONENT *cp1, const COMPONENT *cp2){
    if (strcmp(cp1->manufacturer,cp2->manufacturer) == 0){
        return true;
    }
    if (strcmp(cp1->type,cp2->type) == 0 && (cp1->year_of_production == cp2->year_of_production)){
        return true;
    }
    return false;
}


char* component_to_string(const COMPONENT *cp, char *dest) {
    sprintf(dest, "Manufacturer: %s, type: %s, model: %s, year of production: %d, price: %lf€  \n",cp->manufacturer,cp->type,cp->model,cp->year_of_production,cp->price);
    return dest;
}