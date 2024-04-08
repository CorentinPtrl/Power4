//
// Created by corentin on 4/8/24.
//

#ifndef POWERMATCHMAKING_POWERSTREAM_H
#define POWERMATCHMAKING_POWERSTREAM_H
typedef struct PowerStream {
    int socket_descriptor;
    char* buffer;
    int buffer_capacity;
    int offset;
} power_stream_t;

power_stream_t* Power__create(int sd);
void Power__destroy(power_stream_t* self);
int Power__read_int(power_stream_t* self);
char Power__read_char(power_stream_t* self);
char* Power__read_string(power_stream_t* self);
void Power__write_int(power_stream_t* self, int value);
void Power__write_char(power_stream_t* self, char value);
void Power__write_string(power_stream_t* self, char* value);
void Power__flush(power_stream_t* self);
#endif //POWERMATCHMAKING_POWERSTREAM_H
