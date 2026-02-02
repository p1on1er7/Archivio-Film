# Relazione Progetto – Archivio Film
**Corso:** Programmazione 2  
**Studente:** Cenedese Martino  
**Matricola:** 20059956  
**Componenti del gruppo:** 20041492, 20057103  

---

## 1. Obiettivo del progetto
Il progetto consiste nella realizzazione di un’applicazione in linguaggio C per la gestione di un archivio di film.
L’archivio permette l’inserimento, la ricerca, la cancellazione, l’ordinamento e l’analisi dei dati relativi ai film,
utilizzando strutture dati dinamiche e algoritmi studiati durante il corso.

---

## 2. Struttura dei dati
L’archivio è implementato tramite una **lista concatenata semplice**.
Ogni nodo della lista rappresenta un film ed è descritto dalla seguente struttura:

- ID
- Titolo
- Regista
- Anno di uscita
- Durata
- Voto
- Puntatore al nodo successivo

La scelta della lista concatenata è motivata dal fatto che il numero di film non è noto a priori
e consente una gestione dinamica ed efficiente della memoria.

---

## 3. Struttura del progetto
Il progetto è organizzato in modo modulare:

- `film.h`: definizione della struttura dati e dei prototipi delle funzioni
- `studente1.c`: gestione della lista e operazioni di base (creazione, inserimento, stampa, liberazione memoria)
- `studente2.c`: funzioni di ricerca, cancellazione e calcolo della media dei voti
- `studente3.c`: algoritmi avanzati (MergeSort e stampa inversa)
- `main.c`: gestione del menu e coordinamento delle funzionalità

Questa suddivisione permette una maggiore leggibilità del codice e una separazione chiara delle responsabilità.

---

## 4. Funzionalità implementate
L’applicazione offre le seguenti funzionalità:

- Inserimento di nuovi film nell’archivio
- Eliminazione di un film tramite ID
- Ricerca di film per ID, titolo o regista
- Elenco dei film con durata superiore a una soglia definita dall’utente
- Calcolo della media dei voti dei film presenti nell’archivio
- Ordinamento dell’archivio per anno di uscita (con criterio secondario sul titolo)
- Stampa dell’archivio in ordine corrente
- Stampa dell’archivio in ordine inverso

---

## 5. Gestione della memoria
La memoria dinamica viene gestita tramite `malloc` e `free`.
Ogni nodo della lista viene allocato dinamicamente al momento dell’inserimento
e correttamente deallocato in fase di cancellazione o alla chiusura del programma.

È presente una funzione dedicata alla liberazione completa della lista (`libera_lista`),
chiamata al termine dell’esecuzione per evitare memory leak.

---

## 6. Ricorsione
Nel progetto vengono utilizzate diverse funzioni ricorsive, tra cui:

- Stampa della lista
- Stampa della lista in ordine inverso
- Conteggio dei film con durata superiore a una soglia
- Calcolo della media dei voti

L’uso della ricorsione risulta naturale nel contesto delle liste concatenate,
poiché ogni nodo può essere visto come una lista più piccola.

---

## 7. Algoritmo di ordinamento (MergeSort)
Per l’ordinamento dell’archivio è stato utilizzato l’algoritmo **MergeSort**,
particolarmente adatto alle liste concatenate.

L’algoritmo opera in tre fasi:
1. Suddivisione della lista in due sottoliste tramite la tecnica dei puntatori lento/veloce
2. Ordinamento ricorsivo delle sottoliste
3. Fusione ordinata delle sottoliste

Il criterio di ordinamento adottato è:
- Anno di uscita (crescente)
- Titolo (come chiave secondaria)

La complessità temporale dell’algoritmo è **O(n log n)**.

---

## 8. Conclusioni
Il progetto soddisfa tutti i requisiti richiesti e dimostra l’utilizzo corretto di:
- strutture dati dinamiche
- gestione della memoria
- ricorsione
- algoritmi di ordinamento
- progettazione modulare del codice

L’applicazione risulta funzionale, estendibile e coerente con gli obiettivi del corso.
