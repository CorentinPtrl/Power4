//
// Created by corentin on 4/8/24.
//

#ifndef POWERMATCHMAKING_SERVER_H
#define POWERMATCHMAKING_SERVER_H
typedef struct Server {
    char* address;
    int port;
} server_t;

server_t* Server__create(char* address, int port);
void Server__destroy(server_t* self);
void Server__start(server_t* self);

#endif //POWERMATCHMAKING_SERVER_H
