//
// Created by corentin on 4/10/24.
//

#ifndef POWERMATCHMAKING_USER_H
#define POWERMATCHMAKING_USER_H

typedef struct User {
    int id;
    char* username;
    char* password;
    char* email;
} user_t;

user_t* User__create(int id, char* username, char* password, char* email);
user_t* User__get(int id);
int User__save(user_t* self);
void User__delete(user_t* self);
user_t** User__all();
void User__destroy(user_t* self);
#endif //POWERMATCHMAKING_USER_H
