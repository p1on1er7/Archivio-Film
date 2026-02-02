#ifndef FILM_H
#define FILM_H

#include <stdio.h>

typedef struct film {
    int id;
    char titolo[100];
    char regista[50];
    int anno;
    int durata;
    float voto;
    struct film* next;
} FILM;

typedef FILM* LINK;

/* 20059956 */
LINK crea_lista_vuota(void);
LINK aggiungi_in_coda(LINK l, FILM f);
void stampa_lista(LINK l);
int conta_lunghi(LINK l, int soglia);

/* ricerca / delete / media */
FILM* cerca_per_id(LINK l, int id);
FILM* cerca_per_titolo(LINK l, char* titolo);
void cerca_per_regista(LINK l, const char* regista);
LINK cancella_film(LINK l, int id);
float media_voti(LINK l);

/* mergesort + inversa */
LINK mergesort_film(LINK l);
void stampa_inversa(LINK l);

/* memoria */
void libera_lista(LINK l);

#endif
