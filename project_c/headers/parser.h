#ifndef parser_h
#define parser_h

#include "business.h"
#include "reviews.h"
#include "users.h"
#include "worker.h"
#include "stats.h"


#include <glib.h>

InfoFile parseUsers(char* path, Users users);

InfoFile parseReviews(char* path, Reviews reviews, Business biz, Users users, Stats stats);

InfoFile parseBusiness(char* path, Business business);


#endif