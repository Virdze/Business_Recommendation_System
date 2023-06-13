#include "../headers/parser.h"

#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXREADERUSERS 1000000 //sera suficiente? lol
#define MAXREADER 10000 //

#define userPath     "./db/users_full.csv"
#define businessPath "./db/business_full.csv"
#define reviewsPath  "./db/reviews_1M.csv"


Review parseReview(Business business,Users users, char* review){
    char* id_review = strdup(strsep(&review,";"));
    char* id_user = strdup(strsep(&review,";"));
    char* id_business = strdup(strsep(&review,";"));
    float stars = atof(strsep(&review,";"));
    int useful = atoi(strsep(&review,";"));
    int funny = atoi(strsep(&review,";"));
    int cool = atoi(strsep(&review,";"));
    char* date = strdup(strsep(&review,";"));
    char* text = strdup(strsep(&review,";"));
    char** info = getBusinessInfo(business,id_business); 
    GPtrArray* categories = getBusinessCategories(business,id_business);

    /* Verifica a não existência dos códigos no cat business e cat users */
    if(getBusiness(business,id_business) == NULL) return NULL;
    if(getUsers(users,id_user) == NULL) return NULL;



    return newReview(id_review,id_user,id_business,stars,useful,funny,cool,date,text,info[0],info[1],info[2],categories);
}

InfoFile parseUsers(char* path, Users users){ 
    clock_t tic = clock();

    int linhasLidas = 0;
    char str[MAXREADERUSERS];
    char* user = NULL;

    if(path == NULL) path = strdup(userPath);
    FILE* f = fopen(path,"r");
    if(f == NULL) return NULL;
    fgets(str,MAXREADER,f); // dá skip à primeira linha
    
    while(fgets(str,MAXREADERUSERS,f)){
        if(!str || str[0] == '\r' || str[0] == '\n') break; 
        user = strdup(strtok(str, "\r\n"));
        addUser(users,user);
        linhasLidas++;
    }
    

    fclose(f);
    
    clock_t toc = clock();
    double time = (double)(toc - tic) / CLOCKS_PER_SEC;

    return initInfoFile(path,time,linhasLidas,linhasLidas);
}

InfoFile parseReviews(char* path, Reviews reviews, Business biz, Users users, Stats stats){
    clock_t tic = clock();

    int linhasLidas,linhasValidadas = 0;

    char str[MAXREADER];
    char* review = NULL;

    if(path == NULL) path = strdup(reviewsPath);
    FILE* f = fopen(path,"r");
    if(f == NULL) return NULL;
    fgets(str,MAXREADER,f);

    while(fgets(str,MAXREADER,f)){
        review = strdup(strtok(str, "\r\n"));
        linhasLidas++;
        Review rev = parseReview(biz,users,review);
        if(rev != NULL){
            addReviews(reviews,rev);
            addReviewsCity(stats,rev);
            linhasValidadas++;
        }
    }

    fclose(f);

    clock_t toc = clock();
    printf("Reviews loaded time : %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    double time = (double)(toc - tic) / CLOCKS_PER_SEC;
    return initInfoFile(path,time,linhasLidas,linhasValidadas);
}


InfoFile parseBusiness(char* path, Business business){
    clock_t tic = clock();
    char str[MAXREADER];
    char* biz = NULL;

    int linhasLidas = 0;
    if(path == NULL) path = strdup(businessPath);
    FILE* f = fopen(path,"r");
    if(f == NULL) return NULL;
    fgets(str,MAXREADER,f); 

    while(fgets(str,MAXREADER,f)){
        if(!str || str[0] == '\r' || str[0] == '\n') break; 
        biz = strdup(strtok(str, "\r\n"));
        addBusiness(business,biz);
        linhasLidas++;
    }

    fclose(f);


    clock_t toc = clock();
    double time = (double)(toc - tic) / CLOCKS_PER_SEC;


    return initInfoFile(path,time,linhasLidas,linhasLidas);
}


