# UPOalglib

Libreria di algoritmi e strutture dati astratte sviluppata presso l'[Istituto di Informatica](http://www.di.unipmn.it) dell'[Università del Piemonte Orientale](http://www.uniupo.it) per il corso di *Algorithm 1 - Lab*.

## Descrizione

UPOalglib è una libreria C che implementa varie strutture dati e algoritmi fondamentali per lo studio e l'applicazione pratica dell'algoritmica.

La libreria include:

- **Strutture dati**:
  - Alberi binari di ricerca (BST)
  - Tabelle hash (con implementazioni linear probing e separate chaining)
  - Stack

- **Algoritmi**:
  - Algoritmi di ordinamento (insertion sort, merge sort, quick sort)
  - Valutazione di espressioni in notazione postfissa

- **Utility**:
  - Timer ad alta risoluzione
  - Funzioni di input/output
  - Generazione di numeri casuali

## Struttura del progetto

```
UPOalglib/
├── apps/         # Applicazioni di esempio
├── bin/          # File binari compilati
├── data/         # File di dati di esempio
├── doc/          # Documentazione
├── include/      # File header pubblici
├── src/          # Implementazioni
└── test/         # Test unitari
```

## Compilazione

Per compilare l'intera libreria, le applicazioni e i test:

```bash
make all
```

Per compilare solo la libreria:

```bash
make bin
```

Per compilare le applicazioni di esempio:

```bash
make apps
```

Per eseguire i test:

```bash
make test
```

## Applicazioni di esempio

La libreria include diverse applicazioni di esempio:

- **sort_playlist.c**: Ordinamento di una playlist musicale
- **sort_playlist_multi.c**: Ordinamento di playlist multiple
- **postfix_eval.c**: Valutazione di espressioni matematiche in notazione postfissa
- **use_timer.c**: Esempio di utilizzo del modulo timer

Per eseguire un'applicazione di esempio:

```bash
./bin/sort_playlist data/playlist.txt
./bin/postfix_eval data/postfix.txt
```

## Documentazione

È possibile generare la documentazione API tramite Doxygen:

```bash
make doc
```

La documentazione sarà disponibile nella directory `doc/api`.

## Licenza

UPOalglib è distribuito sotto licenza GNU General Public License v3. Per ulteriori dettagli, consultare il file LICENSE.

## Autori

Sviluppato presso l'Istituto di Informatica dell'Università del Piemonte Orientale.
