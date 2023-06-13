//
// Created by virdze on 10/04/21.
//

#include "../headers/business.h"
#include <stdio.h>
#include <ctype.h>


struct cat_business{
    Catalogo business;
};

typedef struct businessinfo{
    char* name;
    char* city;
    char* state;
    GPtrArray* categories;
}* Businessinfo;

Business initBusiness(){
    Business cat_business = malloc(sizeof(struct cat_business));
    cat_business->business = initCatalogo(0); // com 93 posiçoes
    return cat_business;
}  

gboolean freeBizAux(gpointer key, gpointer value, gpointer data){
    Businessinfo bi = (Businessinfo) value;

    free(bi->name);
    free(bi->city);
    free(bi->state);
    g_ptr_array_free(bi->categories,TRUE);

    free(bi);    
    return FALSE;
}


void freeBusiness(Business biz){
    freeCatalogo(biz->business,freeBizAux);
    free(biz);
}

void addBusiness(Business cat_business, char* biz){
    Businessinfo businessinfo = malloc(sizeof(struct businessinfo));
    char* id = strdup(strsep(&biz, ";"));
    businessinfo->name = strdup(strsep(&biz, ";"));

    businessinfo->city = strdup(strsep(&biz, ";"));

    businessinfo->state = strdup(strsep(&biz, ";"));

    businessinfo->categories = g_ptr_array_new();   

    char* categories = strdup(strsep(&biz,"\r\n"));
    char* categorie = strtok(categories, ",");
    for(int i = 0; categorie!=NULL; i++){

        g_ptr_array_add(businessinfo->categories,strdup(categorie));

        categorie = strtok(NULL,",\r\n");
    }
 
    add(cat_business->business,id,businessinfo);
}

gpointer getBusiness(Business cat_business, char* id_business){
    return getCode(cat_business->business, id_business);
}

/* query 2 */
typedef struct auxLetter{
    char letter;
    Table table;
}*AuxLetter;

/* Função auxiliar responsável por armazenar e imprimir todas as keys de uma GTree numa lista ligada */
gint businessName(gpointer key, gpointer value, gpointer data){
    Businessinfo bi = (Businessinfo) value;
    AuxLetter aux = (AuxLetter) data;

    char* name = bi->name;
    if(toupper(name[0]) == toupper(aux->letter)){
        char** elem = malloc(sizeof(char*));
        elem[0] = strdup(name);
        addElem(aux->table,elem,1);
    }
    
    return FALSE;
}


Table business_started_letter(Business cat_business, char letter){
    Table table = initTable(1,0,10000);
    addTopHeader(table,"Business by Name");

    AuxLetter aux = malloc(sizeof(struct auxLetter));
    aux->letter = letter;
    aux->table = table;

    forEach(cat_business->business, businessName, aux);

    //adicionar nr total de business 
    char** elem = malloc(sizeof(char*));
    elem[0] = malloc(20 * sizeof(char));
    sprintf(elem[0], "Total :: %d", getNrRecords(table));

    addElem(table,elem,1);
    
    return table;
}


/* Funçao que devolve a info (nome, cidade, estrelas) do business */
char** getBusinessInfo(Business cat_business, char* id_business){
    char** info = malloc(3 * sizeof(char*));
    
    Businessinfo infobusiness = getCode(cat_business->business,id_business);
    
    if(infobusiness == NULL) return NULL;
    else {


    info[0] = strdup(infobusiness->name);
    info[1] = strdup(infobusiness->city);
    info[2] = strdup(infobusiness->state);
    }
    return info;
}

/* Funçao que devolve a info (categories) do business */

GPtrArray* getBusinessCategories(Business cat_business, char* id_business){
    Businessinfo businessinfo = getCode(cat_business->business,id_business);   

    return businessinfo->categories;
}


void printBusiness(Business cat_business){
    printCatalogo(cat_business->business);
}
