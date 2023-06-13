#define FILES_PATH "db/"
#include <stdlib.h>

#include "../headers/interpretador.h"

#include <stdio.h>

int main(){
    SGR sgr = load_sgr(NULL,NULL,NULL);

    int res = interpretador(sgr);

    free_sgr(sgr);
    return 0;
}
