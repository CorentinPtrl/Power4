//
// Created by corentin on 4/8/24.
//

#include <malloc.h>
#include "packet.h"

packet_type_t* PacketType__create(
        int buffer_size,
        const char* (*name)(packet_t*),
        void (*decode)(packet_t*, int),
        void (*encode)(packet_t*, int),
        void (*destroy)(packet_t*)) {
    packet_type_t* result = (packet_type_t*) malloc(sizeof(packet_type_t));
    result->buffer_size = buffer_size;
    result->name = name;
    result->decode = decode;
    result->encode = encode;
    result->destroy = destroy;
    return result;
}

packet_t* Packet__create(packet_type_t* type) {
    int size = sizeof(packet_t) + type->buffer_size;
    packet_t* result = (packet_t*) malloc(size);
    result->type = type;
    return result;
}

packet_type_t* Packet__type(packet_t* self) {
    return self->type;
}

void* Packet__buffer(packet_t* self) {
    return (void*) &(self->buffer_start);
}

const char* Packet__name(packet_t* self) {
    if(self) {
        return self->type->name(self);
    }
    return "Unknown";
}

void Packet__encode(packet_t* self, int sd) {
    if(self) {
        self->type->encode(self, sd);
    }
}
void Packet__decode(packet_t* self, int sd) {
    if(self) {
        self->type->decode(self, sd);
    }
}

void Packet__destroy(packet_t* packet) {
    if (packet) {
        packet->type->destroy(packet);
    }
}