//
// Created by slavi on 5. 1. 2023.
//

#ifndef SEMESTRALNA_PRACA_UDSP_COMPUTER_COMPONENT_H
#define SEMESTRALNA_PRACA_UDSP_COMPUTER_COMPONENT_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define CHARACTERS 50
#define BUFFER 150
typedef struct component {
    char manufacturer_[CHARACTERS];
    char type_[CHARACTERS];
    char model_[CHARACTERS];
    double price_;
    int year_of_production_;
} COMPONENT;

void component_init(COMPONENT * cp);
_Bool compare_components(const COMPONENT *cp1, const COMPONENT *cp2);
char* component_to_string(const COMPONENT *cp, char *dest);
_Bool component_compare_by_price(const COMPONENT *cp1, const COMPONENT *cp2);
_Bool component_compare_by_name(const COMPONENT *cp1, const COMPONENT *cp2);
_Bool component_compare_by_year(const COMPONENT *cp1, const COMPONENT *cp2);
_Bool component_contains_key(const COMPONENT *cp1, char *keyword);

#endif //SEMESTRALNA_PRACA_UDSP_COMPUTER_COMPONENT_H
