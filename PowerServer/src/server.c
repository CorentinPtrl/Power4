//
// Created by corentin on 4/8/24.
//

#include <malloc.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include <arpa/inet.h>
#include "server.h"
#include "include/Handshake.h"

#define SA struct sockaddr

void Server__init(server_t * self, char* address, int port) {
    self->address = address;
    self->port = port;
}

server_t* Server__create(char* address, int port) {
    server_t* result = (server_t*) malloc(sizeof(server_t));
    Server__init(result, address, port);
    return result;
}

void Server__destroy(server_t* self) {
    if (self) {
        free(self);
    }
}

void Server__handle_client(server_t* self, power_stream_t* stream)
{
    while (stream->is_connected) {
        packet_t* packet = Packet__from_stream(stream);
        printf("Received packet %s\n", Packet__name(packet));
        Packet__decode(packet, stream);
        Packet__handle(packet);
        Packet__destroy(packet);
    }
}

void Server__start(server_t* self) {
    int sockfd, connfd, len;
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

    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");
    power_stream_t* stream = Power__create(connfd);
    Server__handle_client(self, stream);

    close(sockfd);
}