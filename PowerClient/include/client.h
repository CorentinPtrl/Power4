//
// Created by corentin on 4/8/24.
//

#ifndef POWERMATCHMAKING_CLIENT_H
#define POWERMATCHMAKING_CLIENT_H

typedef struct Client {
    char* address;
    int port;
} client_t;

client_t* Client__create(char* address, int port);
void Client__destroy(client_t* self);
void Client__start(client_t* self);

#endif //POWERMATCHMAKING_CLIENT_H
