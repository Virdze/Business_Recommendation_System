//
// Created by virdze on 10/04/21.
//

#ifndef PROJECTS_BUSINESS_H
#define PROJECTS_BUSINESS_H

#include "catalogo.h"

typedef struct cat_business* Business;


Business initBusiness();
void freeBusiness(Business biz);
void addBusiness(Business business, char* biz);
void printBusiness(Business cat_business);
gpointer getBusiness(Business cat_business, char* id_business);
Table business_started_letter(Business cat_business, char letter);
char** getBusinessInfo(Business cat_business, char* id_business);
GPtrArray* getBusinessCategories(Business cat_business, char* id_business);


#endif //PROJECTS_BUSINESS_H
