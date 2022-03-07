#include "Giochi.h"

//Macro funzione pre_partita
#define GIOCATORI_MINIMI 16

//Macro funzione giocoScrematura
#define MIN 0
#define MAX 999

//Macro funzione partita
#define N_GIOCHI_2_GIOCATORI 6
#define N_GIOCHI_4_GIOCATORI 2

//Macro identificative per i giochi
#define PARI_DISPARI 0
#define DADI 1
#define MORRA_CINESE 2
#define MURRA 3
#define TRIS 4
#define BIGLIE 5
#define PONTE_DI_VETRO 6
#define IMPICCATO 7

//Tipo strutturato per eseguire la scrematura
typedef struct {
    int **gruppiScrematura;
    int n_gruppiScrematura;
    int n_giocatori_per_gruppo;
    int giocatori_restanti;
} Scrematura;

//Richiamo delle funzioni
void pre_partita (Salvataggio);
void scrematura (Salvataggio);
Scrematura crea_GruppiScrematura (Salvataggio, Scrematura);
Scrematura  riempiGruppi_Scrematura (Scrematura, int, int, int, int);
Salvataggio giocoScrematura (Salvataggio, Scrematura);
void partita (Salvataggio);
Partita giocatori_in_gioco (Salvataggio, Partita);
void faseFinale (Salvataggio, Partita);
