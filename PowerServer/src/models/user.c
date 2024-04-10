//
// Created by corentin on 4/10/24.
//

#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "models/user.h"
#include "PowerContext.h"
#include "utils.h"

user_t* User__create(int id, char* username, char* password, char* email) {
    user_t* user = malloc(sizeof(user_t));
    user->id = id;
    user->username = username;
    user->password = password;
    user->email = email;
    return user;
}

user_t* User__get(int id) {
    PGconn* power_instance = PowerContext__connect(PowerContext__instance());
    char* params[1];
    char* buffer = malloc(10 * sizeof(char));
    itoa(id, buffer);
    params[0] = buffer;
    PGresult* res = PQexecParams(power_instance, "SELECT * FROM users WHERE id = $1", 1, NULL, params, NULL, NULL, 0);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        return NULL;
    }
    user_t* user = User__create(atoi(PQgetvalue(res, 0, 0)), PQgetvalue(res, 0, 1), PQgetvalue(res, 0, 2), PQgetvalue(res, 0, 3));
    return user;
}

int User__save(user_t* self) {
    PGconn* power_instance = PowerContext__connect(PowerContext__instance());
    char* buffer = malloc(10 * sizeof(char));
    itoa(self->id, buffer);
    char* values[4] = {buffer, self->username, self->password, self->email};
    PGresult* res = PQexecParams(power_instance, "INSERT INTO users (id, username, password, email) VALUES ($1, $2, $3, $4)", 4, NULL, values, NULL, NULL, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        return 1;
    }
    return 0;
}
void User__delete(user_t* self) {
    PGconn* power_instance = PowerContext__connect(PowerContext__instance());
    printf("Deleting user %d\n", self->id);
    char* params[1];
    char* buffer = malloc(10 * sizeof(char));
    itoa(self->id, buffer);
    params[0] = buffer;
    PGresult* res = PQexecParams(power_instance, "DELETE FROM users WHERE id = $1", 1, NULL, params, NULL, NULL, 0);
}

user_t** User__all() {
    PGconn* power_instance = PowerContext__connect(PowerContext__instance());
    PGresult* res = PQexec(power_instance, "SELECT * FROM users");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        return NULL;
    }
    printf("Number of users: %d\n", PQntuples(res));
    user_t** users = malloc((PQntuples(res) + 2) * sizeof(user_t*));
    for (int i = 0; i < PQntuples(res); i++) {
        users[i] = User__create(atoi(PQgetvalue(res, i, 0)), PQgetvalue(res, i, 1), PQgetvalue(res, i, 2), PQgetvalue(res, i, 3));
    }
    return users;
}
void User__destroy(user_t* self) {
    free(self);
}