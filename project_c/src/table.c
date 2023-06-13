#include "../headers/table.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct table{
    /* content matrix */
    char*** content;
    int nr_records;
    int cur_line; 
    /* top headers */
    char** top;
    int nr_top;
    int cur_top;
    /* side headers */
    char** side;
    int nr_side;
    int cur_side;
    /* allocation current size */
    int size;
};

/**
 * Initiate and returns a new table data structure
 */
Table initTable(int nr_top, int nr_side, int init_records){
    Table t = malloc(sizeof(struct table));
    t->nr_top  = nr_top;
    t->nr_side = nr_side;
    t->nr_records = 0;
    t->size = init_records;
    t->cur_line = 0;
    t->cur_top = 0;
    t->cur_side = 0;

    int i,j;
    t->top = malloc(sizeof(char*) * nr_top);
    for(i = 0; i < nr_top; t->top[i++] = 0);
    
    t->side = malloc(sizeof(char*) * nr_side);
    for(i = 0; i < nr_side; t->side[i++] = 0);

    t->content = malloc(sizeof(char**) * init_records);
    for(i = 0; i < init_records; i++){
        t->content[i] = malloc(sizeof(char*) * nr_top);
        for(j = 0; j < nr_top; j++)
            t->content[i][j] = 0;
    }
    return t;
}

/**
 * Destroys the Table data structure
 */
void destroyTable(Table t){
    /* free top headers */
    int i,j = 0;
    for(i = 0; i < t->nr_top; free(t->top[i++]));
    free(t->top);
    /* free side headers */
    for(i = 0; i < t->nr_side; free(t->side[i++]));
    free(t->side);

    /* free content matrix */
    for(i = 0; i < t->nr_records; i++){
        for(j = 0; j < t->nr_top; j++)
            free(t->content[i][j]);
        free(t->content[i]);
    }
    free(t->content);

    /* free table */
    free(t);
}

/** 
 * Adds an header to the top headers 
 */
int addTopHeader(Table t, char* header){
    int ok = 1;
    if(t->cur_top < t->nr_top){
        t->top[t->cur_top++] = strdup(header);
        ok = 0;
    }
    return ok;
}

/**
 * Adds an header to the side headers 
 */
int addSideHeader(Table t, char* header){
    int ok = 1;
    if(t->cur_side < t->nr_side){
        t->side[t->cur_side++] = strdup(header);
        ok = 0;
    }
    return ok;
}

/**
 * Adds a record to the content table 
 */
int addElem(Table t, char** elem, int size_elem){
    int ok = 0;
    char*** tmp;
    int i,j = 0;
    if(t->cur_line == t->size){
        t->size *= 2;
        tmp = malloc(sizeof(char**) * t->size);
        for(i = t->cur_line; i < t->size; i++){
            tmp[i] = malloc(sizeof(char*) * t->nr_top);
            for(j = 0; j < t->nr_top; j++)
                tmp[i][j] = 0;
        }
        for(i = 0; i < t->cur_line; i++){
            tmp[i] = malloc(sizeof(char*) * t->nr_top);
            for(int j = 0; j < t->nr_top; j++){
                tmp[i][j] = strdup(t->content[i][j]);
                free(t->content[i][j]);
            }
            free(t->content[i]);
        }
        free(t->content);
        t->content = tmp;
    }

    for(j = 0; j < size_elem; j++)
        t->content[t->cur_line][j] = strdup(elem[j]);

    t->cur_line++;
    t->nr_records++;

    return ok;
}
/*
char** filter(Table t, char* column_name, char* value, enum op){
    char** f = malloc(sizeof(char*) * 1000);
    int col = -1, found = 0;
    for(int i = 0; i < t->nr_top && !found; i++)
        if( !strcmp(column_name,top[i]) ){
            col = i;
            found = 1;
        }
    for(int i = 0; i < t->nr_records; i++)
        f[i] = strdup(t->content[i][col]);

    return f;
}
*/

/* Returns a table projection */
Table proj(Table t, int* cols, int n){
    Table p = initTable(n,0,1000);
    int i,j = 0;
    /* add top headers */
    for(i = 0; i < n; i++)
        addTopHeader(p,t->top[cols[i]]);

    /* get subset */
    char** r = malloc(sizeof(char*) * n);
    for(i = 0; i < t->nr_records; i++){
        for(j = 0; j < n; j++)
            r[j] = strdup(t->content[i][cols[j]]);
        addElem(p,r,n);
    }
    return p;
}

/* Returns the element in content[i][j] */
Table getElem(Table t, int i, int j){
    Table p = 0;
    if(i >= 0 && i < t->nr_records && j >= 0 && j < t->nr_top){
        p = initTable(1,0,1);
        char** elem = malloc(sizeof(char*));
        elem[0] = strdup(t->content[i][j]);
        addElem(p,elem,1);
        addTopHeader(p,t->top[j]);
    }
    return p;
}

void printTable(Table t){
    if(t==NULL) printf("Empty table!\n");

    int i = 0;
    printf("|");
    for(i = 0; i < t->nr_top; i++)
        printf("%3s%20s%3s| "," ", t->top[i], " ");
    printf("\n");
    for(i = 0; i < t->nr_records; i++){
        printf("\n|");
        for(int j = 0; j < t->nr_top; j++)
            printf("%3s%20s%3s|  ", " ", t->content[i][j], " ");
    }
    printf("\n");
}

int getNrRecords(Table table){
    return table->nr_records;
}

void tableToCSV(Table table, char delim, char* filepath){
    /* se tabela nao tem conteudo o ficheiro nao e criado */
    if(table == NULL){
        printf("A variável não tem conteúdo atribuído! ");
        return;
    } 
    /*
    char* fullpath = "../files/";
    fullpath = strcat(fullpath, filepath);
*/
    FILE * file = fopen(filepath,"w");
    int i, j;

    /* escreve headers da tabela no ficheiro */
    for(i=0; i < table->nr_top -1 ;i++){
        fprintf(file, "%s%c", table->top[i], delim);
    }
    fprintf(file, "%s\n", table->top[i]);

    /* escreve conteudo da tabela no ficheiro */
    for(i = 0; i < table->nr_records; i++){
        for(j = 0; j < table->nr_top -1 ; j++){
            fprintf(file, "%s%c", table->content[i][j], delim);
        }
        fprintf(file, "%s\n", table->content[i][j]);
    }

    fclose(file);
}