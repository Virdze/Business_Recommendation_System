#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/sgr.h"

#define BUFFERSIZE 1024


char ** tokenize(char * input, char * delim){
    char ** tokens = malloc(4 * sizeof(char **));
    char * token = strtok(input, delim);
    int i = 0;
    while(token != NULL){
        tokens[i++] = strdup(token);
        printf("tokens[%d] : %s\n", i-1, token);
        token = strtok(NULL, delim);
    }
    return tokens;
}

int hashtoken_for_others(char * token){
    int x;
    if(strcmp(token, "show") == 0)
        x = 1;
    else if(strcmp(token, "toCSV") == 0)
        x = 2;
    return x;
}

int hashtoken_for_Assignment(char ** token){
    int x;
    char temp;
    if(strcmp(token[0], "businesses_started_by_letter") == 0 && strcmp(token[1],"sgr") == 0)
        x = 1;
    else if(strcmp(token[0], "business_info") == 0 && strcmp(token[1],"sgr") == 0)
        x = 2;
    else if(strcmp(token[0], "businesses_reviewed") == 0 && strcmp(token[1],"sgr") == 0)
        x = 3;
    else if(strcmp(token[0], "businesses_with_stars_and_city") == 0 && strcmp(token[1],"sgr") == 0)
        x = 4;
    else if(strcmp(token[0], "top_businesses_by_city") == 0 && strcmp(token[1],"sgr") == 0)
        x = 5;
    else if(strcmp(token[0], "international_users") == 0 && strcmp(token[1],"sgr") == 0)
        x = 6;
    else if(strcmp(token[0], "top_businesses_with_category") == 0 && strcmp(token[1],"sgr") == 0)
        x = 7;
    else if(strcmp(token[0], "reviews_with_word") == 0 && strcmp(token[1],"sgr") == 0)
        x = 8;
    else if(strcmp(token[0], "fromCSV") == 0)
        x = 9;
    else if(strcmp(token[0], "filter") == 0)
        x = 10;
    else if(strcmp(token[0], "proj") == 0)
        x = 11;
    else if((temp = token[0][0]) >= 'a' && temp <= 'z')
        x = 12;
    else if(strcmp(token[0], "load_sgr")==0)
        x = 13;
    printf("x :: %d\n", x);
    return x;
}

int findPos(char * vars, char toFind){
    int res = -1;
    if(vars == NULL) return res;
    for(int i = 0; i < strlen(vars); i++)
        if(vars[i] == toFind)
            res = i;
    return res;
}

char * addToVars(char * vars_assigned, char letter, int size){
    int i = 0;
    char *temp = malloc(size * sizeof(char));
    if(vars_assigned != NULL) {
        strcpy(temp,vars_assigned);
        temp[size] = letter;
        temp[size+1] = EOF;
    }
    else {
        temp[0] = letter;
        temp[1] = EOF;
    }
    return temp;
}


Table fromCSV(char * filepath, char* delim){
    FILE * file = fopen(filepath,"r");
    if(file == NULL) return NULL;
    printf("file != null");
    char readed[BUFFERSIZE];
    int i = 0;

    /* read first line and get nr of headers */
    fgets(readed,BUFFERSIZE,file);

    char ** tokens = malloc(sizeof(char **));
    char * token = strtok(readed, delim);

    while(token != NULL){
        tokens[i++] = strdup(token);
        token = strtok(NULL, delim);
    }

    int nr_headers = i;

    Table table = initTable(nr_headers,0,1000);
    for(i=0; i<nr_headers;i++) 
        addTopHeader(table, tokens[i]);


    while(fgets(readed, BUFFERSIZE, file)){
        char** content = malloc(nr_headers * sizeof(char*));
        char * tok = strtok(readed, delim);

        while(tok != NULL){
            content[i++] = strdup(token);
            tok = strtok(NULL, delim);
        }

        addElem(table, content, nr_headers);
    }

    return table;
}

int interpretador(SGR sgr){
    FILE *fp;
    char input[BUFFERSIZE];
    char ** tokens;
    //char * vars_assigned;
    Table table = NULL;

    while((strcmp(fgets(input, BUFFERSIZE, stdin),"quit\n")) != 0){
        //divide o input em strins, o delim que separa é o " "
        tokens = tokenize(input, " )");

        if(strcmp(tokens[1],"=") == 0){ // Verifica se é uma operação de atribuição
            char* var = tokens[0];
            tokens = tokenize(tokens[2], "(,)");

            switch(hashtoken_for_Assignment(tokens)){
                case 1:
                    table = businesses_started_by_letter(sgr, tokens[2][0]);
                    break;
                case 2:
                    table = business_info(sgr,tokens[2]);
                    break;
                case 3:
                    table = businesses_reviewed(sgr,tokens[2]);
                    break;
                case 4:
                    table = businesses_with_stars_and_city(sgr,atof(tokens[2]),tokens[3]);
                    break;
                case 5:
                    table = top_businesses_by_city(sgr,atoi(tokens[2]));
                    break;
                case 6:
                    table = international_users(sgr);
                    break;
                case 7:
                    table = top_businesses_with_category(sgr, atoi(tokens[2]), tokens[3]);
                    break;
                case 8:
                    table = reviews_with_word(sgr,tokens[2]);
                    break;
                case 9:
                    table = fromCSV(tokens[1], tokens[2]);
                    break;
                case 10: /*filter*/
                    break;
                case 11: /* proj*/
                    break;
                case 12: /* get [][] of table */
                    tokens = tokenize(tokens[0],"[]");
                    table = getElem(getResults(sgr,tokens[0]),tokens[1],tokens[2]);
                    break;
                case 13: 
                    free_sgr(sgr);
                    sgr = initSGR();

                    sgr = load_sgr(tokens[1], tokens[2], tokens[3]);
                    break;
                default:
                    printf("COMANDO INVÁLIDO");
                    break;
            }
            addResults(sgr, var, table);
        } else {
            tokens = tokenize(tokens[0], "(,)");
            switch(hashtoken_for_others(tokens[0])){
                case 1: /* show */
                    printTable(getResults(sgr, tokens[1]));
                    break;
                case 2: /* toCSV */
                    table = getResults(sgr, tokens[1]);
                    tableToCSV(table, tokens[2][0], tokens[3]);
                    break;
                default:
                    break;
            }
            // restantes comandos
        }
    }

    return 0;
}