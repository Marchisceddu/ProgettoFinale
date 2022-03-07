#include "Partita.h"

//Funzione per inserire i giocatori partecipanti alla partita
void pre_partita (Salvataggio salvataggio)
{
    //Dichiarazioni variabili locali
    int risp;
    bool controllo=false;

    do //Ciclo per continuare a far inserire il numero dei giocatori in caso quello inserito sia minore del numero minimo
    {
        //Output della domanda
        printf("\nQuanti giocatori parteciperanno al gioco?\n"
               "         (minimo %d giocatori)         \n", GIOCATORI_MINIMI);
        //Richiesta input
        scanf("%d", &salvataggio.N_partecipanti);
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        //Stampa un messaggio di errore se N risulta essere minore del numero minimo
        if (salvataggio.N_partecipanti < GIOCATORI_MINIMI)
        {
            printf("\nATTENZIONE\n");
            printf("Inserire minimo %d giocatori\n", GIOCATORI_MINIMI);
        }
    } while (salvataggio.N_partecipanti < GIOCATORI_MINIMI);

    do //Ciclo per continuare a far inserire il numero dei giocatori in caso quello inserito sia maggiore di N o dei giocatori inseriti a inizio partita
    {
        controllo = false;

        //Output della domanda
        printf("\nQuanti giocatori sono controllati dall'utente?\n");
        //Richiesta input
        scanf("%d", &salvataggio.M_controlloUtente);
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        //Stampa un messaggio di errore se M risulta essere maggiore di M
        if (salvataggio.M_controlloUtente > salvataggio.N_partecipanti)
        {
            printf("\nATTENZIONE\n");
            printf("I giocatori devono essere minori o uguali a %d\n", salvataggio.N_partecipanti);
            controllo = true;
        }
        //Stampa un messaggio di errore se M risulta essere maggiore del numero di giocatori inseriti a inizio partita
        else if (salvataggio.M_controlloUtente > salvataggio.K_giocatoriCreati)
        {
            printf("\nATTENZIONE\n");
            printf("I giocatori devono essere minori o uguali a %d\n", salvataggio.K_giocatoriCreati);
            controllo = true;
        }
        //Stampa un messaggio di errore se M risulta essere negativo
        else if (salvataggio.M_controlloUtente < 0)
        {
            printf("\nATTENZIONE\n");
            printf("Devi inserire un numero maggiore di 0\n");
            controllo = true;
        }
    } while (controllo==true);

    //Alloco dinamicamente la memoria all array d'interi che conterrà gli indici dei giocatori utenti partecipanti alla partita
    salvataggio.giocatoriUtente_partecipanti = (int*) malloc(sizeof(int)*salvataggio.M_controlloUtente);
    //Controllo se la memoria per il puntatore è stata allocata correttamente
    if( salvataggio.giocatoriUtente_partecipanti == NULL )
        exit(-1);

    //Alloco dinamicamente la memoria all array d'interi in cui sarà indicato se i giocatori sono ancora in gioco o sono eliminati
    salvataggio.giocatori_in_gioco = (int*) malloc(sizeof(int)*salvataggio.N_partecipanti);
    //Controllo se la memoria per il puntatore è stata allocata correttamente
    if( salvataggio.giocatori_in_gioco == NULL )
        exit(-1);

    //Ciclo per far inserire all'utente i profili giocatori da utilizzare durante la partita
    for (int i = 0; i < salvataggio.M_controlloUtente; ++i)
    {
        //Output della domanda
        printf("\nQuale profilo vuoi usare per il giocatore n.%d?\n", i+1);
        //Ciclo per stampare tutti i nomi dei giocatori inseriti in precedenza
        for (int j = 0; j < salvataggio.K_giocatoriCreati; ++j)
        {
            printf("%d) %s\n", j, salvataggio.arrayGiocatori[j].nome);
        }

        do //Ciclo per continuare a far inserire il numero del giocatore da usare in caso quello inserito non risulti nell'elenco
        {
            controllo = false;

            printf("Inserisci numero:");
            //Richiesta input
            scanf("%d", &risp);
            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

            //Stampa un messaggio di errore in caso il numero inserito non risulti nell'elenco
            if (risp < 0 || risp >= salvataggio.K_giocatoriCreati)
            {
                printf("\nATTENZIONE\n");
                printf("Inserire un numero collegato ad un profilo esistente\n");
                controllo = true;
            }

            //Stampa un messaggio di errore in caso il numero della indice del giocatore inserito sia già stato scelto
            for (int j = 0; j < salvataggio.M_controlloUtente; ++j) {
                if (risp==salvataggio.giocatoriUtente_partecipanti[j])
                {
                    printf("\nATTENZIONE\n");
                    printf("Il giocatore %s e' gia' stato inserito\n", salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[j]].nome);
                    controllo = true;
                }
            }
        } while (controllo==true);

        //Salva nell array dei giocatori partecipanti controllati dall'utente l'indice del giocatore scelto per partecipare
        salvataggio.giocatoriUtente_partecipanti[i] = risp;

        do //Ciclo per continuare a far inserire l'id del giocatore in caso quello inserito sia già stato usato o supera il numero dei giocatori partecipanti
        {
            controllo = false;

            printf("Inserisci l'id (compreso tra 0 e %d):", salvataggio.N_partecipanti-1);
            //Richiesta input
            scanf("%d", &risp);
            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

            //Stampa un messaggio di errore in caso il numero inserito sia < di 0 o >= dei giocatori partecipanti
            if (risp < 0 || risp >= salvataggio.N_partecipanti)
            {
                printf("\nATTENZIONE\n");
                printf("Inserire un numero compreso tra 0 e %d\n", salvataggio.N_partecipanti-1);
                controllo = true;
            }

            //Stampa un messaggio di errore in caso il numero inserito sia già presente negli id dei giocatori partecipanti
            for (int j = 0; j <= i; ++j) {
                if(risp==salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[j]].id)
                {
                    printf("\nATTENZIONE\n");
                    printf("L'id %d e' gia' stato inserito\n", risp);
                    controllo = true;
                }
            }
        } while (controllo==true);

        //Salva nell array dei giocatori l'id scelto per partecipare
        salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[i]].id = risp;

        //Incrementa il numero di SPR1D_GAME giocati del giocatore selezionato
        salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[i]].n_SPR1D_GAME_giocati++;
    }

    //Richiamo la funzione per la scrematura
    scrematura(salvataggio);
}

//Funzione per la scrematura
void scrematura (Salvataggio salvataggio)
{
    //Dichiarazioni variabili locali
    Scrematura variabili_scrematura;

    variabili_scrematura.gruppiScrematura = NULL;

    //Richiama la funzione per creare i gruppi per la scrematura
    variabili_scrematura = crea_GruppiScrematura(salvataggio, variabili_scrematura);

    //Richiama la funzione per eseguire il gioco della scrematura
    salvataggio = giocoScrematura(salvataggio, variabili_scrematura);

    //Libera la memoria allocata dinamicamente
    free(variabili_scrematura.gruppiScrematura);

    //Richiama la funzione per iniziare la partita
    partita(salvataggio);
}

//Funzione per creare i gruppi per la scrematura
Scrematura crea_GruppiScrematura (Salvataggio salvataggio, Scrematura variabili_scrematura)
{
    //Dichiarazioni variabili locali
    int potenza_di_due;

    //Calcolo l'esponente della potenza di due strettamente minore degli N partecipanti e li sottraggo 1
    potenza_di_due = (int) log2f(salvataggio.N_partecipanti-1);
    //Determino quanti gruppi si devono formare per la scrematura e assegno il valore alla variabile n_gruppiScrematura
    variabili_scrematura.n_gruppiScrematura = (int) pow(2, potenza_di_due-1);

    //Calcolo i gruppi che avranno un giocatore in più (dispari)
    variabili_scrematura.giocatori_restanti = salvataggio.N_partecipanti % variabili_scrematura.n_gruppiScrematura;
    //Calcolo i giocatori che faranno parte in ogni gruppo
    variabili_scrematura.n_giocatori_per_gruppo = salvataggio.N_partecipanti / variabili_scrematura.n_gruppiScrematura;

    //Alloco dinamicamente le righe della matrice per poter contenere tutti i gruppi creati
    variabili_scrematura.gruppiScrematura = (int**) malloc(sizeof(int*)*variabili_scrematura.n_gruppiScrematura);
    //Controllo se la memoria per il puntatore è stata allocata correttamente
    if( variabili_scrematura.gruppiScrematura == NULL )
        exit(-1);

    //Riempio i gruppi con un giocatore in più
    variabili_scrematura = riempiGruppi_Scrematura(variabili_scrematura, salvataggio.N_partecipanti, 0, variabili_scrematura.giocatori_restanti, variabili_scrematura.n_giocatori_per_gruppo + 1);

    //Riempio i gruppi normali
    variabili_scrematura = riempiGruppi_Scrematura(variabili_scrematura, salvataggio.N_partecipanti, variabili_scrematura.giocatori_restanti, variabili_scrematura.n_gruppiScrematura, variabili_scrematura.n_giocatori_per_gruppo);

    //Ritorna le variabili utili per la scrematura alla subroutine chiamante
    return variabili_scrematura;
}

//Funzione per riempire i gruppi con giocatori normali
Scrematura  riempiGruppi_Scrematura (Scrematura variabili_scrematura, int N_partecipanti, int pos_partenza, int pos_arrivo, int giocatori_gruppo)
{
    //Dichiarazioni variabili locali
    int giocatoreSelezionato;
    bool controllo=false, controllo_sottrazione=false;

    //Ciclo per formare i numero dei gruppi (con giocatori pari) per la scrematura
    for (int i = pos_partenza; i < pos_arrivo; ++i)
    {
        //Alloco dinamicamente le colonne della matrice per poter contenere tutti i giocatori appartenenti al gruppo
        variabili_scrematura.gruppiScrematura[i] = (int*) malloc(sizeof(int)*(variabili_scrematura.n_giocatori_per_gruppo+1));
        //Controllo se la memoria per il puntatore è stata allocata correttamente
        if( variabili_scrematura.gruppiScrematura[i] == NULL )
            exit(-1);

        //Ciclo per riempire con un numero le posizioni allocate per essere sicuro che in quelle posizioni non ci sia un numero che potrebbe dare problemi al controllo successivo
        for (int j = 0; j <= variabili_scrematura.n_giocatori_per_gruppo; ++j) {
            //Inserisce il numero N (che non è un numero degli id e quindi non è un numero generato randomicamente)
            variabili_scrematura.gruppiScrematura[i][j]=N_partecipanti;
        }

        //Ciclo per generare randomicamente n_giocatori_per_gruppo da inserire all'interno del gruppo d'indice i
        for (int j = 0; j < giocatori_gruppo; ++j)
        {
            giocatoreSelezionato = rand() % N_partecipanti; //Genera un numero random tra 0 e N-1
            controllo_sottrazione = false;

            do  //Ciclo per continuare a far cambiare il numero generato in caso non si riesca a trovare un numero mancante nei gruppi
            {
                //Esegue il ciclo un numero di volte pari al numero di gruppi già allocati
                for (int k = 0; k <= i; ++k)
                {
                    //Esegue il ciclo un numero di volte pari al numero di giocatori presenti nel gruppo appena allocato
                    for (int l = 0; l <= variabili_scrematura.n_giocatori_per_gruppo; ++l)
                    {
                        //Se il numero generato casualmente è già presente all'interno dell array dei gruppi esegue:
                        if (giocatoreSelezionato==variabili_scrematura.gruppiScrematura[k][l])
                        {
                            //Se il numero generato è pari all'ultimo numero disponibile o se il controllo della sottrazione è attivo esegue;
                            if (giocatoreSelezionato==(N_partecipanti-1) || (controllo_sottrazione==true && giocatoreSelezionato!=0))
                            {
                                giocatoreSelezionato--; //Decrementa il numero generato randomicamente
                                controllo_sottrazione = true; //Setta la variabile del controllo sottrazione a true per far continuare a decrementare il numero in caso sia ancora uguale a uno già presente nell array di gruppi
                            }
                                //Altrimenti esegue:
                            else
                            {
                                giocatoreSelezionato++; //Incrementa il numero generato randomicamente
                            }
                            //Resetta le variabili di controllo dei cicli for per farli ripetere da capo
                            k = RESETTA_RIGHE;
                            l = RESETTA_COLONNE; //Setto la variabile a -1 perché rieseguendo il ciclo la prima volta viene incrementata, in modo da portarla a 0 e poter controllare tutte le posizioni
                            controllo = true;
                        }
                            //Altrimenti esegue:
                        else
                        {
                            controllo = false; //Setta la variabile di controllo a false per permettere di uscire dal ciclo do-while
                        }
                    }
                }
            } while (controllo==true);
            //Inserisce il numero generato all'interno del gruppo di posizione [i][j]
            variabili_scrematura.gruppiScrematura[i][j] = giocatoreSelezionato;
        }
    }

    return variabili_scrematura;
}

//Funzione per il gioco della scrematura
Salvataggio giocoScrematura (Salvataggio salvataggio, Scrematura variabili_scrematura)
{
    //Dichiarazioni variabili locali
    int n_generato, n_scelto[variabili_scrematura.n_giocatori_per_gruppo+1],
        tentativi[variabili_scrematura.n_giocatori_per_gruppo+1], max=MAX, min=MIN, tentativi_minori, vincitore_gruppo, posizione_utente, giocatori_gruppo;
    bool controllo=false, indovinato=false;

    //Stampa della descrizione del gioco
    printf("\n---------------------------------------------------> Fase 0 <--------------------------------------------------\n"
           "Il gioco consiste nell'indovinare un numero generato casualmente tra 0 e 999 con i minori tentativi possibili.\n"
           "Ogni giocatore e' all'interno di un gruppo, il giocatore che in quel gruppo indovina piu velocemente il numero,\n"
           "                                         vince il gioco e passa il turno.\n"
           "-----------------------------------------------> BUONA FORTUNA <-----------------------------------------------\n");

    //Ciclo che si ripete per il n di gruppi formati, per ogni gruppo viene generato un numero randomico che i giocatori dovranno indovinare in meno tentativi possibili
    for (int i = 0; i < variabili_scrematura.n_gruppiScrematura; ++i)
    {
        n_generato = rand() % MAX; //Genera un numero random tra 0 e 999

        printf("\nSta giocando il gruppo n: %d\n", i+1);
        printf("---> PREMI INVIO PER CONTINUARE <---");
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        //Se il gruppo ha giocatori dispari esegue:
        if (variabili_scrematura.giocatori_restanti!=VUOTO)
        {
            variabili_scrematura.giocatori_restanti--; //Decrementa il numero di gruppi con giocatori dispari

            giocatori_gruppo = variabili_scrematura.n_giocatori_per_gruppo + 1;
        }
        //Altrimenti esegue:
        else
        {
            giocatori_gruppo = variabili_scrematura.n_giocatori_per_gruppo;
        }

        //Ciclo per fare indovinare il numero a un giocatore, si esegue per tutti i giocatori del gruppo
        for (int j = 0; j < giocatori_gruppo; ++j)
        {
            //Reset delle variabili
            controllo = false;
            indovinato = false;
            tentativi[j] = VUOTO;
            tentativi_minori = VUOTO;
            min = MIN;
            max = MAX;

            //Ciclo per controllare se il giocatore che sta giocando è controllato dall'utente
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (variabili_scrematura.gruppiScrematura[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    controllo = true;  //Porta la variabile di controllo a true per far capire al programma che sta giocando un giocatore utente
                    posizione_utente = salvataggio.giocatoriUtente_partecipanti[k]; //Salva la posizione dell array del giocatore utente trovato
                    printf("\nGiocatore: %s id:%d e' il tuo turno", salvataggio.arrayGiocatori[posizione_utente].nome, salvataggio.arrayGiocatori[posizione_utente].id);
                }
            }

            do //Ciclo per continuare a far inserire il numero in caso quello inserito non corrisponda a quello generato randomicamente
            {
                tentativi[j]++; //Conta i tentativi impiegati per indovinare

                //Se il giocatore è controllato dall'utente esegue:
                if (controllo == true)
                {
                    //Richiede l'inserimento di un numero
                    printf("\nIndovina il numero:");
                    scanf("%d", &n_scelto[j]);
                    while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio
                }
                    //Altrimenti (se il giocatore è controllato dalla cpu) esegue:
                else
                {
                    n_scelto[j] = min + rand() % (max-min+1); //Genera un numero casuale compreso tra min e max
                }

                //Se il numero è stato indovinato esegue:
                if (n_scelto[j] == n_generato)
                {
                    indovinato = true; //Se la variabile per uscire dal ciclo do-while a true

                    //Se il giocatore è controllato dall'utente esegue:
                    if (controllo == true)
                    {
                        printf("\nBRAVO INDOVINATO!\n"
                               "Giocatore: %s ci hai messo %d tentativi", salvataggio.arrayGiocatori[posizione_utente].nome, tentativi[j]);
                    }
                        //Altrimenti (se il giocatore è controllato dalla cpu) esegue:
                    else
                    {
                        printf("\nIl giocatore n.%d ci ha messo %d tentativi", variabili_scrematura.gruppiScrematura[i][j], tentativi[j]);
                    }
                }
                    //Se il numero scelto è minore del numero generato esegue:
                else if (n_scelto[j] < n_generato)
                {
                    //Se il giocatore è controllato dall'utente esegue:
                    if (controllo == true)
                    {
                        printf("SBAGLIATO!\n"
                               "Il numero e' piu grande\n");
                    }
                        //Altrimenti (se il giocatore è controllato dalla cpu) esegue:
                    else
                    {
                        min = n_scelto[j]+1; //Cambia il minimo con il numero appena inserito+1
                    }
                }
                    //Se il numero scelto è maggiore del numero generato esegue:
                else if (n_scelto[j] > n_generato)
                {
                    //Se il giocatore è controllato dall'utente esegue:
                    if (controllo == true)
                    {
                        printf("SBAGLIATO!\n"
                               "Il numero e' piu piccolo\n");
                    }
                        //Altrimenti (se il giocatore è controllato dalla cpu) esegue:
                    else
                    {
                        max = n_scelto[j]-1; //Cambia il massimo con il numero appena inserito-1
                    }
                }
            } while (indovinato == false);
        }

        //Ciclo per controllare il giocatore che ha impiegato meno turni a indovinare
        for (int j = 0; j < giocatori_gruppo; ++j)
        {
            //Se il giocatore è il primo controllato o se i tentativi di un giocatore sono minori di quelli presenti nella variabile di controllo esegue:
            if (j==0 || tentativi[j]<tentativi_minori)
            {
                tentativi_minori = tentativi[j]; //Aggiorna la variabile che conta i tentativi minori con quelli fatti dal giocatore di pos[j] nel gruppo
                vincitore_gruppo = j; //Inserisce il giocatore di pos[j] del gruppo come vincitore
            }
        }

        //Ciclo per controllare se nel gruppo c'è il giocatore Riccardo Scateni
        for (int j = 0; j < giocatori_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (variabili_scrematura.gruppiScrematura[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Se è presente vince automaticamente
                    vincitore_gruppo = Frontman_dello_SPR1D_GAME(vincitore_gruppo, salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].nome, j);
                }
            }
        }

        //Ciclo per eliminare i giocatori perdenti
        for (int j = 0; j < giocatori_gruppo; ++j)
        {
            //Se il giocatore controllato è il vincitore esegue:
            if (j == vincitore_gruppo)
            {
                salvataggio.giocatori_in_gioco[variabili_scrematura.gruppiScrematura[i][j]] = true;
                printf("\nIl giocatore vincitore del gruppo %d e' il n.%d\n", i+1, variabili_scrematura.gruppiScrematura[i][j]);
            }
                //Altrimenti esegue:
            else
            {
                salvataggio.giocatori_in_gioco[variabili_scrematura.gruppiScrematura[i][j]] = false;
            }
        }
    }

    return salvataggio;
}

//Funziona principale della partita
void partita (Salvataggio salvataggio)
{
    //Dichiarazioni variabili locali
    int scegliGioco, risp;
    bool controlloFrontman=false;
    Partita partita;

    //Resetto le variabili
    partita.giocatoriRimasti = VUOTO;
    partita.arrayGiocatoriRimasti = NULL;
    partita.gruppiGioco = NULL;

    //Aggiorno le variabili partita per controllare i giocatori in gioco
    partita = giocatori_in_gioco(salvataggio, partita);

    //Se ci sono più di 2 giocatori ancora in gioco esegue:
    if (partita.giocatoriRimasti > 2)
    {
        //Stampa della descrizione del gioco
        printf(  "\n--------------------------> Partita <--------------------------\n"
                 "        Inizia la partita vera e propria, sei pronto?         \n"
                 " Adesso verra' estratto un gioco a caso tra gli 8 disponibili \n"
                 "  Gli ultimi 2 giocatori rimanenti andranno alla fase finale  ");
    }

    //Ciclo per controllare se c'è il giocatore Riccardo Scateni
    for (int i = 0; i < salvataggio.M_controlloUtente; ++i)
    {
        //Se è presente sceglie il gioco da giocare
        if (strcmp(salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[i]].nome, "Riccardo Scateni")==false)
        {
            controlloFrontman = true;
        }
    }

    //Ciclo per continuare a scegliere il gioco da fare in caso i giocatori partecipanti siano più di 4
    while (partita.giocatoriRimasti > 2)
    {
        printf("\n------------------> Giocatori Rimanenti: %d <-------------------", partita.giocatoriRimasti);

        //Output della domanda
        printf("\nCosa vuoi fare?\n"
               "1) Continuare la partita\n"
               "3) Salvare i dati\n");
        //Richiesta input
        scanf("%d", &risp);
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        //Ciclo per continuare a far inserire la risposta in caso in cui non sia una delle due richieste
        while (risp!=RISP_CONTINUARE && risp!=RISP_SALVARE)
        {
            printf("\nATTENZIONE!\n"
                   "Inserire uno dei due numeri richiesti\n");
            scanf("%d", &risp);
            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio
        }

        //Se il giocatore vuole salvare esegue:
        if (risp==RISP_SALVARE)
        {
            salvataggio.partita_in_corso = true; //Setta la variabile della partita in corso a 1 perché il giocatore sta salvando una partita iniziata
            salva(salvataggio); //Salvo la partita

            //Output della domanda
            printf("\nCosa vuoi fare?\n"
                   "1) Continuare la partita\n"
                   "2) Uscire dal gioco\n");
            //Richiesta input
            scanf("%d", &risp);
            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

            //Ciclo per continuare a far inserire la risposta in caso in cui non sia una delle due richieste
            while (risp!=RISP_CONTINUARE && risp!=RISP_USCITA)
            {
                printf("\nATTENZIONE!\n"
                       "Inserire uno dei due numeri richiesti\n");
                scanf("%d", &risp);
                while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio
            }
        }
        //Se il giocatore vuole continuare la partita esegue:
        if (risp==RISP_CONTINUARE)
        {
            //Se ci sono più di 4 giocatori in gioco esegue:
            if (partita.giocatoriRimasti > 4)
            {
                //Se Scateni sta giocando esegue:
                if (controlloFrontman==true)
                {
                    printf("\nGrazie al trucco Frontman dello SPR1D GAME puoi scegliere a cosa giocare\n");
                    //Il giocatore Scateni sceglie a che gioco giocare
                    printf("Quale gioco scegli?\n"
                           "0) Pari o Dispari\n"
                           "1) Dadi\n"
                           "2) Morra Cinese\n"
                           "3) Murra\n"
                           "4) Tris\n"
                           "5) Biglie\n"
                           "6) Ponte di Vetro\n"
                           "7) L'impiccato\n");
                    scanf("%d", &scegliGioco);
                    while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio
                }
                //Altrimenti esegue:
                else
                {
                    scegliGioco = rand() % (N_GIOCHI_2_GIOCATORI + N_GIOCHI_4_GIOCATORI); //Sceglie randomicamente un gioco
                }

                //Switch per eseguire il gioco scelto
                switch (scegliGioco)
                {
                    case PARI_DISPARI:
                        printf("\n Il gioco scelto e' Pario o Dispari\n"
                               "         Pronto per giocare?\n"
                               "---> PREMI INVIO PER CONTINUARE <---");
                        while ((getchar()) != '\n');
                        salvataggio = PariDispari(salvataggio, partita);
                        break;

                    case DADI:
                        printf( "\n       Il gioco scelto e' Dadi\n"
                                "         Pronto per giocare?\n"
                                "---> PREMI INVIO PER CONTINUARE <---");
                        while ((getchar()) != '\n');
                        salvataggio = Dadi(salvataggio, partita);
                        break;

                    case MORRA_CINESE:
                        printf( "\n   Il gioco scelto e' Morra Cinese\n"
                                        "         Pronto per giocare?\n"
                                        "---> PREMI INVIO PER CONTINUARE <---");
                        while ((getchar()) != '\n');
                        salvataggio = MorraCinese(salvataggio, partita);
                        break;

                    case MURRA:
                        printf( "\n      Il gioco scelto e' Murra\n"
                                "         Pronto per giocare?\n"
                                "---> PREMI INVIO PER CONTINUARE <---");
                        while ((getchar()) != '\n');
                        salvataggio = Murra(salvataggio, partita);
                        break;

                    case TRIS:
                        printf( "\n       Il gioco scelto e' Tris\n"
                                "         Pronto per giocare?\n"
                                "---> PREMI INVIO PER CONTINUARE <---");
                        while ((getchar()) != '\n');
                        salvataggio = Tris(salvataggio, partita);
                        break;

                    case BIGLIE:
                        printf( "\n     Il gioco scelto e' Biglie\n"
                                "         Pronto per giocare?\n"
                                "---> PREMI INVIO PER CONTINUARE <---");
                        while ((getchar()) != '\n');
                        salvataggio = Biglie(salvataggio, partita);
                        break;

                    case PONTE_DI_VETRO:
                        printf( "\n  Il gioco scelto e' Ponte di Vetro\n"
                                "         Pronto per giocare?\n"
                                "---> PREMI INVIO PER CONTINUARE <---");
                        while ((getchar()) != '\n');
                        salvataggio = PonteVetro(salvataggio, partita);
                        break;

                    case IMPICCATO:
                        printf( "\n     Il gioco scelto e' Impiccato\n"
                                "         Pronto per giocare?\n"
                                "---> PREMI INVIO PER CONTINUARE <---");
                        while ((getchar()) != '\n');
                        salvataggio = Impiccato(salvataggio, partita);
                        break;

                    default:
                        printf("\nATTENZIONE!\n"
                               "Inserire uno dei numeri richiesti\n");
                        break;
                }
            }
            else
            {
                //Se Scateni sta giocando esegue:
                if (controlloFrontman==true)
                {
                    printf("\nGrazie al trucco Frontman dello SPR1D GAME puoi scegliere a cosa giocare\n");
                    //Il giocatore Scateni sceglie a che gioco giocare
                    printf("Quale gioco scegli?\n"
                           "0) Pari o Dispari\n"
                           "1) Dadi\n"
                           "2) Morra Cinese\n"
                           "3) Murra\n"
                           "4) Tris\n"
                           "5) Biglie\n");
                    scanf("%d", &scegliGioco);
                    while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio
                }
                    //Altrimenti esegue:
                else
                {
                    scegliGioco = rand() % N_GIOCHI_2_GIOCATORI; //Sceglie randomicamente un gioco
                }

                //Switch per eseguire il gioco scelto
                switch (scegliGioco)
                {
                    case PARI_DISPARI:
                        printf("\n Il gioco scelto e' Pario o Dispari\n"
                               "         Pronto per giocare?\n"
                               "---> PREMI INVIO PER CONTINUARE <---");
                        while ((getchar()) != '\n');
                        salvataggio = PariDispari(salvataggio, partita);
                        break;

                    case DADI:
                        printf( "\n       Il gioco scelto e' Dadi\n"
                                "         Pronto per giocare?\n"
                                "---> PREMI INVIO PER CONTINUARE <---");
                        while ((getchar()) != '\n');
                        salvataggio = Dadi(salvataggio, partita);
                        break;

                    case MORRA_CINESE:
                        printf( "\n   Il gioco scelto e' Morra Cinese\n"
                                "         Pronto per giocare?\n"
                                "---> PREMI INVIO PER CONTINUARE <---");
                        while ((getchar()) != '\n');
                        salvataggio = MorraCinese(salvataggio, partita);
                        break;

                    case MURRA:
                        printf( "\n      Il gioco scelto e' Murra\n"
                                "         Pronto per giocare?\n"
                                "---> PREMI INVIO PER CONTINUARE <---");
                        while ((getchar()) != '\n');
                        salvataggio = Murra(salvataggio, partita);
                        break;

                    case TRIS:
                        printf( "\n       Il gioco scelto e' Tris\n"
                                "         Pronto per giocare?\n"
                                "---> PREMI INVIO PER CONTINUARE <---");
                        while ((getchar()) != '\n');
                        salvataggio = Tris(salvataggio, partita);
                        break;

                    case BIGLIE:
                        printf( "\n     Il gioco scelto e' Biglie\n"
                                "         Pronto per giocare?\n"
                                "---> PREMI INVIO PER CONTINUARE <---");
                        while ((getchar()) != '\n');
                        salvataggio = Biglie(salvataggio, partita);
                        break;

                    default:
                        printf("\nATTENZIONE!\n"
                               "Inserire uno dei numeri richiesti\n");
                        break;
                }
            }

            partita.giocatoriRimasti = VUOTO; //Resetta la variabile che conta i giocatori rimasti in gioco

            //Aggiorno le variabili partita per controllare i giocatori in gioco
            partita = giocatori_in_gioco(salvataggio, partita);
        }
        //Se il giocatore vuole uscire esegue:
        else if (risp==RISP_USCITA)
        {
            free(partita.arrayGiocatoriRimasti); //Libera la memoria allocata dinamicamente
            return;
        }

    }

    //Richiamo la funzione per la fase finale della partita
    faseFinale(salvataggio, partita);

    free(partita.arrayGiocatoriRimasti); //Libera la memoria allocata dinamicamente
}

//Funzione per aggiornare i giocatori in gioco
Partita giocatori_in_gioco (Salvataggio salvataggio, Partita partita)
{
    //Ciclo per contare i giocatori rimasti in gioco
    for (int i = 0; i < salvataggio.N_partecipanti; ++i)
    {
        //Se il giocatore i non è ancora stato eliminato esegue:
        if (salvataggio.giocatori_in_gioco[i]==true)
        {
            (partita.giocatoriRimasti)++; //Aumenta il conteggio dei giocatori rimasti di 1

            //Alloca dinamicamente la memoria per l'array di giocatori non ancora eliminati per permettere d'inserirne un altro
            partita.arrayGiocatoriRimasti = (int*) realloc(partita.arrayGiocatoriRimasti, (sizeof(int)*partita.giocatoriRimasti));
            //Controllo se la memoria per il puntatore è stata allocata correttamente
            if( partita.arrayGiocatoriRimasti == NULL )
                exit(-1);

            //Inserisco nella posizione dell'array appena allocata l'id del giocatore ancora in gioco
            partita.arrayGiocatoriRimasti[(partita.giocatoriRimasti)-1] = i;
        }
    }

    return partita;
}

//Funzione della fase finale
void faseFinale (Salvataggio salvataggio, Partita partita)
{
    //Dichiarazione variabili locali
    int risp;
    bool ripeti=false;

    //Stampa della descrizione dela fase finale
    printf("\n------------------------> Fase Finale <------------------------\n"
           "     Sono rimasti 2 giocatori, pronti per la fase finale?\n"
           "                          n.%d VS n.%d\n"
           "-----------------------> BUONA FORTUNA <-----------------------\n", partita.arrayGiocatoriRimasti[GIOCATORE1], partita.arrayGiocatoriRimasti[GIOCATORE2]);

    //Output della domanda
    printf("\nCosa vuoi fare?\n"
           "1) Continuare la partita\n"
           "3) Salvare i dati\n");
    //Richiesta input
    scanf("%d", &risp);
    while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

    //Ciclo per continuare a far inserire la risposta in caso in cui non sia una delle due richieste
    while (risp!=RISP_CONTINUARE && risp!=RISP_SALVARE)
    {
        printf("\nATTENZIONE!\n"
               "Inserire uno dei due numeri richiesti\n");
        scanf("%d", &risp);
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio
    }

    //Se il giocatore vuole salvare esegue:
    if (risp==RISP_SALVARE)
    {
        salvataggio.partita_in_corso=true; //Setta la variabile della partita in corso a 1 perché il giocatore sta salvando una partita iniziata
        salva(salvataggio); //Salva la partita

        //Output della domanda
        printf("\nCosa vuoi fare?\n"
               "1) Continuare la partita\n"
               "2) Uscire dal gioco\n");
        //Richiesta input
        scanf("%d", &risp);
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        //Ciclo per continuare a far inserire la risposta in caso in cui non sia una delle due richieste
        while (risp!=RISP_CONTINUARE && risp!=RISP_USCITA)
        {
            printf("\nATTENZIONE!\n"
                   "Inserire uno dei due numeri richiesti\n");
            scanf("%d", &risp);
            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio
        }
    }
    //Se il giocatore vuole continuare la partita esegue:
    if (risp==RISP_CONTINUARE)
    {
        //Ciclo per controllare se dei giocatori rimasti qualcuno è controllato dall'utente
        for (int i = 0; i < GRANDEZZA_GRUPPI2; ++i)
        {
            for (int j = 0; j < salvataggio.M_controlloUtente; ++j)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.arrayGiocatoriRimasti[i] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[j]].id)
                {
                    //Incrementa il numero di finali giocate del giocatore selezionato
                    salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[j]].n_finali_giocate++;
                }
            }
        }

        do //Ciclo per ripetere il gioco in caso finisca in parità
        {
            ripeti = BlackJack(salvataggio, partita);
        } while (ripeti==true);
    }
    //Se il giocatore vuole uscire esegue:
    else if (risp==RISP_USCITA)
    {
        return;
    }
}