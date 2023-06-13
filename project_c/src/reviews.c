#include "../headers/reviews.h"
#include <stdio.h>
#include <string.h>


struct cat_reviews{
    Catalogo reviewsbybusiness;
    Catalogo reviewsbyuser;
};

/* Estrutura criada para inserir como value na GTree presente na struct reviewsBiz, a key vai ser o id_reviews */
typedef struct reviewsinfo{
    float stars;
    int useful;
    int funny;
    int cool;
    char* text;
}*Reviewsinfo;
 
/* Estrutura criada para inserir como value na GTree do catalogo, a key vai ser o id_business */
typedef struct reviewsBiz{
    char* name;
    char* city;
    char* state;
    GPtrArray* categories;
    float stars; // média das estrelas em cada business
    GTree* reviews; 
}*Reviewsbiz;

//struct auxiliar para devolver id nome e num estrelas (query6)
typedef struct info{
    int top;
    int nrprinted;
    float stars;
    Table table;
}*InfoCategoryBiz;

Reviews initReviews(){
    Reviews cat_reviews = malloc(sizeof(struct cat_reviews));
    cat_reviews->reviewsbybusiness = initCatalogo(0);
    cat_reviews->reviewsbyuser = initCatalogo(0);
    
    return cat_reviews;
}  

gboolean freeBusiness2(gpointer key, gpointer value, gpointer data){
    Reviewsinfo ri = (Reviewsinfo) value;
    free(ri->text);
    free(ri);

    return FALSE;
}

gboolean freeBusinessAux(gpointer key, gpointer value, gpointer data){
    Reviewsbiz rb = (Reviewsbiz) value;

    free(rb->name);
    free(rb->city);
    free(rb->state);
    
    g_tree_foreach(rb->reviews,freeBusiness2,NULL);
    g_tree_destroy(rb->reviews);

    free(rb);

    return FALSE;
}


gboolean freeUsersAux1(gpointer key, gpointer value, gpointer data){
    g_tree_destroy(value);
    return FALSE;
}


void freeReviews(Reviews rev){
    freeCatalogo(rev->reviewsbybusiness, freeBusinessAux);
    freeCatalogo(rev->reviewsbyuser,freeUsersAux1);
    free(rev);
}

void addReviews(Reviews catReview, Review review){
    // Criar a estrutura reviewsInfo que vai guardar a info relativa a uma review
    
    Reviewsinfo ri = malloc(sizeof(struct reviewsinfo));
    ri->stars = getStars(review);
    ri->useful = getUseful(review);
    ri->funny = getFunny(review);
    ri->cool = getCool(review);
    ri->text = getText(review);


    // Verificar a existencia (ou nao) de id_business no catalogo reviewsbybusiness
    Reviewsbiz revbiz = getCode(catReview->reviewsbybusiness,getIDBusiness(review));

    if(revbiz == NULL) {
        revbiz = malloc(sizeof(struct reviewsBiz));
        revbiz->name = getName(review);
        revbiz->city = getCity(review);
        revbiz->state = getState(review);
        revbiz->categories = getCategories(review);
        revbiz->stars = getStars(review);
        revbiz->reviews = g_tree_new(comparaCod);
        // Adiciona o novo id_business no catalogo reviewsbybusiness e com a estrutura revbiz
        add(catReview->reviewsbybusiness,getIDBusiness(review),revbiz);

    }else{
        revbiz->stars += getStars(review);
    }

    g_tree_insert(revbiz->reviews,getIDReview(review),ri);    
    //USERS                 
    // criar uma Gtree key = id_user value = GTree cuja key id_business e value = struct reviewsBiz

    // Verificar a existencia (ou nao) de id_user no catalogo reviewsbyuser
    GTree* bus = getCode(catReview->reviewsbyuser,getIDUser(review));

    if(bus == NULL){
        bus = g_tree_new(comparaCod);
        add(catReview->reviewsbyuser,getIDUser(review),bus);
    }
    g_tree_insert(bus,getIDBusiness(review),revbiz);
}

gint printTree2(gpointer key, gpointer value, gpointer data){
    printf("id_review : %s\n",(char*)key);
    Reviewsinfo ri = (Reviewsinfo) value;
    printf("stars: %f useful: %d text : %s \n", ri->stars,ri->useful,ri->text);


    return FALSE;   
}

gint printTree(gpointer key, gpointer value, gpointer data){
    Reviewsbiz rb = (Reviewsbiz) value;
    printf("name: %s city: %s state : %s media_stars : %f \n", rb->name, rb->city, rb->state, rb->stars);
    

    return FALSE;
}

gint printTreeUser(gpointer key, gpointer value, gpointer data){
    printf("id_user: %s\n", (char*)key);
    g_tree_foreach(value, printTree, NULL);

    return FALSE;
}

//query 3

Table business_info_aux(Reviews reviews, char *business_id){

    Reviewsbiz rev = getCode(reviews->reviewsbybusiness,business_id);

    if(rev == NULL) return NULL;
    Table table = initTable(5,0,10000);
    addTopHeader(table,"Business Name");
    addTopHeader(table,"City");
    addTopHeader(table,"State");
    addTopHeader(table,"Stars");
    addTopHeader(table,"Number of Reviews");

    char info[100];
    char** temp = malloc(5 * sizeof(char*));
    temp[0] = strdup(rev->name);
    temp[1] = strdup(rev->city);
    temp[2] = strdup(rev->state);
    int cont = g_tree_nnodes(rev->reviews);
    sprintf(info,"%.2f",rev->stars/cont);
    temp[3] = strdup(info);
    sprintf(info, "%d",cont);
    temp[4] = strdup(info);

    addElem(table,temp,5);

    return table;
}

// query 4
gboolean auxUser_Business(gpointer key, gpointer value, gpointer data){
    Reviewsbiz rb = (Reviewsbiz) value;
    char** temp = malloc(2 * sizeof(char*));
    temp[0] = strdup((char*)key);
    temp[1] = strdup(rb->name);

    addElem(data,temp,2);

    return FALSE;
}

Table user_business(Reviews reviews, char* user_id){
    GTree* business = getCode(reviews->reviewsbyuser,user_id);
    if(business == NULL) return NULL;
    Table table = initTable(2,0,10000);
    addTopHeader(table,"Business Reviewed");
    addTopHeader(table,"Name");

    g_tree_foreach(business,auxUser_Business,table);
    int cont = g_tree_nnodes(business);
    
    char** temp = malloc(2 * sizeof(char*));
    temp[0] = "nr of reviews";
    temp[1] = malloc(10 * sizeof(char));
    sprintf(temp[1],"%d",cont);
    

    addElem(table,temp,2);

    return table;
}


/* QUERY 5 */
gint business_stars_city_aux(gpointer key, gpointer value, gpointer data){
    Reviewsbiz rb = (Reviewsbiz) value;
    int nrBusiness = (int) g_tree_nnodes(rb->reviews);
    float mediaStars = rb->stars/nrBusiness;
    StarsCity sc = (StarsCity) data;
    

    // value nª stars > n & cidade ==
    if(!strcmp(stringUpper(rb->city),getCityBiz(sc)) && mediaStars >= getStarsBiz(sc)){
        char** elem = malloc(2 * sizeof(char*));
        elem[0] = strdup((char*)key);
        elem[1] = strdup(rb->name);
        addElem(getTable(sc),elem,2);
    }
    return FALSE;
}

/* a lista de negócios com n ou mais stars na dada cidade, id e nome do business */
Table businesses_stars_city(Reviews reviews, float stars,char* city){

    Table table = initTable(2,0,10000);
    addTopHeader(table,"Business id");
    addTopHeader(table,"Business name");

    StarsCity sc = initStarsCity(city,stars,table); 
    

    forEach(reviews->reviewsbybusiness,business_stars_city_aux,sc);

    return table;
}

//Query 7
/* funcao auxiliar GCompareFunc que compara duas strings caso a primeira seja diferente de NULL */
gint comparaCodee(gconstpointer codigo1, gconstpointer codigo2){
    if(codigo1 == NULL) return 1;
    return (strcmp((char*)codigo1,(char*)codigo2));
}


gboolean intUsersAux(gpointer key, gpointer value, gpointer data){
    Reviewsbiz rb = (Reviewsbiz) value;
    GSList* states = (GSList*) data;
    char* state = rb->state;

    if(g_slist_find_custom(states,state,comparaCodee) == NULL)
        states = g_slist_append(states,state);
    
    return FALSE;
}

gboolean internationalUsersAux(gpointer key, gpointer value, gpointer data){
    GSList* states = g_slist_alloc();
    g_tree_foreach(value,intUsersAux,states);
    int size = g_slist_length(states)-1; 

    if(size>1){
        char** elem = malloc(sizeof(char*));
        elem[0] = strdup(key);
        addElem((Table) data, elem, 1); 
    }  
    return FALSE;
}

Table international_users_aux(Reviews rev){
    Table table = initTable(1,0,10000);
    addTopHeader(table,"id_users");
    forEach(rev->reviewsbyuser,internationalUsersAux,table);

    return table;
}

//QUERY 8

gboolean comparaString(gconstpointer a, gconstpointer b){
    if(strcmp(a,b)==0) return TRUE;

    return FALSE;
}

gboolean printInfo2(gpointer key, gpointer value, gpointer data){
    InfoCategoryBiz icb = (InfoCategoryBiz) data;
    
    if(icb->nrprinted < icb->top){
        char** elem = malloc(3 * sizeof(char*));
        elem[0] = strdup((char*)key);
        elem[1] = (char*)value;
        elem[2] = malloc(10 * sizeof(char));
        sprintf(elem[2], "%.2f", icb->stars);

        addElem(icb->table, elem, 3);
        icb->nrprinted++;
    }else return TRUE;

    return FALSE;
}

gboolean printInfo(gpointer key, gpointer value, gpointer data){
    float f = *((float*)key);
    InfoCategoryBiz icb = (InfoCategoryBiz) data;

    icb->stars = f;

    g_tree_foreach(value,printInfo2,data);


    return FALSE;

}

gboolean categoryAux(gpointer key, gpointer value, gpointer data){
    InfoCategory ic = (InfoCategory) data;
    Reviewsbiz rb = (Reviewsbiz) value;
    GTree* result = getResult(ic);


    if(g_ptr_array_find_with_equal_func(rb->categories,getCategory(ic),comparaString,NULL) == TRUE){
        float* mediaStars = malloc(sizeof(float*));
        *mediaStars = rb->stars / g_tree_nnodes(rb->reviews);

        GTree* business = g_tree_lookup(result,mediaStars);

        if(business == NULL){
            business = g_tree_new(comparaCod);
            g_tree_insert(result,mediaStars,business);
        }
        g_tree_insert(business,key,rb->name);

    }
    return FALSE;
}

Table top_businesses_with_category_aux(Reviews rev, int top, char* category){
    Table table = initTable(3, 0, 1000);
    addTopHeader(table, "Id_business");
    addTopHeader(table, "Nome");
    addTopHeader(table, "Nr Estrelas");


    InfoCategory ic = initInfoCategory(category);
    
    InfoCategoryBiz icb = malloc(sizeof(struct info));
    icb->nrprinted = 0;
    icb->top = top;
    icb->table = table;
    

    forEach(rev->reviewsbybusiness,categoryAux,ic);

    g_tree_foreach(getResult(ic),printInfo,icb);

    return table;
}

// Query 9 auxs
typedef struct auxRevWord{
    Table table;
    char* help;
}*RevWord;


/* zero se word esta contida em text, 1 caso contrario */
int seekText(char* word, char* text){
    int wi, ti;
    int word_size = strlen(word);


    for(ti = 0; ti<strlen(text); ){
        for(wi = 0; wi<word_size; wi++){
            if(toupper(text[ti++]) != toupper(word[wi])) break;
        }
        if(wi == word_size) return 0; 
    }
    return 1;
}


gboolean wordAux(gpointer key, gpointer value, gpointer data){
    Reviewsinfo ri = (Reviewsinfo) value;
    RevWord rw = (RevWord) data;

    int result = seekText(rw->help, ri->text);

    if(result == 0){
        char** elem = malloc(sizeof(char*));
        elem[0] = strdup(key);
        addElem(rw->table,elem,1);
    }

    return FALSE;
}

gboolean revWordAux(gpointer key, gpointer value, gpointer data){
    Reviewsbiz rb = (Reviewsbiz) value;
    g_tree_foreach(rb->reviews, wordAux, data);
    return FALSE;
}

//query 9
Table revWord(Reviews reviews, char* word){
    Table table = initTable(1,0,10000);
    addTopHeader(table, "Id Review"); 
    RevWord rw = malloc(sizeof(struct auxRevWord));
    rw->table = table;
    rw->help = word;
    forEach(reviews->reviewsbybusiness,revWordAux,rw);

    return rw->table;
}


void printReviews(Reviews catRev){
    printCatalogoFunc(catRev->reviewsbyuser,printTreeUser);
}
