//
// Created by virdze on 09/04/21.
//

#ifndef PROJECTS_REVIEWS_H
#define PROJECTS_REVIEWS_H

#include "catalogo.h"
#include "worker.h"


typedef struct cat_reviews * Reviews;

Reviews initReviews();
void freeReviews(Reviews rev);
void addReviews(Reviews catReview, Review review);
void printReviews(Reviews catRev);
Table business_info_aux(Reviews reviews, char *business_id);
Table user_business(Reviews reviews, char* user_id);
Table businesses_stars_city(Reviews reviews, float stars,char* city);
Table international_users_aux(Reviews rev);
Table top_businesses_with_category_aux(Reviews rev, int top, char* category);
Table revWord(Reviews reviews, char* word);



#endif //PROJECTS_REVIEWS_H
