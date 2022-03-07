#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

//Macro generali
#define DIM_NOME_COGNOME 64
#define VUOTO 0
#define RISP_CONTINUARE 1
#define RISP_USCITA 2
#define RISP_SALVARE 3

//Macro funzioni salvataggi
#define INDIRIZZO_FILE_SALVATAGGI "Salvataggi/FileSalvataggi.txt"
#define DIM_NOME_FILE 46
#define QUANTITA 1
#define NUOVO_FILE 1
#define VECCHIO_FILE 2

//Tipo strutturato giocatore
typedef struct {
    int id;
    char nome[DIM_NOME_COGNOME];
    int n_SPR1D_GAME_vinti;
    int n_SPR1D_GAME_giocati;
    int n_finali_giocate;
    int n_tot_minigiochi_giocati;
    int n_tot_minigiochi_vinti;
} Giocatore;

//Tipo strutturato per tutti i dati da salvare
typedef struct {
    int K_giocatoriCreati;
    Giocatore *arrayGiocatori;
    int partita_in_corso;
    int N_partecipanti;
    int M_controlloUtente;
    int *giocatoriUtente_partecipanti;
    int *giocatori_in_gioco;
} Salvataggio;

//Richiamo delle funzioni
void eliminaSalvataggi ();
void salva (Salvataggio);
char** leggiFileSalvataggi (char**, int*);
void inserisciSalvataggio (char**, int*, char*);
void stampaFileSalvataggi ();
void selezionaSalvataggio (char**, int, char*);
void salvaDati (char*, Salvataggio);
Salvataggio caricaSalvataggio (Salvataggio);