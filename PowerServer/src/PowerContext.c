//
// Created by corentin on 4/10/24.
//

#include <malloc.h>
#include <stdlib.h>
#include "PowerContext.h"
static PGconn* conn = NULL;
static power_context_t* power_context_instance = NULL;

power_context_t* PowerContext__create(char* connection_string) {
    power_context_t* context = malloc(sizeof(power_context_t));
    context->connection_string = connection_string;
    return context;
}

power_context_t* PowerContext__from_env() {
    char* connection_string = malloc(1024 * sizeof(char));
    sprintf(connection_string,"host=%s port=%s dbname=%s user=%s password=%s", getenv("DB_HOST"),
            getenv("DB_PORT"),
            getenv("DB_NAME"),
            getenv("DB_USER"),
            getenv("DB_PASSWORD"));
    return PowerContext__create(connection_string);
}

power_context_t* PowerContext__instance() {
    if(power_context_instance == NULL) {
        power_context_instance = PowerContext__from_env();
    }
    return power_context_instance;
}

PGconn* PowerContext__connect(power_context_t* self) {
    if(conn != NULL) {
        return conn;
    }
    conn = PQconnectdb(self->connection_string);
    if(PQstatus(conn) != CONNECTION_OK) {
        printf("Connection to database failed: %s", PQerrorMessage(conn));
        exit(1);
    }
    printf("Connected to database\n");
    return conn;
}
void PowerContext__destroy(power_context_t* self) {
    free(self);
}