//
// Created by corentin on 4/8/24.
//

#ifndef POWERMATCHMAKING_HANDSHAKE_H
#define POWERMATCHMAKING_HANDSHAKE_H

#include "packet.h"

typedef struct Handshake handshake_t;
packet_t* Handshake__to_packet(handshake_t* handshake);
handshake_t* Handshake__from_packet(packet_t* handshake);
handshake_t* Handshake__create(char* username);
void Handshake__decode(packet_t* handshake, int sd);
void Handshake__encode(packet_t* handshake, int sd);
void Handshake__destroy(packet_t* handshake);
char* Handshake__username(handshake_t* self);

#endif //POWERMATCHMAKING_HANDSHAKE_H
