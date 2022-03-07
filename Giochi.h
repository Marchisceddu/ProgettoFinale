#include "Salvataggi.h"

//Macro generali giochi
#define GRANDEZZA_GRUPPI2 2
#define GRANDEZZA_GRUPPI4 4
#define GIOCATORE1 0
#define GIOCATORE2 1

//Macro per le funzioni di generazioni dei gruppi
#define RESETTA_RIGHE 0
#define RESETTA_COLONNE -1

//Macro funzione pari o dispari
#define DITA_MANO 5

//Macro funzione pari o dispari e biglie
#define PARI 2
#define DISPARI 1

//Macro funzione dadi
#define QUANTITA_DADI 2
#define FACCE_DADI 6

//Macro funzione MorraCinese
#define N_SIMBOLI 3
#define DIM_SIMBOLI 8

//Macro funzione Tris
#define RIGHE 3
#define COLONNE 3
#define PEDINA_X 1
#define PEDINA_O 2

//Macro funzione Murra
#define MAX_N_SCELTO 5
#define MIN_N_SCELTO 1
#define MAX_SOMMA_SCELTA 10
#define MIN_SOMMA_SCELTA 2

//Macro funzione Biglie
#define N_BIGLIE_GIOCATORE 10

//Macro funzione PonteVetro
#define LUNGHEZZA 3
#define LARGHEZZA 2
#define FRAGILE -1
#define VETRO_SINISTRA 0
#define VETRO_DESTRA 1

//Macro funzione Impiccato
#define DEFAULT_DICTIONARY "Dizionari/default.txt"
#define CUSTOM_DICTIONARY "Dizionari/custom.txt"
#define LUNGHEZZA_FRASI 120
#define N_MAX_FRASI 50
#define LETTERE_ALFABETO 26
#define CONVERSIONE_LETTERA 32
#define MAX_TENTATIVI 4

//Macro funzione riempiDizionario e inserisciGiocatori
#define DIM_SI_NO 3

//Macro funzione BlackJack
#define N_CARTE 13
#define MAX_NOMI_FIGURE 5
#define N_SEMI 4
#define MAX_NOMI_SEMI 7
#define ASSO11 11
#define ASSO1 1
#define MAX_RISCHIO 16
#define SOMMA_VITTORIA 21
#define MAX_CARTE_MANO 11

//Tipo strutturato per salvare informazioni sulla partita
typedef struct {
    int giocatoriRimasti;
    int *arrayGiocatoriRimasti;
    int giocatori_per_gruppo;
    int n_gruppi;
    int **gruppiGioco;
} Partita;

//Tipo strutturato dizionario
typedef struct {
    int n_frasi;
    char frasi[N_MAX_FRASI][LUNGHEZZA_FRASI];
} Dizionario;

//Creo un nuovo tipo di dato enumerazione "Simboli"
typedef enum {SASSO, CARTA, FORBICI} Simboli;

//Creo un nuovo tipo di dato enumerazione "Seme"
typedef enum {CUORI, QUADRI, PICCHE, FIORI} Seme;

//Creo un nuovo tipo di dato enumerazione "Figura"
typedef enum {ASSO, DUE, TRE, QUATRO, CINQUE, SEI, SETTE, OTTO, NOVE, DIECI, J, Q, K} Figura;

//Tip strutturato carta
typedef struct {
    Seme seme;
    Figura figura;
    int valore;
} Carta;

//Richiamo delle funzioni generali
Partita creaGruppi_Partita (Partita, int);
int Frontman_dello_SPR1D_GAME (int, char[], int);

//Richiamo delle funzioni dei giochi
Salvataggio PariDispari (Salvataggio, Partita);
Salvataggio Dadi (Salvataggio, Partita);
Salvataggio MorraCinese (Salvataggio, Partita);
Salvataggio Murra (Salvataggio, Partita);
Salvataggio Biglie (Salvataggio, Partita);
Salvataggio PonteVetro (Salvataggio, Partita);

Salvataggio Tris (Salvataggio, Partita);
void aiTris (int[][COLONNE], int, int);

Salvataggio Impiccato (Salvataggio, Partita);
Dizionario scegliDizionario ();
void riempiDizionario (char[]);
bool controlloFrase (char[]);
Dizionario leggiDizionario ();

bool BlackJack (Salvataggio, Partita);