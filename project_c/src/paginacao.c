#include "../headers/paginacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void paginacao(Table t){
    int linhasmax = 24,  //standard value for lines in terminal
    colunasmax = 80; //standard value for columns in terminal
    int l = 0,
        c = 0;
    char * keypressed;

    toPage(t,c,l,colunasmax, linhasmax);

    while(fgets(keypressed,1,stdin)){
        if(strcmp(keypressed,"n")){ // n - next
            c += colunasmax;
            l += linhasmax;
            colunasmax += colunasmax;
            linhasmax += linhasmax;
            toPage(t,c,l,colunasmax,linhasmax);
        }
        else if(strcmp(keypressed,"p")){
            c -= colunasmax;
            l -= linhasmax;
            colunasmax += colunasmax;
            linhasmax += linhasmax;
            toPage(t,c,l,colunasmax,linhasmax);
        } // p -previous
    }
}

void toPage(Table t, int colunas_init, int linhas_init, int colunas_end, int linhas_end){

    printf("|");
    for(int i = 0; i < t->nr->top; i++)
        printf("%3s%20s%3s| "," ", t->top[i], " ");
    printf("\n");
    for(i = colunas_init; i < colunas_end; i++){
        printf("\n|");
        for(int j = linhas_init; j < linhas_end; j++)
            printf("%3s%20s%3s|  ", " ", t->content[i][j], " ");
    }
    printf("\n");

}