cmake_minimum_required(VERSION 3.18)
project(Semestralna_praca_udsp C)

set(CMAKE_C_STANDARD 99)

add_executable(Semestralna_praca_udsp main.c header_file/registration_system.h header_file/user.h source_file/user.c header_file/socket_definitions.h
        source_file/socket_definitions.c source_file/socket_client.c source_file/socket_server.c header_file/socket.h header_file/token.h source_file/token.c header_file/client_app.h
        source_file/client_app.c header_file/computer_component.h source_file/computer_component.c header_file/registration_system_responses.h source_file/registration_system_responses.c)

target_link_libraries(Semestralna_praca_udsp pthread)