//
// Created by corentin on 4/8/24.
//
#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#include <malloc.h>
#include "client.h"
#include "include/Handshake.h"

#define SA struct sockaddr

void Client__init(client_t * self, char* address, int port) {
    self->address = address;
    self->port = port;
}

client_t* Client__create(char* address, int port) {
    client_t* result = (client_t*) malloc(sizeof(client_t));
    Client__init(result, address, port);
    return result;
}

void Client__destroy(client_t* self) {
    if (self) {
        free(self);
    }
}

void Client__handle(client_t* self, power_stream_t* stream)
{
    handshake_t* handshake = Handshake__create("corentin");
    Packet__encode(Handshake__to_packet(handshake), stream);
    Packet__encode(Handshake__to_packet(handshake), stream);
    Packet__encode(Handshake__to_packet(handshake), stream);
    Packet__encode(Handshake__to_packet(handshake), stream);
    Packet__encode(Handshake__to_packet(handshake), stream);
    Packet__encode(Handshake__to_packet(handshake), stream);
    Packet__encode(Handshake__to_packet(handshake), stream);
    Packet__encode(Handshake__to_packet(handshake), stream);
    Packet__encode(Handshake__to_packet(handshake), stream);
    Packet__encode(Handshake__to_packet(handshake), stream);
    Packet__encode(Handshake__to_packet(handshake), stream);
    Packet__encode(Handshake__to_packet(handshake), stream);
    Packet__encode(Handshake__to_packet(handshake), stream);
}

void Client__start(client_t* self) {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(self->address);
    servaddr.sin_port = htons(self->port);

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
    power_stream_t* stream = Power__create(sockfd);
    Client__handle(self, stream);

    close(sockfd);
}