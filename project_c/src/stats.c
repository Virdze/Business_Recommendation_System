#include "../headers/stats.h"

struct stats{
    Catalogo reviewsByCity;
    InfoFile business;
    InfoFile users;
    InfoFile reviews;
    GTree* results;
};

typedef struct bizCity{
    char* name;
    float stars;
    int nrReviews;
}*BizCity;

//struct auxiliar para devolver id nome e num estrelas (query6)
typedef struct info{
    int top;
    int nrprinted;
    char* city;
    Table table;
}*InfoCityBiz;



/* Estrutura responsável por guardar o nome e as linhas lidas e validadas de um ficheiro
guarda os tempos de carregamento de cada ficheiro */
struct infoFile{
    char* name;
    double time;
    int linhasLidas;
    int linhasValidas;
};  

InfoFile initInfoFile(char * name, double time, int linhasLidas, int linhasValidas){
    InfoFile info = (InfoFile)malloc(sizeof(struct infoFile));
    info->name= strdup(name);
    info->time = time;
    info->linhasLidas = linhasLidas;
    info->linhasValidas = linhasValidas;
    return info;
}


void freeInfoFile(InfoFile info){
    free(info->name);
    free(info);
}

void addInfoFiles(Stats stats,InfoFile business,InfoFile users, InfoFile reviews){
    stats->business = business;
    stats->users = users;
    stats->reviews = reviews;
}

void printInfoFile(InfoFile info){
  printf("Localização do ficheiro : '%s'\nTempo de carregamento : %.2f sec\nNúmero de linhas lidas --> %d\nNúmero de linhas válidas --> %d\n", info->name,info->time, info->linhasLidas, info->linhasValidas);

}


Stats initStats(){
    Stats stats = malloc(sizeof(struct stats));
    stats->reviewsByCity = initCatalogo(1);
    stats->results = g_tree_new(comparaCod);
    return stats;
} 


int addReviewsCity(Stats stats, Review review){
    char* city_upper = stringUpper(getCity(review));
    GTree* bus = getCode(stats->reviewsByCity,city_upper);

    if(bus == NULL){
        bus = g_tree_new(comparaCod);
        add(stats->reviewsByCity,city_upper,bus);
    }

    BizCity bizcity = g_tree_lookup(bus,getIDBusiness(review));
    if(bizcity == NULL){
        bizcity = (BizCity) malloc(sizeof(struct bizCity));
        bizcity->name = strdup(getName(review));
        bizcity->stars = getStars(review);
        bizcity->nrReviews = 1;
        g_tree_insert(bus,getIDBusiness(review),bizcity);
    }
    else{
        bizcity->stars += getStars(review);
        bizcity->nrReviews++;
    }
    

    return 0;
}



gboolean addToTable2(gpointer key, gpointer value, gpointer data){
    InfoCityBiz cb = (InfoCityBiz)data;
    BizCity bc = (BizCity)value;

    if(cb->nrprinted < cb->top){
        char** elem = malloc(4 * sizeof(char*));
        elem[0] = cb->city;
        elem[1] = (char*)key;
        elem[2] = bc->name;
        elem[3] = malloc(10 * sizeof(char));
        float media = bc->stars/bc->nrReviews;
        sprintf(elem[3], "%.2f", media);

        addElem(cb->table, elem, 4);
        cb->nrprinted++;
    }else return TRUE;

    return FALSE;
}


gboolean addToTable(gpointer key, gpointer value, gpointer data){
    g_tree_foreach(value,addToTable2,data);

    return FALSE;
}

/* lidar com a ordenaçao da GTree key = id_business value = bizCity */
gboolean func2_bi_city(gpointer key, gpointer value, gpointer data){
    //calcular media
    BizCity bc = (BizCity) value;
    float* mediaStars = malloc(sizeof(float*));
    *mediaStars = bc->stars / bc->nrReviews;

    GTree* business = g_tree_lookup(data,mediaStars);

    if(business == NULL){
        business = g_tree_new(comparaCod);
        g_tree_insert(data,mediaStars,business);
    }
    g_tree_insert(business,key,bc);


    return FALSE;
}

/* key cidade, value GTRee id_bus, value struct bizCity */
gboolean func_biz_city(gpointer key, gpointer value, gpointer data){
    InfoCityBiz cb = (InfoCityBiz)data;
    cb->city = strdup((char*)key);

    GTree* result = g_tree_new(comparaStars);

    //para cada cidade cria uma gtree 
    g_tree_foreach(value,func2_bi_city,result);
    
    //associar result a cidade
    cb->nrprinted = 0;
    g_tree_foreach(result,addToTable,cb);

    return FALSE;
}


Table top_business_by_city_aux(Stats stats, int top){
    Table table = initTable(4, 0, 1000);
    addTopHeader(table, "City");
    addTopHeader(table, "Id_business");
    addTopHeader(table, "Nome");
    addTopHeader(table, "Nr Estrelas");

    InfoCityBiz cb = malloc(sizeof(struct info));
    cb->top = top;
    cb->nrprinted = 0;
    cb->table = table;


    forEach(stats->reviewsByCity,func_biz_city,cb);

    return cb->table;
}


void addResultAux(Stats stats, char* var, Table table){
    if(g_tree_lookup(stats->results, var) == NULL){
        g_tree_insert(stats->results, var, table);
    }else g_tree_replace(stats->results, var, table);
}

Table getResultAux(Stats stats, char* var){
    return g_tree_lookup(stats->results, var);
}
