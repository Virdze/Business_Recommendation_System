//
// Created by virdze on 09/04/21.
//
#include <stdio.h>

#include "../headers/users.h"

struct cat_users{
    Catalogo users;
};

struct userinfo{
    char* name;
    GPtrArray* friends;
};

void addUser(Users catUsers, char* user){
    Userinfo userinfo = malloc(sizeof(struct userinfo));
    char* id = strdup(strsep(&user, ";"));
    userinfo->name = strdup(strsep(&user,";"));
    userinfo->friends = g_ptr_array_new();

    /* Possibilidade de ter amigos
    char* friends = strdup(strsep(&user,"\r\n"));
    char* friend = strtok(friends,",");
    for(int i = 0; friend!=NULL; i++){
        printf("amigos :: %s :: \n",friend);

        g_ptr_array_add(userinfo->friends,strdup(friend));
        friend = strtok(NULL,",\r\n");
    }
    */
    

    add(catUsers->users,id,userinfo);
}

Users initUsers(){
    Users cat_users = malloc(sizeof(struct cat_users));
    cat_users->users = initCatalogo(0); // 93 posiçoes
    return cat_users;
}

gboolean freeUsersAux(gpointer key, gpointer value, gpointer data){
    Userinfo ui = (Userinfo) value;

    free(ui->name);
    g_ptr_array_free(ui->friends,TRUE);

    free(ui);    

    return FALSE;
}


void freeUsers(Users users){
    freeCatalogo(users->users,freeUsersAux);
    free(users);
}

gpointer getUsers(Users cat_users, char* id_users){
    return getCode(cat_users->users, id_users);
}


void printUsers(Users cat_users){
    printCatalogo(cat_users->users);
}