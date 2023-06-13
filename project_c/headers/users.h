//
// Created by virdze on 09/04/21.
//

#ifndef PROJECTS_USERS_H
#define PROJECTS_USERS_H

#include "catalogo.h"

typedef struct cat_users * Users;
typedef struct userinfo * Userinfo;

void addUser(Users users, char* user);
Users initUsers();
void freeUsers(Users users);
gpointer getUsers(Users cat_users, char* id_users);
void printUsers(Users cat_users);

#endif //PROJECTS_USERS_H
