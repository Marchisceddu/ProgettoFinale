#include "Avvio.h"

//Funzione di avvio gioco
Salvataggio avvio ()
{
    //Dichiarazioni variabili locali
    Salvataggio salvataggio;
    int risp;

    salvataggio.arrayGiocatori = NULL;
    salvataggio.giocatoriUtente_partecipanti = NULL;
    salvataggio.giocatori_in_gioco = NULL;

    //Alloca dinamicamente lo spazio per un giocatore
    salvataggio.arrayGiocatori = (Giocatore*) malloc(sizeof(Giocatore));

    //Controllo se la memoria per il puntatore è stata allocata correttamente
    if( salvataggio.arrayGiocatori == NULL )
        exit(-1);

    //Output introduzione
    printf("\n-----------------------------------> SPR1D GAME <----------------------------------\n"
           "Benvenuto, riuscirai a superare Programmazione 1 o dovrai ritentare un'altro anno?\n"
           "               Attenzione il professore Riccardo Scateni e' severo\n"
           "---------------------------------> Buona Fortuna <---------------------------------\n");

    //Output della domanda
    printf("Cosa vuoi fare?\n"
           "1) Inserisci un nuovo giocatore\n"
           "2) Carica un file di salvataggio\n");
    //Richiesta input
    scanf("%d", &risp);
    while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

    //Ciclo per continuare a far inserire la risposta in caso in cui non sia una delle due richieste
    while (risp!=RISP_NUOVO_GIOCATORE && risp!=RISP_CARICA_SALVATAGGIO)
    {
        printf("\nATTENZIONE!\n"
               "Inserire uno dei due numeri richiesti\n");
        scanf("%d", &risp);
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio
    }

    //Se la risposta precedente è 1 esegue:
    if (risp==RISP_NUOVO_GIOCATORE)
    {
        salvataggio.partita_in_corso=false; //Setta la variabile della partita in corso a 0 perché non ancora iniziata

        //Richiamo la funzione per inserire n giocatori
        salvataggio.K_giocatoriCreati = inserisciGiocatori(salvataggio);
    }
    //Se la risposta precedente è 2 esegue:
    else if (risp==RISP_CARICA_SALVATAGGIO)
    {
        //Richiamo la funzione per caricare un salvataggio
        salvataggio = caricaSalvataggio(salvataggio);
    }

    return salvataggio;
}

//Funzione per inserire n giocatori
int inserisciGiocatori (Salvataggio salvataggio)
{
    //Dichiarazione variabili locali
    bool controlloSI=false, controlloNO=false;
    char risp[DIM_SI_NO];
    int posizione=0;

    do //Ciclo per continuare a chiedere se vuole inserire un giocatore
    {
        //Richiama la funzione per inserire un giocatore
        inserisciGiocatore(salvataggio.arrayGiocatori, posizione);

        do //Ciclo per continuare a far inserire la risposta in caso in cui non sia o si o no
        {
            //Ripristina le variabili di controllo
            controlloNO = false;
            controlloSI = false;

            //Output della domanda
            printf("\nVuoi inserire un nuovo giocatore? si/no :");
            //Richiesta input
            scanf("%2s", risp);
            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

            //Se la risposta è uguale a no esegue:
            if (strcmp(risp, "NO")==false || strcmp(risp, "No")==false || strcmp(risp, "nO")==false || strcmp(risp, "no")==false)
            {
                controlloNO = true; //Aggiorna la variabile di controllo del no
            }
            //Se la risposta è uguale a si esegue:
            else if (strcmp(risp, "SI")==false || strcmp(risp, "Si")==false || strcmp(risp, "sI")==false || strcmp(risp, "si")==false)
            {
                controlloSI = true; //Aggiorna la variabile di controllo del si
                posizione++; //Aumenta di un unità la variabile posizione

                //Aumenta lo spazio allocato dinamicamente per poter far inserire un nuovo giocatore
                salvataggio.arrayGiocatori = (Giocatore*) realloc(salvataggio.arrayGiocatori, (sizeof(Giocatore)*(posizione+1)));
                //Controllo se la memoria per il puntatore è stata allocata correttamente
                if( salvataggio.arrayGiocatori == NULL )
                    exit(-1);
            }
            //Altrimenti esegue:
            else
            {
                printf("\nDevi inserire o si o no\n");
            }
        } while (controlloSI==false && controlloNO==false);
    } while (controlloNO==false);

    //Restituisce il numero dei giocatori creati dall'utente
    return posizione + 1;
}

//Funzione per inserire un giocatore
void inserisciGiocatore (Giocatore* arrayGiocatori, int posizione)
{
    //Dichiarazione variabili locali
    bool controllo;
    char nome[DIM_NOME_COGNOME];

    do //Ciclo per continuare a far inserire il nome del giocatore in caso quello inserito sia già presente
    {
        //Output della domanda
        printf("\nCome si chiama il giocatore?\n"
               "  (massimo 63 caratteri)  \n");
        //Richiesta input
        scanf("%63[^\n]", nome);
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        //Controlla che il nome non sia già presente nell array dei giocatori
        controllo = controlloGiocatori(arrayGiocatori, posizione, nome);

        //Sette le altre variabili della struttura a 0 e l'id a -1
        arrayGiocatori[posizione].id = ID_VUOTO;
        arrayGiocatori[posizione].n_SPR1D_GAME_vinti = VUOTO;
        arrayGiocatori[posizione].n_SPR1D_GAME_giocati = VUOTO;
        arrayGiocatori[posizione].n_finali_giocate = VUOTO;
        arrayGiocatori[posizione].n_tot_minigiochi_giocati = VUOTO;
        arrayGiocatori[posizione].n_tot_minigiochi_vinti = VUOTO;

        //Se il giocatore inserito si chiama Riccardo Scateni attiva il trucco:
        if (strcmp(arrayGiocatori[posizione].nome, "Riccardo Scateni")==false)
        {
            printf("Hai attivato il trucco Frontman dello SPR1D GAME\n");
        }

    } while (controllo==false);
}

//Funzione per controllare che non ci siano due giocatori con lo stesso nome
bool controlloGiocatori (Giocatore* arrayGiocatori, int posizione, char nome[])
{
    //Dichiarazione variabili locali
    bool controllo=false;

    //Esegue il ciclo fino al numero di posizione del array
    for (int i = 0; i < posizione; ++i)
    {
        //Controlla se il nome appena inserito non sia già presente nell array dei giocatori
        if (i!=posizione && strcmp(nome, arrayGiocatori[i].nome)==false)
        {
            controllo = true; //Se vine trovato un giocatore con lo stesso nome modifica la variabile di controllo
        }
    }

    //Se trova già due giocatori con lo stesso nome restituisce false e un messaggio di errore
    if (controllo==true)
    {
        printf("\nIl nome e' gia' stato usato\n"
               "Inserire nuovamente\n");
        return false;
    }

    //Altrimenti inserisce il nome del giocatore nell array di giocatori e restituisce true
    strcpy(arrayGiocatori[posizione].nome, nome);
    return true;
}

//Funzione schermata principale
void schermataPrincipale (Salvataggio salvataggio)
{
    //Dichiarazioni variabili locali
    int risp;

    //Output della domanda
    printf("\nCosa vuoi fare?\n"
           "1) Iniziare un nuova partita\n"
           "2) Uscire dal gioco\n"
           "3) Salvare i dati dei giocatori inseriti\n");
    //Richiesta input
    scanf("%d", &risp);
    while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

    //Ciclo per continuare a far inserire la risposta in caso in cui non sia una delle tre richieste
    while (risp!=RISP_SALVARE && risp!=RISP_INIZIO && risp!=RISP_USCITA)
    {
        printf("\nATTENZIONE!\n"
               "Inserire uno dei tre numeri richiesti\n");
        scanf("%d", &risp);
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio
    }

    //Se la risposta precedente è SALVARE esegue:
    if (risp==RISP_SALVARE)
    {
        //Richiamo la funzione del salvataggio
        salva(salvataggio);

        //Output della domanda
        printf("\nCosa vuoi fare?\n"
               "1) Iniziare un nuova partita\n"
               "2) Uscire dal gioco\n");
        //Richiesta input
        scanf("%d", &risp);
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        //Ciclo per continuare a far inserire la risposta in caso in cui non sia una delle due richieste
        while (risp!=RISP_INIZIO && risp!=RISP_USCITA)
        {
            printf("\nATTENZIONE!\n"
                   "Inserire uno dei due numeri richiesti\n");
            scanf("%d", &risp);
            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio
        }
    }
    //Se la risposta precedente è INIZIARE esegue:
    if (risp==RISP_INIZIO)
    {
        pre_partita(salvataggio);
    }
    //Se la risposta precedente è USCIRE esegue:
    else if (risp==RISP_USCITA)
    {
        return; //Ritorna il controllo al main
    }
}