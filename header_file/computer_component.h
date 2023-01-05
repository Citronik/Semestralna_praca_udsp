//
// Created by slavi on 5. 1. 2023.
//

#ifndef SEMESTRALNA_PRACA_UDSP_COMPUTER_COMPONENT_H
#define SEMESTRALNA_PRACA_UDSP_COMPUTER_COMPONENT_H
#define CHARACTERS 50
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct component {
char manufacturer[CHARACTERS];
char type[CHARACTERS];
char model[CHARACTERS];
unsigned int year_of_production;
double price;
} COMPONENT;
_Bool compare_components(const COMPONENT *cp1, const COMPONENT *cp2);
char* component_to_string(const COMPONENT *cp, char *dest);

#endif //SEMESTRALNA_PRACA_UDSP_COMPUTER_COMPONENT_H
