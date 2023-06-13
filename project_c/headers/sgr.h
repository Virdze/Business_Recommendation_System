#ifndef _SGR_H_
#define _SGR_H_

/* includes dos headers necessários */
#include "parser.h"


/**
 * Estrutura que guarda toda a informacao do Sistema de Gestão de Recomendações
 */
typedef struct sgr *SGR;

/**
 * Inicializa a estrutura geral do sistema
 *
 * return : estrutura geral do sistema inicializada
 */
SGR initSGR();

/**
 * Destroi a estrutura geral do sistema libertando toda a sua memoria
 *
 * sgr : estrutura geral do sistema
 */
void free_sgr(SGR sgr);


/* Auxiliares */


/* queries */

// Função para carregar os ficheiros para as estruturas respectivas
SGR load_sgr(char* users,char* businesses,char* reviews);
Table businesses_started_by_letter(SGR sgr, char letter);
Table business_info(SGR sgr, char *business_id);
Table businesses_reviewed(SGR sgr, char *user_id);
Table businesses_with_stars_and_city(SGR sgr, float stars, char *city);
Table top_businesses_by_city(SGR sgr, int top);
Table international_users(SGR sgr);
Table top_businesses_with_category(SGR sgr, int top, char *category);
Table reviews_with_word(SGR sgr, char *word);

void addResults(SGR sgr, char* var, Table table);
Table getResults(SGR sgr, char* var);

#endif