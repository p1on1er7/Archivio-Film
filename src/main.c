#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "film.h"

static void trim_newline(char* s) { s[strcspn(s, "\n")] = '\0'; }

static int leggi_int(const char* prompt) {
    int x;
    printf("%s", prompt);
    while (scanf("%d", &x) != 1) {
        printf("Input non valido. Riprova: ");
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
    }
    int c; while ((c = getchar()) != '\n' && c != EOF) {}
    return x;
}

static float leggi_float(const char* prompt) {
    float x;
    printf("%s", prompt);
    while (scanf("%f", &x) != 1) {
        printf("Input non valido. Riprova: ");
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
    }
    int c; while ((c = getchar()) != '\n' && c != EOF) {}
    return x;
}

static void leggi_stringa(const char* prompt, char* buf, size_t n) {
    printf("%s", prompt);
    if (!fgets(buf, (int)n, stdin)) { buf[0] = '\0'; return; }
    trim_newline(buf);
}

static void stampa_film_singolo(const FILM* f) {
    printf("ID: %d\nTitolo: %s\nRegista: %s\nAnno: %d\nDurata: %d\nVoto: %.2f\n",
           f->id, f->titolo, f->regista, f->anno, f->durata, f->voto);
}

static void stampa_menu(void) {
    printf("\n=== ARCHIVIO FILM ===\n");
    printf("0) Esci dal programma\n");
    printf("1) Inserisci nuovo film\n");
    printf("2) Elimina film dall'archivio\n");
    printf("3) Cerca film (ID / titolo / regista)\n");
    printf("4) Elenca film con durata superiore a N\n");
    printf("5) Calcola media voti totale dell'archivio\n");
    printf("6) Ordina archivio per anno di uscita\n");
    printf("7) Stampa archivio (ordine corrente)\n");
    printf("8) Stampa archivio in ordine inverso\n");
    printf("Scelta: ");
}

int main(void) {
    LINK archivio = crea_lista_vuota();

    for (;;) {
        stampa_menu();

        int scelta;
        if (scanf("%d", &scelta) != 1) {
            printf("Input non valido.\n");
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }
        int c; while ((c = getchar()) != '\n' && c != EOF) {}

        if (scelta == 0) {
            printf("Uscita dal programma...\n");
            break;
        }

        switch (scelta) {
            case 1: {
                FILM f;
                f.id = leggi_int("ID: ");
                leggi_stringa("Titolo: ", f.titolo, sizeof(f.titolo));
                leggi_stringa("Regista: ", f.regista, sizeof(f.regista));
                f.anno = leggi_int("Anno di uscita: ");
                f.durata = leggi_int("Durata (minuti): ");
                f.voto = leggi_float("Voto: ");
                f.next = NULL;

                archivio = aggiungi_in_coda(archivio, f);
                printf("Operazione completata: film inserito.\n");
            } break;

            case 2: {
                if (archivio == NULL) {
                    printf("Operazione non eseguibile: archivio vuoto.\n");
                    break;
                }
                int id = leggi_int("ID del film da eliminare: ");
                FILM* trovato = cerca_per_id(archivio, id);
                if (!trovato) {
                    printf("Operazione completata: nessun film con ID %d trovato.\n", id);
                } else {
                    archivio = cancella_film(archivio, id);
                    printf("Operazione completata: film con ID %d eliminato.\n", id);
                }
            } break;

            case 3: {
                if (archivio == NULL) {
                    printf("Archivio vuoto.\n");
                    break;
                }
                printf("\n--- Ricerca film ---\n");
                printf("1) Cerca per ID\n");
                printf("2) Cerca per titolo\n");
                printf("3) Cerca per regista\n");
                printf("0) Indietro\n");
                int sub = leggi_int("Scelta: ");

                if (sub == 1) {
                    int id = leggi_int("ID da cercare: ");
                    FILM* f = cerca_per_id(archivio, id);
                    if (!f) printf("Nessun film trovato con ID %d.\n", id);
                    else stampa_film_singolo(f);
                } else if (sub == 2) {
                    char titolo[100];
                    leggi_stringa("Titolo: ", titolo, sizeof(titolo));
                    FILM* f = cerca_per_titolo(archivio, titolo);
                    if (!f) printf("Nessun film trovato con titolo '%s'.\n", titolo);
                    else stampa_film_singolo(f);
                } else if (sub == 3) {
                    char reg[50];
                    leggi_stringa("Regista: ", reg, sizeof(reg));
                    cerca_per_regista(archivio, reg);
                }
            } break;

            case 4: {
                if (archivio == NULL) {
                    printf("Archivio vuoto.\n");
                    break;
                }
                int n = leggi_int("Inserisci N (minuti): ");
                int count = conta_lunghi(archivio, n);
                printf("Film con durata > %d: %d\n", n, count);

                LINK cur = archivio;
                int stampati = 0;
                while (cur) {
                    if (cur->durata > n) {
                        stampati = 1;
                        printf("ID: %d | %s | %d min\n", cur->id, cur->titolo, cur->durata);
                    }
                    cur = cur->next;
                }
                if (!stampati) printf("Nessun film supera la soglia.\n");
            } break;

            case 5: {
                if (archivio == NULL) {
                    printf("Archivio vuoto. Media = 0.\n");
                    break;
                }
                float m = media_voti(archivio);
                printf("Media voti archivio: %.2f\n", m);
            } break;

            case 6: {
                if (archivio == NULL || archivio->next == NULL) {
                    printf("Operazione completata: archivio già ordinato (0 o 1 film).\n");
                } else {
                    archivio = mergesort_film(archivio);
                    printf("Operazione completata: archivio ordinato per anno di uscita.\n");
                }
            } break;

            case 7: {
                if (archivio == NULL) printf("Archivio vuoto.\n");
                else stampa_lista(archivio);
            } break;

            case 8: {
                if (archivio == NULL) printf("Archivio vuoto.\n");
                else stampa_inversa(archivio);
            } break;

            default:
                printf("Scelta non valida.\n");
                break;
        }
    }

    libera_lista(archivio);
    return 0;
}
