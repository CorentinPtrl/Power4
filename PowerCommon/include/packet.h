//
// Created by corentin on 4/8/24.
//

#ifndef POWERMATCHMAKING_PACKET_H
#define POWERMATCHMAKING_PACKET_H

#include "PowerStream.h"

typedef struct PacketType packet_type_t;
typedef struct Packet {
    packet_type_t* type;
    char buffer_start;
} packet_t;

typedef struct PacketType {
    int buffer_size;
    const char* (*name)(packet_t*);
    const int (*id)(packet_t*);
    void (*decode)(packet_t*, power_stream_t*);
    void (*encode)(packet_t*, power_stream_t*);
    void (*destroy)(packet_t*);
} packet_type_t;

packet_type_t* PacketType__create(
        int buffer_size,
        const char* (*name)(packet_t*),
        const int (*id)(packet_t*),
        void (*decode)(packet_t*, power_stream_t*),
        void (*encode)(packet_t*, power_stream_t*),
        void (*destroy)(packet_t*));

packet_t* Packet__create(packet_type_t* type);
packet_type_t* Packet__type(packet_t* self);
void* Packet__buffer(packet_t* self);
const char* Packet__name(packet_t* self);
void Packet__encode(packet_t* self, power_stream_t* stream);
void Packet__decode(packet_t* self, power_stream_t* stream);
packet_t *Packet__from_stream(power_stream_t *stream);
void Packet__destroy(packet_t* self);

#endif //POWERMATCHMAKING_PACKET_H
