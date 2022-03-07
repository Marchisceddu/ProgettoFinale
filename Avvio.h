#include "Partita.h"

//Macro funzione avvio
#define RISP_NUOVO_GIOCATORE 1
#define RISP_CARICA_SALVATAGGIO 2

//Macro funzione inserisciGiocatore
#define ID_VUOTO -1

//Macro funzione schermataPrincipale
#define RISP_INIZIO 1

//Richiamo delle funzioni
Salvataggio avvio ();
int inserisciGiocatori (Salvataggio);
void inserisciGiocatore (Giocatore*, int);
bool controlloGiocatori (Giocatore*, int, char[]);
void schermataPrincipale (Salvataggio);