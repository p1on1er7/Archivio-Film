#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "film.h"

FILM* cerca_per_id(LINK l, int id) {
    while (l) {
        if (l->id == id) return l;
        l = l->next;
    }
    return NULL;
}

FILM* cerca_per_titolo(LINK l, char* titolo) {
    while (l) {
        if (strcmp(l->titolo, titolo) == 0) return l;
        l = l->next;
    }
    return NULL;
}

void cerca_per_regista(LINK l, const char* regista) {
    int trovati = 0;
    while (l) {
        if (strcmp(l->regista, regista) == 0) {
            trovati = 1;
            printf("ID: %d | %s (%d) | %d min | voto %.2f\n",
                   l->id, l->titolo, l->anno, l->durata, l->voto);
        }
        l = l->next;
    }
    if (!trovati) printf("Nessun film trovato per regista: %s\n", regista);
}

LINK cancella_film(LINK l, int id) {
    if (!l) return NULL;

    if (l->id == id) {
        LINK nuova = l->next;
        free(l);
        return nuova;
    }

    LINK prev = l;
    LINK curr = l->next;
    while (curr) {
        if (curr->id == id) {
            prev->next = curr->next;
            free(curr);
            return l;
        }
        prev = curr;
        curr = curr->next;
    }
    return l;
}

typedef struct { float somma; int count; } Acc;

static Acc media_acc(LINK l) {
    if (!l) { Acc a = {0.0f, 0}; return a; }
    Acc r = media_acc(l->next);
    r.somma += l->voto;
    r.count += 1;
    return r;
}

float media_voti(LINK l) {
    Acc a = media_acc(l);
    if (a.count == 0) return 0.0f;
    return a.somma / (float)a.count;
}
