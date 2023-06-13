#ifndef PROJECTS_WORKER_H
#define PROJECTS_WORKER_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <glib.h>
#include "catalogo.h"


typedef struct review * Review;
typedef struct starsCity * StarsCity;
typedef struct infoCategory * InfoCategory;

Review newReview(char* id_review, char* id_user,char* id_business,float stars,int useful,int funny,int cool,char* date, char* text,char* name, char* city, char* state, GPtrArray* categories);
void printReview(Review review);
char* getIDReview(Review review);
char* getIDUser(Review review);
char* getIDBusiness(Review review);
float getStars(Review review);
int getUseful(Review review);
int getFunny(Review review);
int getCool(Review review);
char* getDate(Review review);
char* getText(Review review);
char* getName(Review review);
char* getCity(Review review);
char* getState(Review review);
GPtrArray* getCategories(Review review);
void print(gpointer data, gpointer user_data);
StarsCity initStarsCity(char* cidade, float stars, Table table);
float getStarsBiz(StarsCity sc);
char* getCityBiz(StarsCity sc);
Table getTable(StarsCity sc);
char* stringUpper(char* string);
InfoCategory initInfoCategory(char* category);
char* getCategory(InfoCategory ic);
GTree* getResult(InfoCategory ic);




#endif //PROJECTS_WORKER_H
