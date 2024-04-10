#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <libpq-fe.h>
#include "server.h"
#include "models/user.h"
#include "PowerContext.h"

int main()
{
    int libpq_ver = PQlibVersion();
    printf("Version of libpq: %d\n", libpq_ver);
    power_context_t* context = PowerContext__instance();
    PGconn* conn = PowerContext__connect(context);
    if (conn == NULL) {
        printf("Connection to database failed\n");
        return 1;
    }

    PGresult* res = PQexec(conn, "SELECT version()");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("No data retrieved\n");
        return 1;
    }
    printf("Postgres version: %s\n", PQgetvalue(res, 0, 0));
    PQclear(res);
    user_t* user = User__create(1, "admin", "admin", "corentin.pitrel@outlook.fr");
    User__save(user);
    user = User__create(2, "admin", "admin", "corentin.pitrel@outlook.fr");
    User__save(user);

    user_t* user2 = User__get(1);
    printf("User: %s password: %s, email: %s\n", user2->username, user2->password, user2->email);

    printf("All users:\n");
    user_t** users = User__all();
    printf("Username all : %s\n", users[0]->username);
    printf("Username all : %s\n", users[1]->username);
    for (int i = 0; users[i] != NULL; i++) {
        printf("User: %s password: %s, email: %s\n", users[i]->username, users[i]->password, users[i]->email);
    }

    User__delete(user2);
    printf("User deleted\n");

    printf("All users:\n");
    users = User__all();
    for (int i = 0; users[i] != NULL; i++) {
        printf("User: %s password: %s, email: %s\n", users[i]->username, users[i]->password, users[i]->email);
    }
}