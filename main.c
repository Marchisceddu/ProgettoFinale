/*---------------------------------------------------------------------------------------------------*\
| Autore: Pilia Marco                                                                                 |
| Matricola: N.66134                                                                                  |
| Scopo:  SPR1D GAME (chi viene eliminato ripeterà PR1 l'anno prossimo)                               |
\*---------------------------------------------------------------------------------------------------*/

#include "Avvio.h"

int main() {

    //Dichiarazione variabili
    Salvataggio salvataggio;

    salvataggio.arrayGiocatori = NULL;
    salvataggio.giocatoriUtente_partecipanti = NULL;
    salvataggio.giocatori_in_gioco = NULL;

    //Generazione del seme per la funzione genera numero randomico
    srand(time(NULL));

    //Richiamo la funzione di avvio
    salvataggio=avvio();

    //Se la partita non è ancora iniziata esegue:
    if (salvataggio.partita_in_corso==VUOTO)
    {
        //Richiamo la funzione di schermata principale
        schermataPrincipale(salvataggio);
    }
        //Se si riprende una partita in corso esegue:
    else
    {
        //Richiamo la funzione partita
        partita(salvataggio);
    }

    //Libero la memoria allocata dinamicamente
    free(salvataggio.arrayGiocatori);
    free(salvataggio.giocatoriUtente_partecipanti);
    free(salvataggio.giocatori_in_gioco);

    return 0;
}