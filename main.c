#include <stdio.h>
#include "header_file/socket_definitions.h"
#include "header_file/registration_system.h"

int main() {
    REGISTRATION_SYSTEM reg;
    SOCKET soket;
    create_connection(&soket, 11111);


    return 0;
}
