//
// Created by virdze on 10/04/21.
//

#include "../headers/sgr.h"

struct sgr{
    Users users;
    Business business;
    Reviews reviews;
    Stats stats;
};


SGR initSGR(){
    SGR new = (SGR) malloc(sizeof(struct sgr));
    new->business = initBusiness();
    new->users = initUsers();
    new->stats = initStats();
    new->reviews = initReviews();
    return new;
}


SGR load_sgr(char* users,char* businesses,char* reviews){
    SGR sgr = initSGR();
    InfoFile businessInfo = parseBusiness(businesses,sgr->business);
    printInfoFile(businessInfo); 
    InfoFile usersInfo = parseUsers(users, sgr->users);
    printInfoFile(usersInfo); 
    InfoFile reviewsInfo =  parseReviews(reviews, sgr->reviews, sgr->business,sgr->users,sgr->stats);
    printInfoFile(reviewsInfo); 
    addInfoFiles(sgr->stats,businessInfo,usersInfo,reviewsInfo);
    return sgr;
}

void free_sgr(SGR sgr){
    freeUsers(sgr->users);
    printf("free users\n");
    freeBusiness(sgr->business);
    printf("free business\n");
    freeReviews(sgr->reviews);
    printf("free reviews\n");
    
    free(sgr);
}


/*          Auxiliares     */


/*          Queries     */



// 2 - 
Table businesses_started_by_letter(SGR sgr, char letter){
    clock_t tic = clock();

    Table table = business_started_letter(sgr->business,letter);

    clock_t toc = clock();
    printf("Query2: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return table;
}

//3 - 
//  nome, cidade, estado, stars e numero total reviews
Table business_info(SGR sgr, char *business_id){
    clock_t tic = clock();

    Table table = business_info_aux(sgr->reviews,business_id);

    clock_t toc = clock();
    printf("Query3: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    
    return table;
}

//4 -
Table businesses_reviewed(SGR sgr, char *user_id){
    clock_t tic = clock();

    Table table = user_business(sgr->reviews,user_id);

    clock_t toc = clock();
    printf("Query4: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return table;
}

//5 - 
Table businesses_with_stars_and_city(SGR sgr, float stars, char *city){
    clock_t tic = clock();

    Table table = businesses_stars_city(sgr->reviews,stars,city);

    clock_t toc = clock();
    printf("Query5: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return table;
}

//6 -
Table top_businesses_by_city(SGR sgr, int top){
    clock_t tic = clock();

    Table table = top_business_by_city_aux(sgr->stats,top);

    clock_t toc = clock();
    printf("Query6: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return table;
} 

//7 -
Table international_users(SGR sgr){
    clock_t tic = clock();

    Table table = international_users_aux(sgr->reviews);

    clock_t toc = clock();
    printf("Query7: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return table;
}

//8-
Table top_businesses_with_category(SGR sgr, int top, char *category){
    clock_t tic = clock();
    
    Table table = top_businesses_with_category_aux(sgr->reviews,top,category);

    clock_t toc = clock();
    printf("Query8: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    
    return table;
}


//9- reviews_with_Words

Table reviews_with_word(SGR sgr, char *word){
    clock_t tic = clock();

    Table table =  revWord(sgr->reviews, word);

    clock_t toc = clock();
    printf("Query9: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    
    return table;
}


void addResults(SGR sgr, char* var, Table table){
    addResultAux(sgr->stats, var, table);
}

Table getResults(SGR sgr, char* var){
    return getResultAux(sgr->stats, var);
}