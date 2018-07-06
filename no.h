#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

typedef struct no no_t;

no_t* cria_no(void* dado);

void liga_nos(no_t* no_p, no_t* no_s);

void desliga_no(no_t* no);
void desliga_no_anterior (no_t *no);
void desliga_no_proximo (no_t *no);

void* obtem_dado(no_t* no);

no_t* obtem_proximo(no_t* no);
no_t *obtem_anterior (no_t *no);


#endif // NO_H_INCLUDED
