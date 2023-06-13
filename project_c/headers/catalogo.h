#ifndef catalogo_h
#define catalogo_h

#include <time.h>
#include <glib.h>

#include "table.h"


#define BASE 93 /* 26 letras do alfabeto representam a 1ªletra do id + caracteres especiais */
#define BASE1 26 /* 26 letras do alfabeto */

typedef struct catalogo* Catalogo;

void addCatalogos(Catalogo* catalogos, char* codigo, gpointer value);
void printCatalogo(Catalogo catalogo);
Catalogo initCatalogo(int base);
void freeCatalogo(Catalogo catalogo, GTraverseFunc cleanFunc);
void add(Catalogo catalogos, char* codigo, gpointer value);
gint comparaCod(gconstpointer codigo1, gconstpointer codigo2);
gint comparaStars(gconstpointer code1, gconstpointer code2);
void forEach(Catalogo catalogo, GTraverseFunc function, gpointer data); 
gpointer getCode(Catalogo catalogo,char* code);
void printCatalogoFunc(Catalogo catalogo, GTraverseFunc function);
void forEach(Catalogo catalogo, GTraverseFunc function, gpointer data);

#endif