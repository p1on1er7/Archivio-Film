#include <stdlib.h>
#include <string.h>
#include "film.h"

static int cmp_film(const FILM* a, const FILM* b) {
    if (a->anno != b->anno) return (a->anno < b->anno) ? -1 : 1;
    int t = strcmp(a->titolo, b->titolo);
    if (t < 0) return -1;
    if (t > 0) return 1;
    return 0;
}

static void split_list(LINK source, LINK* front, LINK* back) {
    if (!source || !source->next) {
        *front = source;
        *back = NULL;
        return;
    }

    LINK slow = source;
    LINK fast = source->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

static LINK merge_sorted(LINK a, LINK b) {
    if (!a) return b;
    if (!b) return a;

    if (cmp_film(a, b) <= 0) {
        a->next = merge_sorted(a->next, b);
        return a;
    } else {
        b->next = merge_sorted(a, b->next);
        return b;
    }
}

LINK mergesort_film(LINK l) {
    if (!l || !l->next) return l;

    LINK a = NULL, b = NULL;
    split_list(l, &a, &b);

    a = mergesort_film(a);
    b = mergesort_film(b);

    return merge_sorted(a, b);
}

void stampa_inversa(LINK l) {
    if (!l) return;
    stampa_inversa(l->next);
    printf("ID: %d | %s | %s | %d | %d min | voto %.2f\n",
           l->id, l->titolo, l->regista, l->anno, l->durata, l->voto);
}
