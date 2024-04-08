//
// Created by corentin on 4/8/24.
//

#include "Handshake.h"
#include <malloc.h>
#include <unistd.h>
#include <string.h>

typedef struct HandshakeData {
    char* username;
} handshake_data_t;

handshake_data_t* Handshake__packet_data(handshake_t* self) {
    packet_t* packet = (packet_t*) self;
    return (handshake_data_t*) Packet__buffer(packet);
}

const char* Handshake__name_override(packet_t* self) {
    return "Handshake";
}

void Handshake__decode_override(packet_t* self, int sd) {
    char buffer[1024];
    int size;
    read(sd, &size, sizeof(size));
    read(sd, buffer, size);
    buffer[size] = '\0';
    handshake_data_t* handshake_data = Handshake__packet_data(Handshake__from_packet(self));
    handshake_data->username = strdup(buffer);
}

void Handshake__encode_override(packet_t* self, int sd) {
    char* username = Handshake__packet_data(Handshake__from_packet(self))->username;
    int size = strlen(username);

    char buffer[1024];

    int offset = 0;

    memcpy(buffer + offset, &size, sizeof(size));
    offset += sizeof(size);

    strcpy(buffer + offset, username);
    offset += strlen(username);
    write(sd, buffer, offset);
}

void Handshake__destroy_override(packet_t* self) {
    free(self);
}

packet_t* Handshake__to_packet(handshake_t* self) {
    return ((packet_t*) self);
}

handshake_t* Handshake__from_packet(packet_t* self) {
    if (!self)  {
        return ((handshake_t*) 0);
    }

    return ((handshake_t*) self);
}

handshake_t* Handshake__create(char* username) {
    packet_type_t* packet_type = PacketType__create(
            sizeof(handshake_data_t),
            Handshake__name_override,
            Handshake__decode_override,
            Handshake__encode_override,
            Handshake__destroy_override
    );

    handshake_t* result = (handshake_t*) Packet__create(packet_type);
    handshake_data_t* handshake_data = Handshake__packet_data(result);
    handshake_data->username = username;
    return result;
}

char* Handshake__username(handshake_t* self) {
    return Handshake__packet_data(self)->username;
}