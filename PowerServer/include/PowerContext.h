//
// Created by corentin on 4/10/24.
//

#ifndef POWERMATCHMAKING_POWERCONTEXT_H
#define POWERMATCHMAKING_POWERCONTEXT_H

#include <libpq-fe.h>

typedef struct PowerContext {
    char* connection_string;
} power_context_t;

power_context_t* PowerContext__instance();
PGconn* PowerContext__connect(power_context_t* self);
void PowerContext__destroy(power_context_t* self);

#endif //POWERMATCHMAKING_POWERCONTEXT_H
