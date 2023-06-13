#ifndef PROJECTS_STATS_H
#define PROJECTS_STATS_H

#include <stdio.h>
#include <stdlib.h>
#include "catalogo.h"
#include "worker.h"

typedef struct stats * Stats;


typedef struct infoFile * InfoFile;
InfoFile initInfoFile(char * name, double time, int linhasLidas, int linhasValidas); 
void printInfoFile(InfoFile info);

Stats initStats();
void addInfoFiles(Stats stats, InfoFile business, InfoFile users, InfoFile reviews);
gboolean printinfo(gpointer key, gpointer value, gpointer data);
int addReviewsCity(Stats stats, Review review);
Table top_business_by_city_aux(Stats stats, int top);

void addResultAux(Stats stats, char* var, Table table);
Table getResultAux(Stats stats, char* var);

#endif //PROJECTS_STATS_H
