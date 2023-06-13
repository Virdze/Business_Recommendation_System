#include "../headers/worker.h"

struct review{
    char* id_review;
    char* id_user;
    char* id_business;
    float stars;
    int useful;
    int funny;
    int cool;
    char* date;
    char* text;
    char* name;
    char* city;
    char* state;
    GPtrArray* categories;
};

//struct auxiliar para ter o nºstars e cidade (query 5)
struct starsCity{
    char* cidade;
    float stars;
    Table table;
};

//struct auxiliar para saber categoria e guarda o resultado numa GTree (query 8)
struct infoCategory{
    char* string;
    GTree* result;
    Table table;
};


Review newReview(char* id_review, char* id_user,char* id_business,float stars,int useful,int funny,int cool,char* date, char* text,char* name, char* city, char* state, GPtrArray* categories){
    Review rev = malloc(sizeof(struct review));
    rev->id_review = id_review;
    rev->id_user = id_user;
    rev->id_business = id_business;
    rev->stars = stars;
    rev->useful = useful;
    rev->funny = funny;
    rev->cool = cool;
    rev->date = date;
    rev->text = text;
    rev->name = name;
    rev->city = city;
    rev->state = state;
    rev->categories = categories;

    return rev;
}


/*Função auxiliar que imprime para o terminal*/ // ->>>>>>> NAO É PARA FICAR AQUI
void print(gpointer data, gpointer user_data){
    if(!(data == NULL)) {
    printf("%s\n", (char*)data);
    }
}

void printReview(Review review){
    printf("id_reviews :: %s\n",review->id_review);
    printf("id_business :: %s\n",review->id_business);
    printf("id_user :: %s\n",review->id_user);
    printf("stars :: %f\n",review->stars);
    printf("useful :: %d\n",review->useful);
    printf("funny :: %d\n",review->funny);
    printf("cool :: %d\n",review->cool);
    printf("nome :: %s\n",review->name);
    printf("estado :: %s\n",review->state);
    printf("cidade :: %s\n",review->city);
    
    g_ptr_array_foreach(review->categories, print, NULL);
    printf("TEXT :: %s\n", review->text);
}

char* getIDReview(Review review){
    return review->id_review;
}

char* getIDUser(Review review){
    return review->id_user;
}

char* getIDBusiness(Review review){
    return review->id_business;
}

float getStars(Review review){
    return review->stars;
}

int getUseful(Review review){
    return review->useful;
}

int getFunny(Review review){
    return review->funny;
}

int getCool(Review review){
    return review->cool;
}

char* getDate(Review review){
    return review->date;
}

char* getText(Review review){
    return review->text;
}


char* getName(Review review){
    return review->name;
}

char* getCity(Review review){
    return review->city;
}

char* getState(Review review){
    return review->state;
}

GPtrArray* getCategories(Review review){
    return review->categories;
}

/* stars city */

char* stringUpper(char* string){
    int len = strlen(string)+1;
    int i = 0;
    char* newString = malloc(len * sizeof(char));
    while (i<len){
        newString[i] = toupper(string[i]);
        i++;
    }
    //newString[i] = '\0';
    return newString;
}

StarsCity initStarsCity(char* cidade, float stars, Table t){
    StarsCity sc = malloc(sizeof(struct starsCity));

    sc->cidade = stringUpper(cidade);
    sc->stars = stars;
    sc->table = t;

    return sc;
}

InfoCategory initInfoCategory(char* category){
    InfoCategory ic = malloc(sizeof(struct infoCategory));

    ic->string = category;
    ic->result = g_tree_new(comparaStars);

    return ic;
}


float getStarsBiz(StarsCity sc){
    return sc->stars;
}

char* getCityBiz(StarsCity sc){
    return sc->cidade;
}

Table getTable(StarsCity sc){
    return sc->table;
}

char* getCategory(InfoCategory ic){
    return ic->string;
}

GTree* getResult(InfoCategory ic){
    return ic->result;
}
