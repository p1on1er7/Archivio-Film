#include <stdlib.h>
#include <stdio.h>
#include "film.h"

LINK crea_lista_vuota(void) {
    return NULL;
}

LINK aggiungi_in_coda(LINK l, FILM f) {
    LINK nuovo = (LINK)malloc(sizeof(FILM));
    if (!nuovo) {
        fprintf(stderr, "Errore: malloc fallita.\n");
        return l;
    }

    *nuovo = f;
    nuovo->next = NULL;

    if (l == NULL) return nuovo;

    LINK curr = l;
    while (curr->next != NULL) curr = curr->next;
    curr->next = nuovo;
    return l;
}

void stampa_lista(LINK l) {
    if (l == NULL) return;

    printf("ID: %d\n", l->id);
    printf("Titolo: %s\n", l->titolo);
    printf("Regista: %s\n", l->regista);
    printf("Anno: %d\n", l->anno);
    printf("Durata: %d minuti\n", l->durata);
    printf("Voto: %.2f\n", l->voto);
    printf("--------------------------\n");

    stampa_lista(l->next);
}

int conta_lunghi(LINK l, int soglia) {
    if (l == NULL) return 0;
    return (l->durata > soglia) + conta_lunghi(l->next, soglia);
}

void libera_lista(LINK l) {
    if (l == NULL) return;
    libera_lista(l->next);
    free(l);
}
