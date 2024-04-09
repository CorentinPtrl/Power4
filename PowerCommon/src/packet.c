//
// Created by corentin on 4/8/24.
//

#include <malloc.h>
#include "packet.h"
#include "Handshake.h"

packet_type_t* PacketType__create(
        int buffer_size,
        const char* (*name)(packet_t*),
        int (*id)(packet_t*),
        void (*decode)(packet_t*, power_stream_t*),
        void (*encode)(packet_t*, power_stream_t*),
        void (*handle)(packet_t*),
        void (*destroy)(packet_t*)) {
    packet_type_t* result = (packet_type_t*) malloc(sizeof(packet_type_t));
    result->buffer_size = buffer_size;
    result->name = name;
    result->id = id;
    result->decode = decode;
    result->encode = encode;
    result->handle = handle;
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

void Packet__encode(packet_t* self, power_stream_t* stream) {
    if(self) {
        Power__write_int(stream, self->type->id(self));
        self->type->encode(self, stream);
        Power__flush(stream);
    }
}
void Packet__decode(packet_t* self, power_stream_t* stream) {
    if(self) {
        self->type->decode(self, stream);
    }
}

void Packet__handle(packet_t* self) {
    if(self) {
        self->type->handle(self);
    }
}

void Packet__destroy(packet_t* packet) {
    if (packet) {
        packet->type->destroy(packet);
    }
}

packet_t *Packet__from_stream(power_stream_t *stream) {
    int id = Power__read_int(stream);
    packet_t* result = NULL;
    switch (id) {
        case 1:
            result = Handshake__to_packet(Handshake__create(""));
            break;
        default:
            printf("Unknown packet id: %d\n", id);
            break;
    }
    return result;
}
