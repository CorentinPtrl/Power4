//
// Created by corentin on 4/8/24.
//

#include "PowerStream.h"

#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

power_stream_t* Power__create(int sd) {
    power_stream_t* result = (power_stream_t*) malloc(sizeof(power_stream_t));
    result->socket_descriptor = sd;
    result->buffer = (char*) malloc(1024);
    result->buffer_capacity = 1024;
    result->offset = 0;
    result->is_connected = 1;
    return result;
}

void Power__destroy(power_stream_t* self) {
    free(self->buffer);
    free(self);
}

int Power__read_int(power_stream_t* self) {
    int result;
    if(read(self->socket_descriptor, &result, sizeof(result)) == 0)
        self->is_connected = 0;
    return result;
}
char Power__read_char(power_stream_t* self) {
    char result;
    read(self->socket_descriptor, &result, sizeof(result));
    return result;
}

char* Power__read_string(power_stream_t* self) {
    int size = Power__read_int(self);
    char* result = (char*) malloc(size + 1);
    if(read(self->socket_descriptor, result, size) == 0)
        self->is_connected = 0;
    result[size] = '\0';
    return result;
}

void Power__write_int(power_stream_t* self, int value) {
    memcpy(self->buffer + self->offset, &value, sizeof(value));
    self->offset += sizeof(value);
}

void Power__write_char(power_stream_t* self, char value) {
    memcpy(self->buffer + self->offset, &value, sizeof(value));
    self->offset += sizeof(value);
}

void Power__write_string(power_stream_t* self, char* value) {
    size_t size = strlen(value);
    Power__write_int(self, size);
    memcpy(self->buffer + self->offset, value, size);
    self->offset += size;
}

void Power__flush(power_stream_t* self) {
    write(self->socket_descriptor, self->buffer, self->offset);
    self->offset = 0;
}

void Power__close(power_stream_t* self) {
    close(self->socket_descriptor);
    self->is_connected = 0;
}