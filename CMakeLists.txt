cmake_minimum_required(VERSION 3.18)
project(Semestralna_praca_udsp C)

set(CMAKE_C_STANDARD 99)

add_executable(Semestralna_praca_udsp main.c source_file/user.c header_file/user.h header_file/socket_definitions.h source_file/socket_definitions.c source_file/socket_server.c source_file/socket_client.c)
