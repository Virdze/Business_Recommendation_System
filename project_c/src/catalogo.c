#include "../headers/catalogo.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


/* Estrutura Catalogo:
* Hashtable estatica de pointers para uma GTree
*/

struct catalogo{
    GTree** codigos;
    int base;
};

/* Funcao que calcula o indice do array em que um determinado codigo deve ser colocado */
int hashKey(char* codigo, int base){
    int index = -1;
    if(base == 0) index = codigo[0] - '!';
    else {
        index = codigo[0] - 'A';
    }
    return index;
}

/* Função para comparar os codigos a inserir  */
gint comparaCod(gconstpointer codigo1, gconstpointer codigo2){
    return (strcmp(codigo1,codigo2));
}

/* Ordena por ordem decrescente do número das estrelas */
gint comparaStars(gconstpointer code1, gconstpointer code2){
    float a = *((float*)code1) ;
    float b = *((float*)code2) ;
    if(a<b) return 1;
    if(a==b) return 0;
    if(a>b) return -1;
}

/* Inicializa Catálogos */
Catalogo initCatalogo(int base){
    Catalogo cata = (Catalogo)malloc(sizeof(struct catalogo));
    cata->base = base;
    cata->codigos = (GTree**) malloc(BASE * sizeof(GTree *));

    int b = (base == 0) ? BASE : BASE1;
    for(int i = 0; i<b; i++){
        cata->codigos[i] = g_tree_new(comparaCod);  
    }
    
    return cata;
}   


/* Liberta a memória utilizada */
void freeCatalogo(Catalogo catalogo, GTraverseFunc cleanFunc){
    int i;
    int b = (catalogo->base == 0) ? BASE : BASE1;
    
    for(i=0; i<b; i++){
        g_tree_foreach(catalogo->codigos[i],cleanFunc,NULL);
        g_tree_destroy(catalogo->codigos[i]);
    }
    
    free(catalogo);
}

void add(Catalogo catalogo, char* codigo, gpointer value){
    int index = hashKey(codigo,catalogo->base);
    g_tree_insert(catalogo->codigos[index], codigo, value); 
}

/* Devolve o value cuja key é code na GTree presente num catálogo */
gpointer getCode(Catalogo catalogo,char* code){
    int index= hashKey(code, catalogo->base);
    return g_tree_lookup(catalogo->codigos[index], code);
}

/*Função que aplica uma determinada função passada como parâmetro a todos os elementos de um catálogo*/
void forEach(Catalogo catalogo, GTraverseFunc function, gpointer data){
    int cont = 0;
    int b = (catalogo->base == 0) ? BASE : BASE1;
    for(int i=0; i<b; i++){
        int nrnodes = g_tree_nnodes(catalogo->codigos[i]);
        g_tree_foreach(catalogo->codigos[i], function, data);
        cont += nrnodes;
    }

}



gint TraverseTree2(gpointer key, gpointer value, gpointer data){
    printf("Codigos: %s\n", (char*)key);
    return FALSE;
}

void printCatalogo(Catalogo catalogo){
    for(int i=0; i<BASE ; i++)
        g_tree_foreach(catalogo->codigos[i], TraverseTree2, NULL);
}

void printCatalogoFunc(Catalogo catalogo, GTraverseFunc function){
    int i;
    for(i=0; i<BASE ; i++)
        g_tree_foreach(catalogo->codigos[i], function, NULL);
}