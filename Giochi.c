#include "Giochi.h"

//Funzione per creare gruppi composti da 2 giocatori
Partita creaGruppi_Partita (Partita partita, int N_partecipanti)
{
    //Dichiarazione variabili locali
    int giocatoreSelezionato;
    bool controllo=false, controllo_sottrazione=false, controllo_eliminazione=true;

    //Conta i numeri di gruppi da creare
    partita.n_gruppi = partita.giocatoriRimasti/partita.giocatori_per_gruppo;

    //Alloco dinamicamente le righe della matrice per poter contenere tutti i gruppi creati
    partita.gruppiGioco = (int**) malloc(sizeof(int*)*partita.n_gruppi);
    //Controllo se la memoria per il puntatore è stata allocata correttamente
    if( partita.gruppiGioco == NULL )
        exit(-1);

    for (int i = 0; i < partita.n_gruppi; ++i)
    {
        //Alloco dinamicamente le colonne della matrice per poter contenere tutti i giocatori appartenenti al gruppo
        partita.gruppiGioco[i] = (int*) malloc(sizeof(int)*partita.giocatori_per_gruppo);
        //Controllo se la memoria per il puntatore è stata allocata correttamente
        if( partita.gruppiGioco[i] == NULL )
            exit(-1);

        //Ciclo per riempire con un numero le posizioni allocate per essere sicuro che in quelle posizioni non ci sia un numero che potrebbe dare problemi al controllo successivo
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j) {
            //Inserisce il numero N (che non è un numero degli id e quindi non è un numero generato randomicamente)
            partita.gruppiGioco[i][j]=N_partecipanti;
        }

        //Ciclo per generare randomicamente n_giocatori_per_gruppo da inserire all'interno del gruppo d'indice i
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            giocatoreSelezionato = rand()%N_partecipanti; //Genera un numero random tra 0 e N-1

            //Resetta le variabili di controllo
            controllo_sottrazione = false;
            controllo_eliminazione = true;
            controllo = true;

            do //Ciclo per continuare a far cambiare il numero generato in caso non si riesca a trovare un numero mancante nei gruppi e non eliminato
            {
                //Esegue il ciclo un numero di volte pari al numero di gruppi già allocati
                for (int k = 0; k <= i; ++k)
                {
                    //Esegue il ciclo un numero di volte pari al numero di giocatori presenti nel gruppo appena allocato
                    for (int l = 0; l < partita.giocatori_per_gruppo; ++l)
                    {
                        //Ciclo per controllare se il giocatore selezionato o già stato eliminato
                        for (int m = 0; m < partita.giocatoriRimasti; ++m)
                        {
                            //Se il giocatore non è stato eliminato esegue:
                            if (partita.arrayGiocatoriRimasti[m]==giocatoreSelezionato)
                            {
                                controllo_eliminazione=false;
                                m = partita.giocatoriRimasti; //porta k al valore dei giocatori rimasti per uscire dal ciclo
                            }
                            //Altrimenti esegue:
                            else
                            {
                                controllo_eliminazione = true;
                            }
                        }
                        //Se il numero generato casualmente è già presente all'interno dell array dei gruppi o se il giocatore generato è stato eliminato esegue:
                        if (giocatoreSelezionato==partita.gruppiGioco[k][l] || controllo_eliminazione==true)
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
            partita.gruppiGioco[i][j] = giocatoreSelezionato;
        }
    }

    return partita;
}

//Trucco Frontman dello SPR1D GAME
int Frontman_dello_SPR1D_GAME (int vincitore, char giocatore_nome[], int giocatore_id)
{
    //Se il giocatore passato si chiama Riccardo Scateni esegue:
    if (strcmp(giocatore_nome, "Riccardo Scateni")==false)
    {
        printf("\nGrazie al trucco del Frontman dello SPR1D GAME\n"
               "             --> HAI VINTO <--\n");

        //Il vincitore è lui
        vincitore = giocatore_id;
    }

    return vincitore;
}

//Funzione gioco Pari o Dispari
Salvataggio PariDispari (Salvataggio salvataggio, Partita partita)
{
    //Dichiarazione variabili locali
    int giocatore_pari, giocatore_dispari, posizione_utente, pari_dispari, vincitore, dita_puntate[GRANDEZZA_GRUPPI2], somma_risposte=0;
    bool controllo=false, controllo2=false;

    partita.giocatori_per_gruppo = GRANDEZZA_GRUPPI2;

    //Crea i gruppi di giocatori
    partita = creaGruppi_Partita(partita, salvataggio.N_partecipanti);

    //Stampa della descrizione del gioco
    printf("\n----------------------------> Pari o Dispari <----------------------------\n"
           " Per questo gioco dovrai scegliere se essere un giocatore pari o dispari\n"
           "        Ogni giocatore decidera' quante dita della mano mostrare\n"
           "                    La somma decretera' il vincitore\n"
           "----------------------------> BUONA FORTUNA <-----------------------------\n");

    //Esegue il gioco per ogni gruppo creato
    for (int i = 0; i < partita.n_gruppi; ++i)
    {
        printf("\nSta giocando il gruppo n: %d\n", i+1);
        printf("---> PREMI INVIO PER CONTINUARE <---");
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        //Resetta le variabili
        controllo = false;
        somma_risposte = 0;

        //Ciclo per controllare se esiste un giocatore controllato dall'utente
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    controllo = true;  //Porta la variabile di controllo a true per far capire al programma che sta giocando un giocatore utente
                    posizione_utente = salvataggio.giocatoriUtente_partecipanti[k]; //Salva la posizione in cui si trova

                    //Incrementa il numero di mini-giochi giocati del giocatore selezionato
                    salvataggio.arrayGiocatori[posizione_utente].n_tot_minigiochi_giocati++;
                }
            }
        }

        //Se c'è almeno un giocatore utente esegue:
        if (controllo==true)
        {
            //Output della domanda
            printf("\n%s vuoi essere pari o dispari?\n"
                   "1) Dispari\n"
                   "2) Pari\n", salvataggio.arrayGiocatori[posizione_utente].nome);
            //Richiesta input
            scanf("%d", &pari_dispari);
            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

            //Ciclo per continuare a far inserire la risposta in caso in cui non sia una delle due richieste
            while (pari_dispari!=DISPARI && pari_dispari!=PARI)
            {
                printf("\nATTENZIONE!\n"
                       "Inserire uno dei due numeri richiesti\n");
                scanf("%d", &pari_dispari);
                while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio
            }

            //Se l'utente ha scelto di essere dispari esegue:
            if (pari_dispari==DISPARI)
            {
                //Ciclo per controllare quale utente ha scelto dispari e settare l'altro pari
                for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
                {
                    //Se il giocatore controllato è quello che ha scelto esegue:
                    if (partita.gruppiGioco[i][j]==salvataggio.arrayGiocatori[posizione_utente].id)
                    {
                        giocatore_dispari = partita.gruppiGioco[i][j];
                    }
                    //Altrimenti esegue:
                    else
                    {
                        giocatore_pari = partita.gruppiGioco[i][j];
                    }
                }
            }
            //Se l'utente ha scelto di essere pari esegue:
            else
            {
                //Ciclo per controllare quale utente ha scelto pari e settare l'altro dispari
                for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
                {
                    //Se il giocatore controllato è quello che ha scelto esegue:
                    if (partita.gruppiGioco[i][j]==salvataggio.arrayGiocatori[posizione_utente].id)
                    {
                        giocatore_pari = partita.gruppiGioco[i][j];
                    }
                    //Altrimenti esegue:
                    else
                    {
                        giocatore_dispari = partita.gruppiGioco[i][j];
                    }
                }
            }

            //Ciclo per controllare se il giocatore che sta giocando è controllato dall'utente
            for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
            {
                controllo2=false; //Resetta la variabile di controllo

                //Ciclo per controllare se il giocatore che sta giocando è controllato dall'utente
                for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
                {
                    //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                    if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                    {
                        controllo2 = true;
                    }
                }

                //Se il giocatore è controllato dall'utente esegue:
                if (controllo2==true)
                {
                    //Output della domanda
                    printf("\nQuante dita di una mano vuoi mostrare?\n");
                    //Richiesta input
                    scanf("%d", &dita_puntate[j]);
                    while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

                    //Ciclo per continuare a far inserire la risposta in caso in cui non sia una delle due richieste
                    while ((dita_puntate[j] < 0) || (dita_puntate[j] > DITA_MANO))
                    {
                        printf("\nDove hai visto una mano con %d dita?\n"
                               "Inserisci un numero da 0 a 5\n", dita_puntate[j]);
                        scanf("%d", &dita_puntate[j]);
                        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio
                    }
                }
                //Se è controllato dalla cpu esegue:
                else
                {
                    dita_puntate[j] = rand() % (DITA_MANO + 1); //Genera randomicamente il numero di dita da contare
                    printf("Il giocatore cpu %d ha mostrato %d dita\n", partita.gruppiGioco[i][j], dita_puntate[j]);
                }

                //Somma le dita puntate da entrambi i giocatori del gruppo
                somma_risposte += dita_puntate[j];
            }

            //Se la somma è dispari esegue:
            if ((somma_risposte % 2)!=0)
            {
                printf("La somma delle dita mostrate e' un numero dispari\n");
                vincitore = giocatore_dispari; //Vince il giocatore dispari
            }
            //Se la somma è pari esegue:
            else
            {
                printf("La somma delle dita mostrate e' un numero pari\n");
                vincitore = giocatore_pari; //Vince il giocatore pari
            }
        }
        //Altrimenti esegue
        else
        {
            //Genera randomicamente il vincitore
            vincitore = partita.gruppiGioco[i][rand()%partita.giocatori_per_gruppo];
        }

        //Ciclo per controllare se nel gruppo c'è il giocatore Riccardo Scateni
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Se è presente vince automaticamente
                    vincitore = Frontman_dello_SPR1D_GAME(vincitore, salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].nome, partita.gruppiGioco[i][j]);
                }
            }
        }

        //Ciclo per controllare quale giocatore del gruppo ha vinto
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            //Se il giocatore controllato è il vincitore esegue:
            if (vincitore==partita.gruppiGioco[i][j])
            {
                //Ciclo che controlla se il giocatore vincitore è controllato dall'utente
                for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
                {
                    //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                    if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                    {
                        //Incrementa il numero di mini-giochi vinti del giocatore selezionato
                        salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_tot_minigiochi_vinti++;
                    }
                }

                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = true;
                printf("\nIl giocatore vincitore del gruppo %d e' il n.%d\n", i+1, partita.gruppiGioco[i][j]);
            }
            //Altrimenti esegue:
            else
            {
                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = false;
            }
        }
    }

    free(partita.gruppiGioco); //Libero la memoria allocata dinamicamente

    return salvataggio;
}

//Funzione gioco Dadi
Salvataggio Dadi (Salvataggio salvataggio, Partita partita)
{
    //Dichiarazione variabili locali
    int dadi[partita.giocatori_per_gruppo][QUANTITA_DADI], n_tiro=0, mossa, somma_tiro_corrente=0, somma_tiro_precedente=0, vittoria;
    bool controllo=false;

    partita.giocatori_per_gruppo = GRANDEZZA_GRUPPI2;

    //Stampa della descrizione del gioco
    printf("\n------------------------> Dadi <-------------------------\n"
                   " Per questo gioco ogni giocatore dovra' lanciare 2 dadi,\n"
                   "     Il primo giocatore che fa un tiro la cui somma\n"
                   "          e' minore del tiro precedente, perde\n"
                   "--------------------> BUONA FORTUNA <--------------------\n");

    //Crea i gruppi di giocatori
    partita = creaGruppi_Partita(partita, salvataggio.N_partecipanti);

    //Esegue il gioco per ogni gruppo creato
    for (int i = 0; i < partita.n_gruppi; ++i)
    {
        printf("\nSta giocando il gruppo n: %d\n", i+1);
        printf("---> PREMI INVIO PER CONTINUARE <---");
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        //Ciclo per controllare se esiste un giocatore controllato dall'utente
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Incrementa il numero di mini-giochi giocati del giocatore selezionato
                    salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_tot_minigiochi_giocati++;
                }
            }
        }

        //Resetta le variabili
        somma_tiro_corrente = 0;
        somma_tiro_precedente = 0;
        n_tiro = 0;

        mossa = rand()%partita.giocatori_per_gruppo; //Sceglie randomicamente quale giocatore deve fare la prima mossa

        printf("Il primo tiro e' del giocatore %d\n", partita.gruppiGioco[i][mossa]);

        //Il giocatore scelto per la prima mossa tira il primo dado
        dadi[mossa][n_tiro] = 1 + rand() % FACCE_DADI;
        printf("Dal primo dado e' uscito %d\n", dadi[mossa][n_tiro]);
        somma_tiro_precedente += dadi[mossa][n_tiro]; //Aggiunge il numero uscito alla somma
        n_tiro++;

        //Il giocatore scelto per la prima mossa tira il secondo dado
        dadi[mossa][n_tiro] = 1 + rand() % FACCE_DADI;
        printf("Dal secondo dado e' uscito %d\n", dadi[mossa][n_tiro]);
        somma_tiro_precedente += dadi[mossa][n_tiro]; //Aggiunge il numero uscito alla somma

        printf("La somma dei numeri usciti e':%d\n", somma_tiro_precedente);

        do //Ciclo per continuare a far continuare a lanciare i dadi finché un giocatore non perde
        {
            somma_tiro_corrente = 0; //Resetto la variabile della somma del tiro appena fatto

            //Se il turno precedente ha giocato il giocatore 1 esegue:
            if (mossa==GIOCATORE1)
            {
                n_tiro = 0; //Resetto la variabile del tiro

                //Il giocatore2 tira il primo dado
                printf("\nTira il giocatore %d\n", partita.gruppiGioco[i][GIOCATORE2]);
                dadi[GIOCATORE2][n_tiro] = 1 + rand() % FACCE_DADI;
                printf("Dal primo dado e' uscito %d\n", dadi[GIOCATORE2][n_tiro]);
                somma_tiro_corrente += dadi[GIOCATORE2][n_tiro]; //Aggiunge il numero uscito alla somma
                n_tiro++;

                //Il giocatore2 tira il secondo dado
                dadi[GIOCATORE2][n_tiro] = 1 + rand() % FACCE_DADI;
                printf("Dal secondo dado e' uscito %d\n", dadi[GIOCATORE2][n_tiro]);
                somma_tiro_corrente += dadi[GIOCATORE2][n_tiro]; //Aggiunge il numero uscito alla somma

                printf("La somma dei numeri usciti e':%d\n", somma_tiro_corrente);
                mossa = GIOCATORE2; //Inserisce la posizione del giocatore 2 alla variabile mossa per capire quale giocatore ha appena effettuato il turno

                //Se la somma dei numeri usciti al giocatore che ha effettuato il turno è minore di quella avvenuta al turno precedente esegue:
                if (somma_tiro_precedente > somma_tiro_corrente)
                {
                    printf("Ha vinto giocatore id:%d\n", partita.gruppiGioco[i][GIOCATORE1]);
                    vittoria = partita.gruppiGioco[i][GIOCATORE1]; //Vince il giocatore 1
                    controllo = true; //Setta la variabile di controllo a true per poter uscire dal ciclo
                }
                //Se la somma è superiore esegue:
                else
                {
                    somma_tiro_precedente = somma_tiro_corrente; //La somma dei tiri correnti diventa la somma dei tiri precedenti
                    controllo = false;
                }
            }
            //Se il turno precedente ha giocato il giocatore 2 esegue:
            else
            {
                n_tiro = 0; //Resetto la variabile del tiro

                //Il giocatore1 tira il primo dado
                printf("\nTira il giocatore %d\n", partita.gruppiGioco[i][GIOCATORE1]);
                dadi[GIOCATORE1][n_tiro] = 1 + rand() % FACCE_DADI;
                printf("Dal primo dado e' uscito %d\n", dadi[GIOCATORE1][n_tiro]);
                somma_tiro_corrente += dadi[GIOCATORE1][n_tiro]; //Aggiunge il numero uscito alla somma
                n_tiro++;

                //Il giocatore1 tira il secondo dado
                dadi[GIOCATORE1][n_tiro] = 1 + rand() % FACCE_DADI;
                printf("Dal secondo dado e' uscito %d\n", dadi[GIOCATORE1][n_tiro]);
                somma_tiro_corrente += dadi[GIOCATORE1][n_tiro]; //Aggiunge il numero uscito alla somma

                printf("La somma dei numeri usciti e':%d\n", somma_tiro_corrente);
                mossa=GIOCATORE1; //Inserisce la posizione del giocatore 1 alla variabile mossa per capire quale giocatore ha appena effettuato il turno

                //Se la somma dei numeri usciti al giocatore che ha effettuato il turno è minore di quella avvenuta al turno precedente esegue:
                if (somma_tiro_precedente > somma_tiro_corrente)
                {
                    printf("Ha vinto giocatore id:%d\n", partita.gruppiGioco[i][GIOCATORE2]);
                    vittoria = partita.gruppiGioco[i][GIOCATORE2]; //Vince il giocatore 2
                    controllo = true; //Setta la variabile di controllo a true per poter uscire dal ciclo
                }
                //Se la somma è superiore esegue:
                else
                {
                    somma_tiro_precedente = somma_tiro_corrente; //La somma dei tiri correnti diventa la somma dei tiri precedenti
                    controllo = false;
                }
            }
        } while (controllo==false);

        //Ciclo per controllare se nel gruppo c'è il giocatore Riccardo Scateni
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Se è presente vince automaticamente
                    vittoria = Frontman_dello_SPR1D_GAME(vittoria, salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].nome, partita.gruppiGioco[i][j]);
                }
            }
        }

        //Ciclo per controllare quale giocatore del gruppo ha vinto
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            //Se il giocatore controllato è il vincitore esegue:
            if (vittoria==partita.gruppiGioco[i][j])
            {
                //Ciclo che controlla se il giocatore vincitore è controllato dall'utente
                for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
                {
                    //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                    if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                    {
                        //Incrementa il numero di mini-giochi vinti del giocatore selezionato
                        salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_tot_minigiochi_vinti++;
                    }
                }

                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = true;
                printf("\nIl giocatore vincitore del gruppo %d e' il n.%d\n", i+1, partita.gruppiGioco[i][j]);
            }
                //Altrimenti esegue:
            else
            {
                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = false;
            }
        }
    }

    free(partita.gruppiGioco); //Libero la memoria allocata dinamicamente

    return salvataggio;
}

//Funzione gioco Morra Cinese
Salvataggio MorraCinese (Salvataggio salvataggio, Partita partita)
{
    //Dichiarazione variabili locali
    int vincitore, posizione_utente, simboli_scelti[GRANDEZZA_GRUPPI2];
    char simboli[N_SIMBOLI][DIM_SIMBOLI]={"Sasso","Carta","Forbici"};
    bool controllo=false, utente=false, controlloSimbolo=false, fine_partita=false;

    partita.giocatori_per_gruppo = GRANDEZZA_GRUPPI2;

    //Stampa della descrizione del gioco
    printf("\n-------------------------------> Morra Cinese <-------------------------------\n"
                   " Per questo gioco ogni giocatore dovra' scegliere uno tra i seguenti simboli:\n"
                   "                             Sasso, Carta, Forbici\n"
                   "          I simboli verranno comparati e il vincitore verra' scelto\n"
                   "                         in base alle seguenti regole:\n"
                   "                        - Sasso VS Carta -> Vince Carta\n"
                   "                        - Carta VS Forbici -> Vince Forbici\n"
                   "                        - Sasso VS Forbici -> Vince Sasso\n"
                   "------------------------------> BUONA FORTUNA <-------------------------------\n");

    //Crea i gruppi di giocatori
    partita = creaGruppi_Partita(partita, salvataggio.N_partecipanti);

    //Esegue il gioco per ogni gruppo creato
    for (int i = 0; i < partita.n_gruppi; ++i)
    {
        printf("\nSta giocando il gruppo n: %d\n", i+1);
        printf("---> PREMI INVIO PER CONTINUARE <---");
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        controllo = false; //Resetto la variabile per controllare se nel gruppo un giocatore è controllato dall'utente
        fine_partita = false; //Resetto la variabile per capire se la partita è finita

        //Ciclo per controllare se esiste un giocatore controllato dall'utente
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Incrementa il numero di mini-giochi giocati del giocatore selezionato
                    salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_tot_minigiochi_giocati++;
                    controllo = true;
                }
            }
        }

        //Se nel gruppo c'è un giocatore controllato dall'utente esegue:
        if (controllo==true)
        {
            do //Ciclo per continuare a far continuare la partita finché un giocatore non vince
            {
                for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
                {
                    utente = false; //Resetta per controllare se il giocatore che esegue il turno è controllato dall'utente

                    //Ciclo per controllare se il giocatore che sta eseguendo il turno è controllato dall'utente
                    for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
                    {
                        //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                        if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                        {
                            utente = true;
                            posizione_utente = salvataggio.giocatoriUtente_partecipanti[k]; //Salva la posizione dell'utente nell'array di giocatori
                        }
                    }

                    //Se il giocatore che sta eseguendo il turno è controllato dall'utente esegue:
                    if (utente==true)
                    {
                        do //Ciclo per continuare a far continuare a inserire il numero del simbolo, in caso quello scelto non esista
                        {
                            controlloSimbolo = false; //Resetta la variabile per controllare se è stato inserito un simbolo esistente

                            printf("\n%s cosa vuoi buttare?\n"
                                   "0) Sasso\n"
                                   "1) Carta\n"
                                   "2) Forbici\n", salvataggio.arrayGiocatori[posizione_utente].nome);
                            printf("Inserisci numero:");
                            scanf("%d", &simboli_scelti[j]);
                            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

                            //Se il numero scelto non rispetta la condizioni esegue:
                            if ((simboli_scelti[j] != SASSO) && (simboli_scelti[j] != CARTA) && (simboli_scelti[j] != FORBICI))
                            {
                                printf("ATTENZIONE devi inserire uno dei tre simboli\n");
                                controlloSimbolo = true;
                            }
                        } while (controlloSimbolo==true);
                    }
                    //Altrimenti esegue:
                    else
                    {
                        simboli_scelti[j] = rand() % N_SIMBOLI; //Genera randomicamente un simbolo
                    }
                }

                //Stampa i simboli buttati da entrambi i giocatori
                printf("\nIl giocatore n.%d ha buttato %s\n", partita.gruppiGioco[i][GIOCATORE1], simboli[simboli_scelti[GIOCATORE1]]);
                printf("Il giocatore n.%d ha buttato %s\n", partita.gruppiGioco[i][GIOCATORE2], simboli[simboli_scelti[GIOCATORE2]]);

                //Se ha vinto il giocatore 1 esegue:
                if ((simboli_scelti[GIOCATORE1]==SASSO && simboli_scelti[GIOCATORE2]==FORBICI) || (simboli_scelti[GIOCATORE1]==CARTA && simboli_scelti[GIOCATORE2]==SASSO) || (simboli_scelti[GIOCATORE1]==FORBICI && simboli_scelti[GIOCATORE2]==CARTA))
                {
                    printf("Ha vinto il giocatore n.%d\n", partita.gruppiGioco[i][GIOCATORE1]);
                    vincitore = partita.gruppiGioco[i][GIOCATORE1]; //Setta il giocatore 1 come vincitore
                    fine_partita = true;
                }
                //Se ha vinto il giocatore 2 esegue:
                else if ((simboli_scelti[GIOCATORE2]==SASSO && simboli_scelti[GIOCATORE1]==FORBICI) || (simboli_scelti[GIOCATORE2]==CARTA && simboli_scelti[GIOCATORE1]==SASSO) || (simboli_scelti[GIOCATORE2]==FORBICI && simboli_scelti[GIOCATORE1]==CARTA))
                {
                    printf("Ha vinto il giocatore n.%d\n", partita.gruppiGioco[i][GIOCATORE2]);
                    vincitore = partita.gruppiGioco[i][GIOCATORE2]; //Setta il giocatore 2 come vincitore
                    fine_partita = true;
                }
                //Se non ha vinto nessuno dei due esegue:
                else
                {
                    printf("La partita e' finita in pareggio\n");
                    fine_partita = false; //Non fa finire la partita e la fa ripetere da capo
                }
            } while (fine_partita == false);
        }
        //Altrimenti esegue:
        else
        {
            //Genera randomicamente il vincitore
            vincitore = partita.gruppiGioco[i][rand()%partita.giocatori_per_gruppo];
        }

        //Ciclo per controllare se nel gruppo c'è il giocatore Riccardo Scateni
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Se è presente vince automaticamente
                    vincitore = Frontman_dello_SPR1D_GAME(vincitore, salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].nome, partita.gruppiGioco[i][j]);
                }
            }
        }

        //Ciclo per controllare quale giocatore del gruppo ha vinto
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            //Se il giocatore controllato è il vincitore esegue:
            if (vincitore==partita.gruppiGioco[i][j])
            {
                //Ciclo che controlla se il giocatore vincitore è controllato dall'utente
                for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
                {
                    //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                    if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                    {
                        //Incrementa il numero di mini-giochi vinti del giocatore selezionato
                        salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_tot_minigiochi_vinti++;
                    }
                }

                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = true;
                printf("\nIl giocatore vincitore del gruppo %d e' il n.%d\n", i+1, partita.gruppiGioco[i][j]);
            }
                //Altrimenti esegue:
            else
            {
                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = false;
            }
        }
    }

    return salvataggio;
}

//Funzione gioco Tris
Salvataggio Tris (Salvataggio salvataggio, Partita partita)
{
    //Dichiarazione variabili locali
    int tabella[RIGHE][COLONNE]={VUOTO}, pedina_turno, pedina_avversario;
    int vincitore, riga, colonna, pareggio;
    bool controllo=false, utente=false, fine_partita=false, ripeti=false;

    partita.giocatori_per_gruppo = GRANDEZZA_GRUPPI2;

    //Stampa della descrizione del gioco
    printf("\n---------------------------------------> Tris <---------------------------------------\n"
           " Per questo gioco ogni giocatore dovra' scegliere dove posizionare la propria pedina.\n"
           "          Vince chi ottiene per primo una riga, una colonna o una diagonale\n"
           "                      interamente occupata dalla propria pedina\n"
           "----------------------------------> BUONA FORTUNA <-----------------------------------\n");

    //Crea i gruppi di giocatori
    partita = creaGruppi_Partita(partita, salvataggio.N_partecipanti);

    //Esegue il gioco per ogni gruppo creato
    for (int i = 0; i < partita.n_gruppi; ++i)
    {
        printf("\nSta giocando il gruppo n: %d\n", i+1);
        printf("---> PREMI INVIO PER CONTINUARE <---");
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        controllo = false; //Resetto la variabile per controllare se nel gruppo un giocatore è controllato dall'utente
        fine_partita = false; //Resetto la variabile per capire se la partita è finita

        //Ciclo per controllare se esiste un giocatore controllato dall'utente
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Incrementa il numero di mini-giochi giocati del giocatore selezionato
                    salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_tot_minigiochi_giocati++;
                    controllo = true;
                }
            }
        }

        //Se nel gruppo c'è un giocatore controllato dall'utente esegue:
        if (controllo==true)
        {
            //Stampa la tabella di gioco
            printf("\n");
            for (int k = 0; k < RIGHE; ++k)
            {
                if (k==0)
                {
                    for (int l = 0; l < COLONNE; ++l)
                    {
                        switch (l)
                        {
                            case VUOTO:
                                printf("  1 ");
                                break;

                            case 1:
                                printf("2 ");
                                break;

                            case 2:
                                printf("3\n");
                                break;
                        }
                    }
                }

                for (int l = 0; l < COLONNE; ++l)
                {
                    if (l==0)
                    {
                        switch (k)
                        {
                            case VUOTO:
                                printf("1 ");
                                break;

                            case 1:
                                printf("2 ");
                                break;

                            case 2:
                                printf("3 ");
                                break;
                        }
                    }

                    switch (tabella[k][l])
                    {
                        case VUOTO:
                            printf("* ");
                            break;

                        case 1:
                            printf("x ");
                            break;

                        case 2:
                            printf("o ");
                            break;
                    }
                }
                printf("\n");
            }

            do //Ciclo per continuare a far continuare la partita finché un giocatore non vince
            {
                for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
                {
                    utente = false; //Resetta per controllare se il giocatore che esegue il turno è controllato dall'utente
                    pareggio = VUOTO; //Resetta la variabile per controllare il pareggio

                    //Ciclo per controllare se il giocatore che sta eseguendo il turno è controllato dall'utente
                    for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
                    {
                        //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                        if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                        {
                            utente = true;
                        }
                    }

                    //Switch per settare i valori delle pedine del turno
                    switch (j)
                    {
                        //Se sta giocando il giocatore con la pedina (x) esegue:
                        case PEDINA_X-1:
                            pedina_turno = PEDINA_X; //Setta x come pedina da usare
                            pedina_avversario = PEDINA_O; //Setta o come pedina dell'avversario
                            break;

                        //Se sta giocando il giocatore con la pedina (o) esegue:
                        case PEDINA_O-1:
                            pedina_turno = PEDINA_O; //Setta o come pedina da usare
                            pedina_avversario = PEDINA_X; //Setta x come pedina dell'avversario
                            break;
                    }

                    //Se il giocatore che sta eseguendo il turno è controllato dall'utente esegue:
                    if (utente==true)
                    {
                        do //Ciclo per continuare a far continuare a inserire la posizione in cui posizionare la pedina in caso quella scelta non esista o sia già occupata
                        {
                            ripeti = false; //Resetta la variabile di controllo

                            printf("\nIn quale posizione vuoi mettere la pedina?\n");
                            printf("Inserisci riga:");
                            scanf("%d", &riga);
                            riga--; //Decrementa la riga per ottenere la posizione della matrice
                            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

                            printf("Inserisci colonna:");
                            scanf("%d", &colonna);
                            colonna--; //Decrementa la colonna per ottenere la posizione della matrice
                            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

                            //Se la riga o la colonna inserite non esistono esegue:
                            if ((riga < 0 || riga > 2) || (colonna < 0 || colonna > 2))
                            {
                                printf("ATTENZIONE, inserisci una posizione esistente\n");
                                ripeti = true;
                            }
                            //Se la posizione scelta risulta occupata esegue:
                            else if (tabella[riga][colonna]!=VUOTO)
                            {
                                printf("ATTENZIONE, la posizione scelta e' piena\n");
                                ripeti = true;
                            }
                        } while (ripeti==true);

                        tabella[riga][colonna] = pedina_turno; //Inserisce nella posizione scelta la pedina del giocatore
                    }
                    //Altrimenti esegue:
                    else
                    {
                        //Richiamo la funzione dell'intelligenza artificiale per far inserire dalla cpu la pedina nella posizione ritenuta migliore
                        aiTris(tabella, pedina_turno, pedina_avversario);
                        printf("\nTurno giocatore %d\n", partita.gruppiGioco[i][j]);
                    }

                    //Stampa la tabella di gioco aggiornata
                    for (int k = 0; k < RIGHE; ++k)
                    {
                        if (k==0)
                        {
                            for (int l = 0; l < COLONNE; ++l)
                            {
                                switch (l)
                                {
                                    case VUOTO:
                                        printf("  1 ");
                                        break;

                                    case 1:
                                        printf("2 ");
                                        break;

                                    case 2:
                                        printf("3\n");
                                        break;
                                }
                            }
                        }

                        for (int l = 0; l < COLONNE; ++l)
                        {
                            if (l==0)
                            {
                                switch (k)
                                {
                                    case VUOTO:
                                        printf("1 ");
                                        break;

                                    case 1:
                                        printf("2 ");
                                        break;

                                    case 2:
                                        printf("3 ");
                                        break;
                                }
                            }

                            switch (tabella[k][l])
                            {
                                case VUOTO:
                                    printf("* ");
                                    break;

                                case 1:
                                    printf("x ");
                                    break;

                                case 2:
                                    printf("o ");
                                    break;
                            }
                        }
                        printf("\n");
                    }

                    //Ciclo per controllare se qualcuno ha vinto
                    for (int row = 0; row < RIGHE; ++row)
                    {
                        for (int col = 0; col < COLONNE; ++col)
                        {
                            //Controlla se qualcuno ha vinto in verticale
                            if ((row==0 && tabella[row][col]!=VUOTO && tabella[row][col]==tabella[row+1][col] && tabella[row][col]==tabella[row+2][col])
                                || (row==1 && tabella[row][col]!=VUOTO && tabella[row][col]==tabella[row-1][col] && tabella[row][col]==tabella[row+1][col])
                                || (row==2 && tabella[row][col]!=VUOTO && tabella[row][col]==tabella[row-2][col] && tabella[row][col]==tabella[row-1][col]))
                            {
                                vincitore = partita.gruppiGioco[i][tabella[row][col]-1]; //Setta il vincitore che ha la pedina nel punto controllato
                                fine_partita = true;
                            }
                            //Controlla se qualcuno ha vinto in orizzontale
                            else if ((col==0 && tabella[row][col]!=VUOTO && tabella[row][col]==tabella[row][col+1] && tabella[row][col]==tabella[row][col+2])
                                     || (col==1 && tabella[row][col]!=VUOTO && tabella[row][col]==tabella[row][col-1] && tabella[row][col]==tabella[row][col+1])
                                     || (col==2 && tabella[row][col]!=VUOTO && tabella[row][col]==tabella[row][col-2] && tabella[row][col]==tabella[row][col-1]))
                            {
                                vincitore = partita.gruppiGioco[i][tabella[row][col]-1]; //Setta il vincitore che ha la pedina nel punto controllato
                                fine_partita = true;
                            }
                            //Controlla se qualcuno ha vinto in obliquo direzione (\)
                            else if ((row==0 && col==0 && tabella[row][col]!=VUOTO && tabella[row][col]==tabella[row+1][col+1] && tabella[row][col]==tabella[row+2][col+2])
                                     || (row==1 && col==1 && tabella[row][col]!=VUOTO && tabella[row][col]==tabella[row-1][col-1] && tabella[row][col]==tabella[row+1][col+1])
                                     || (row==2 && col==2 && tabella[row][col]!=VUOTO && tabella[row][col]==tabella[row-2][col-2] && tabella[row][col]==tabella[row-1][col-1]))
                            {
                                vincitore = partita.gruppiGioco[i][tabella[row][col]-1]; //Setta il vincitore che ha la pedina nel punto controllato
                                fine_partita = true;
                            }
                            //Controlla se qualcuno ha vinto in obliquo direzione (/)
                            else if ((row==0 && col==2 && tabella[row][col]!=VUOTO && tabella[row][col]==tabella[row+1][col-1] && tabella[row][col]==tabella[row+2][col-2])
                                     || (row==1 && col==1 && tabella[row][col]!=VUOTO && tabella[row][col]==tabella[row-1][col+1] && tabella[row][col]==tabella[row+1][col-1])
                                     || (row==2 && col==0 && tabella[row][col]!=VUOTO && tabella[row][col]==tabella[row-2][col+2] && tabella[row][col]==tabella[row-1][col+1]))
                            {
                                vincitore = partita.gruppiGioco[i][tabella[row][col]-1]; //Setta il vincitore che ha la pedina nel punto controllato
                                fine_partita = true;
                            }
                        }
                    }

                    //Ciclo per controllare che la partita non sia finita in parità
                    for (int row = 0; row < RIGHE; ++row)
                    {
                        for (int col = 0; col < COLONNE; ++col)
                        {
                            //Se la posizione della tabella è vuota esegue:
                            if (tabella[col][row]==VUOTO)
                            {
                                pareggio++; //Incrementa la variabile di controllo del pareggio
                            }
                        }
                    }

                    //Se non vengono trovate celle vuote e la partita non è finita esegue:
                    if (pareggio==VUOTO && fine_partita==false)
                    {
                        printf("\nLa partita e' finita in partita', si rincomincia\n");

                        //Ciclo per resettare la tabella
                        for (int row = 0; row < RIGHE; ++row)
                        {
                            for (int col = 0; col < COLONNE; ++col)
                            {
                                tabella[row][col] = VUOTO; //Setta tutti i valori della matrice a 0
                            }
                        }

                        j = RESETTA_COLONNE; //Resetta la variabile j per far ricominciare a giocare il giocatore n.0
                    }
                    //Se la partita è terminata esegue
                    else if (fine_partita==true)
                    {
                        //Stampa il vincitore
                        printf("Ha vinto il giocatore n.%d\n", vincitore);
                    }
                }
            } while (fine_partita==false);
        }
        //Altrimenti esegue:
        else
        {
            //Genera randomicamente il vincitore
            vincitore = partita.gruppiGioco[i][rand()%partita.giocatori_per_gruppo];
        }

        //Ciclo per controllare se nel gruppo c'è il giocatore Riccardo Scateni
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Se è presente vince automaticamente
                    vincitore = Frontman_dello_SPR1D_GAME(vincitore, salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].nome, partita.gruppiGioco[i][j]);
                }
            }
        }

        //Ciclo per controllare quale giocatore del gruppo ha vinto
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            //Se il giocatore controllato è il vincitore esegue:
            if (vincitore==partita.gruppiGioco[i][j])
            {
                //Ciclo che controlla se il giocatore vincitore è controllato dall'utente
                for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
                {
                    //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                    if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                    {
                        //Incrementa il numero di mini-giochi vinti del giocatore selezionato
                        salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_tot_minigiochi_vinti++;
                    }
                }

                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = true;
                printf("\nIl giocatore vincitore del gruppo %d e' il n.%d\n", i+1, partita.gruppiGioco[i][j]);
            }
                //Altrimenti esegue:
            else
            {
                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = false;
            }
        }
    }

    return salvataggio;
}

//Funzione per l'intelligenza artificiale di Tris
void aiTris (int tabella[][COLONNE], int pedina_turno, int pedina_avversario)
{
    //Dichiarazione variabili locali
    int mossa_pc=0, riga, colonna;
    bool doppia=false;

    //"Intelligenza Artificiale" per far decide al computer dove inserire la pedina per riuscire a vincere
    for (int row = 0; row < RIGHE; ++row)
    {
        for (int col = 0; col < COLONNE; ++col)
        {
            //Controlla se può vincere in verticale
            if ((row==0 && tabella[row][col]==VUOTO && tabella[row+1][col]==pedina_turno && tabella[row+2][col]==pedina_turno)
                || (row==1 && tabella[row-1][col]==pedina_turno && tabella[row][col]==VUOTO && tabella[row+1][col]==pedina_turno)
                || (row==2 && tabella[row-2][col]==pedina_turno && tabella[row-1][col]==pedina_turno && tabella[row][col]==VUOTO))
            {
                tabella[row][col] = pedina_turno; //Inserisce la pedina nella posizione controllata
                return;
            }
                //Controlla se può vincere in orizzontale
            else if ((col==0 && tabella[row][col]==VUOTO && tabella[row][col+1]==pedina_turno && tabella[row][col+2]==pedina_turno)
                     || (col==1 && tabella[row][col-1]==pedina_turno && tabella[row][col]==VUOTO && tabella[row][col+1]==pedina_turno)
                     || (col==2 && tabella[row][col-2]==pedina_turno && tabella[row][col-1]==pedina_turno && tabella[row][col]==VUOTO))
            {
                tabella[row][col] = pedina_turno; //Inserisce la pedina nella posizione controllata
                return;
            }
                //Controlla se può vincere in obliquo direzione (\)
            else if ((row==0 && col==0 && tabella[row][col]==VUOTO && tabella[row+1][col+1]==pedina_turno && tabella[row+2][col+2]==pedina_turno)
                     || (row==1 && col==1 && tabella[row-1][col-1]==pedina_turno && tabella[row][col]==VUOTO && tabella[row+1][col+1]==pedina_turno)
                     || (row==2 && col==2 && tabella[row-2][col-2]==pedina_turno && tabella[row-1][col-1]==pedina_turno && tabella[row][col]==VUOTO))
            {
                tabella[row][col] = pedina_turno; //Inserisce la pedina nella posizione controllata
                return;
            }
                //Controlla se può vincere in obliquo direzione (/)
            else if ((row==0 && col==2 && tabella[row][col]==VUOTO && tabella[row+1][col-1]==pedina_turno && tabella[row+2][col-2]==pedina_turno)
                     || (row==1 && col==1 && tabella[row-1][col+1]==pedina_turno && tabella[row][col]==VUOTO && tabella[row+1][col-1]==pedina_turno)
                     || (row==2 && col==0 && tabella[row-2][col+2]==pedina_turno && tabella[row-1][col+1]==pedina_turno && tabella[row][col]==VUOTO))
            {
                tabella[row][col] = pedina_turno; //Inserisce la pedina nella posizione controllata
                return;
            }
        }
    }

    //"Intelligenza Artificiale" per far decide al computer dove inserire la pedina per riuscire a bloccare il giocatore
    for (int row = 0; row < RIGHE; ++row)
    {
        for (int col = 0; col < COLONNE; ++col)
        {
            //Controlla se può vincere in verticale
            if ((row==0 && tabella[row][col]==VUOTO && tabella[row+1][col]==pedina_avversario && tabella[row+2][col]==pedina_avversario)
                || (row==1 && tabella[row-1][col]==pedina_avversario && tabella[row][col]==VUOTO && tabella[row+1][col]==pedina_avversario)
                || (row==2 && tabella[row-2][col]==pedina_avversario && tabella[row-1][col]==pedina_avversario && tabella[row][col]==VUOTO))
            {
                tabella[row][col] = pedina_turno; //Inserisce la pedina nella posizione controllata
                return;
            }
                //Controlla se può vincere in orizzontale
            else if ((col==0 && tabella[row][col]==VUOTO && tabella[row][col+1]==pedina_avversario && tabella[row][col+2]==pedina_avversario)
                     || (col==1 && tabella[row][col-1]==pedina_avversario && tabella[row][col]==VUOTO && tabella[row][col+1]==pedina_avversario)
                     || (col==2 && tabella[row][col-2]==pedina_avversario && tabella[row][col-1]==pedina_avversario && tabella[row][col]==VUOTO))
            {
                tabella[row][col] = pedina_turno; //Inserisce la pedina nella posizione controllata
                return;
            }
                //Controlla se può vincere in obliquo direzione (\)
            else if ((row==0 && col==0 && tabella[row][col]==VUOTO && tabella[row+1][col+1]==pedina_avversario && tabella[row+2][col+2]==pedina_avversario)
                     || (row==1 && col==1 && tabella[row-1][col-1]==pedina_avversario && tabella[row][col]==VUOTO && tabella[row+1][col+1]==pedina_avversario)
                     || (row==2 && col==2 && tabella[row-2][col-2]==pedina_avversario && tabella[row-1][col-1]==pedina_avversario && tabella[row][col]==VUOTO))
            {
                tabella[row][col] = pedina_turno; //Inserisce la pedina nella posizione controllata
                return;
            }
                //Controlla se può vincere in obliquo direzione (/)
            else if ((row==0 && col==2 && tabella[row][col]==VUOTO && tabella[row+1][col-1]==pedina_avversario && tabella[row+2][col-2]==pedina_avversario)
                     || (row==1 && col==1 && tabella[row-1][col+1]==pedina_avversario && tabella[row][col]==VUOTO && tabella[row+1][col-1]==pedina_avversario)
                     || (row==2 && col==0 && tabella[row-2][col+2]==pedina_avversario && tabella[row-1][col+1]==pedina_avversario && tabella[row][col]==VUOTO))
            {
                tabella[row][col] = pedina_turno; //Inserisce la pedina nella posizione controllata
                return;
            }
        }
    }

    //Se non ci sono mosse convenienti posiziona la pedina in una cella vuota a caso
    do //Ciclo per continuare a generare una posizione nella tabella in caso quella scelta sia già occupata
    {
        doppia = false; //Resetta la variabile di controllo

        riga = rand() % RIGHE; //Genera casualmente la riga
        colonna = rand() % COLONNE; //Genera casualmente la colonna

        //Ciclo per controllare se la posizione scelta è già occupata
        for (int k = 0; k < RIGHE; ++k)
        {
            for (int l = 0; l < COLONNE ; ++l)
            {
                //Se la posizione è occupata esegue:
                if (tabella[riga][colonna]!=VUOTO)
                {
                    doppia = true;
                }
            }
        }
    } while (doppia==true);

    tabella[riga][colonna] = pedina_turno; //Setta la pedina del pc nella posizione scelta
}

//Funzione gioco Murra
Salvataggio Murra (Salvataggio salvataggio, Partita partita)
{
    //Dichiarazione variabili locali
    int vincitore, posizione_utente, n_scelto[GRANDEZZA_GRUPPI2], somma_scelta[GRANDEZZA_GRUPPI2], somma_turno;
    bool controllo=false, utente=false, controllo_numero=false, fine_partita=false;

    partita.giocatori_per_gruppo = GRANDEZZA_GRUPPI2;

    //Stampa della descrizione del gioco
    printf("\n------------------------------> Murra <------------------------------\n"
           " Per questo gioco ogni giocatore dovra' un numero compreso tra 1 e 5\n"
           "                  e cercare di indovinare la somma\n"
           "     delle dita da lui puntate + quelle puntate dall'avversario.\n"
           "        Vince il giocatore che riesce ad indovinare la somma\n"
           "--------------------------> BUONA FORTUNA <--------------------------\n");

    //Crea i gruppi di giocatori
    partita = creaGruppi_Partita(partita, salvataggio.N_partecipanti);

    //Esegue il gioco per ogni gruppo creato
    for (int i = 0; i < partita.n_gruppi; ++i)
    {
        printf("\nSta giocando il gruppo n: %d\n", i+1);
        printf("---> PREMI INVIO PER CONTINUARE <---");
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        controllo = false; //Resetto la variabile per controllare se nel gruppo un giocatore è controllato dall'utente
        fine_partita = false; //Resetto la variabile per capire se la partita è finita

        //Ciclo per controllare se esiste un giocatore controllato dall'utente
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Incrementa il numero di mini-giochi giocati del giocatore selezionato
                    salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_tot_minigiochi_giocati++;
                    controllo = true;
                }
            }
        }

        //Se nel gruppo c'è un giocatore controllato dall'utente esegue:
        if (controllo==true)
        {
            do //Ciclo per continuare a far continuare la partita finché un giocatore non vince
            {
                for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
                {
                    utente = false; //Resetta per controllare se il giocatore che esegue il turno è controllato dall'utente

                    //Ciclo per controllare se il giocatore che sta eseguendo il turno è controllato dall'utente
                    for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
                    {
                        //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                        if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                        {
                            utente = true;
                            posizione_utente = salvataggio.giocatoriUtente_partecipanti[k]; //Salva la posizione dell'utente nell'array di giocatori
                        }
                    }

                    //Se il giocatore che sta eseguendo il turno è controllato dall'utente esegue:
                    if (utente==true)
                    {
                        printf("\nGiocatore %s, id:%d e' il tuo turno\n", salvataggio.arrayGiocatori[posizione_utente].nome, salvataggio.arrayGiocatori[posizione_utente].id);

                        do //Ciclo per continuare a far inserire il numero scelto
                        {
                            controllo_numero = false; //Resetta la variabile per controllare se il numero inserito rispetta la condizioni date

                            printf("Scegli un numero tra 1 e 5:");
                            scanf("%d", &n_scelto[j]);
                            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

                            //Se il numero scelto non rispetta la condizioni esegue:
                            if ((n_scelto[j] < MIN_N_SCELTO) || (n_scelto[j] > MAX_N_SCELTO))
                            {
                                printf("ATTENZIONE devi inserire un numero tra 1 e 5\n");
                                controllo_numero = true;
                            }
                        } while (controllo_numero==true);

                        do //Ciclo per continuare a far inserire la somma scelta
                        {
                            controllo_numero = false; //Resetta la variabile per controllare se il numero inserito rispetta la condizioni date

                            printf("La somma di quanto sara'?");
                            scanf("%d", &somma_scelta[j]);
                            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

                            //Se il numero scelto non rispetta la condizioni esegue:
                            if ((somma_scelta[j] < MIN_SOMMA_SCELTA) || (somma_scelta[j] > MAX_SOMMA_SCELTA))
                            {
                                printf("ATTENZIONE devi inserire un numero tra 2 e 10\n");
                                controllo_numero = true;
                            }
                        } while (controllo_numero==true);
                    }
                    //Altrimenti esegue:
                    else
                    {
                        //Genera randomicamente il numero da scegliere tra 0 e 5
                        n_scelto[j] =  MIN_N_SCELTO + rand() % (MAX_N_SCELTO-MIN_N_SCELTO+1);

                        //Se io numero scelto è maggiore o uguale alla somma minima esegue
                        if (n_scelto[j] >= MIN_SOMMA_SCELTA)
                        {
                            //Genera randomicamente la somma pensata, la quale sarà tra il numero scelto+1 e 5(numero maggiore che può scegliere l'avversario) + il numero scelto
                            somma_scelta[j] = (n_scelto[j]+1) + rand() % ((MAX_N_SCELTO+n_scelto[j])-(n_scelto[j]+1)+1);
                        }
                        //Altrimenti esegue:
                        else
                        {
                            //Genera randomicamente la somma pensata, la quale sarà tar il numero minimo possibile(2) e il numero massimo che si può scegliere(5)+1
                            somma_scelta[j] = MIN_SOMMA_SCELTA + rand() % ((MAX_N_SCELTO+1)-MIN_SOMMA_SCELTA+1);
                        }
                    }
                }

                //Output risultati turno
                printf("\nI numeri scelti sono stati:\n"
                       "Giocatore id:%d n.%d\n"
                       "Giocatore id:%d n.%d\n", partita.gruppiGioco[i][GIOCATORE1], n_scelto[GIOCATORE1], partita.gruppiGioco[i][GIOCATORE2], n_scelto[GIOCATORE2]);
                printf("\nLe somme scelte sono state:\n"
                       "Giocatore id:%d n.%d\n"
                       "Giocatore id:%d n.%d\n", partita.gruppiGioco[i][GIOCATORE1], somma_scelta[GIOCATORE1], partita.gruppiGioco[i][GIOCATORE2], somma_scelta[GIOCATORE2]);

                //Genero la somma dei numeri scelti dai due giocatori
                somma_turno = n_scelto[GIOCATORE1] + n_scelto[GIOCATORE2];

                printf("\nLa somma finale e': %d\n", somma_turno);

                //Se entrambi i giocatori hanno indovinato esegue:
                if (somma_scelta[GIOCATORE1]==somma_turno && somma_scelta[GIOCATORE2]==somma_turno)
                {
                    printf("\nEntrambi i giocatori hanno indovinato, il turno si ripete\n");
                }
                //Se ha indovinato il giocatore 1 esegue:
                else if (somma_scelta[GIOCATORE1]==somma_turno)
                {
                    vincitore = partita.gruppiGioco[i][GIOCATORE1]; //Vince il giocatore 1
                    printf("\nIl giocatore id:%d ha indovinato\n", partita.gruppiGioco[i][GIOCATORE1]);
                    fine_partita = true;
                }
                //Se ha indovinato il giocatore 2 esegue:
                else if (somma_scelta[GIOCATORE2]==somma_turno)
                {
                    vincitore = partita.gruppiGioco[i][GIOCATORE2]; //Vince il giocatore 2
                    printf("\nIl giocatore id:%d ha indovinato\n", partita.gruppiGioco[i][GIOCATORE2]);
                    fine_partita = true;
                }
            } while (fine_partita == false);
        }
        //Altrimenti esegue:
        else
        {
            //Genera randomicamente il vincitore
            vincitore = partita.gruppiGioco[i][rand()%partita.giocatori_per_gruppo];
        }

        //Ciclo per controllare se nel gruppo c'è il giocatore Riccardo Scateni
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Se è presente vince automaticamente
                    vincitore = Frontman_dello_SPR1D_GAME(vincitore, salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].nome, partita.gruppiGioco[i][j]);
                }
            }
        }

        //Ciclo per controllare quale giocatore del gruppo ha vinto
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            //Se il giocatore controllato è il vincitore esegue:
            if (vincitore==partita.gruppiGioco[i][j])
            {
                //Ciclo che controlla se il giocatore vincitore è controllato dall'utente
                for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
                {
                    //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                    if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                    {
                        //Incrementa il numero di mini-giochi vinti del giocatore selezionato
                        salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_tot_minigiochi_vinti++;
                    }
                }

                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = true;
                printf("\nIl giocatore vincitore del gruppo %d e' il n.%d\n", i+1, partita.gruppiGioco[i][j]);
            }
            //Altrimenti esegue:
            else
            {
                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = false;
            }
        }
    }

    return salvataggio;
}

//Funzione gioco Biglie
Salvataggio Biglie (Salvataggio salvataggio, Partita partita)
{
    //Dichiarazione variabili locali
    int vincitore, posizione_utente, biglie_puntate[GRANDEZZA_GRUPPI2], biglie_rimaste[GRANDEZZA_GRUPPI2], risp[GRANDEZZA_GRUPPI2], somma_puntate;
    bool controllo=false, utente=false, ripeti=false, fine_partita=false;

    partita.giocatori_per_gruppo = GRANDEZZA_GRUPPI2;

    //Stampa della descrizione del gioco
    printf("\n----------------------------> Biglie <-----------------------------\n"
                  "     Per questo gioco ogni giocatore avra' in mano 10 biglie,\n"
                  "      a ogni turno entrambi i giocatori puntano delle biglie\n"
                  "  e devono riuscire ad indovinare se la somma e' pari o dispari,\n"
                  "  il giocatore che riesce ad indovinare riceve le biglie puntate.\n"
                  " Il gioco termina quando uno dei due giocatori rimane con 0 biglie\n"
                  "-------------------------> BUONA FORTUNA <-------------------------\n");

    //Crea i gruppi di giocatori
    partita = creaGruppi_Partita(partita, salvataggio.N_partecipanti);

    //Esegue il gioco per ogni gruppo creato
    for (int i = 0; i < partita.n_gruppi; ++i)
    {
        printf("\nSta giocando il gruppo n: %d\n", i+1);
        printf("---> PREMI INVIO PER CONTINUARE <---");
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        controllo = false; //Resetto la variabile per controllare se nel gruppo un giocatore è controllato dall'utente

        //Ciclo per controllare se esiste un giocatore controllato dall'utente
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Incrementa il numero di mini-giochi giocati del giocatore selezionato
                    salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_tot_minigiochi_giocati++;
                    controllo = true;
                }
            }
        }

        //Se nel gruppo c'è un giocatore controllato dall'utente esegue:
        if (controllo==true)
        {
            //Setta la biglie in mano a ogni giocatore a 10
            biglie_rimaste[GIOCATORE1] = N_BIGLIE_GIOCATORE;
            biglie_rimaste[GIOCATORE2] = N_BIGLIE_GIOCATORE;

            fine_partita = false; //Resetta la variabile per controllare se la partita è finita

            do //Ciclo per continuare a far continuare la partita finché un giocatore non vince
            {
                for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
                {
                    utente = false; //Resetta per controllare se il giocatore che esegue il turno è controllato dall'utente

                    //Ciclo per controllare se il giocatore che sta eseguendo il turno è controllato dall'utente
                    for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
                    {
                        //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                        if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                        {
                            utente = true;
                            posizione_utente = salvataggio.giocatoriUtente_partecipanti[k];
                        }
                    }

                    //Se il giocatore che sta eseguendo il turno è controllato dall'utente esegue:
                    if (utente==true)
                    {
                        do //Ciclo per continuare a far inserire il numero di biglie puntate se quelle inserite non vengono accettate
                        {
                            ripeti = false; //Resetta la variabile per far ripetere il ciclo

                            printf("\nGiocatore %s, quante biglie vuoi scommettere?\n"
                                   "           (biglie rimanenti: %d)\n", salvataggio.arrayGiocatori[posizione_utente].nome, biglie_rimaste[j]);
                            scanf("%d", &biglie_puntate[j]);
                            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

                            //Se non viene puntata neanche una biglia esegue:
                            if (biglie_puntate[j] <= VUOTO)
                            {
                                printf("ATTENZIONE devi inserire almeno una biglia\n");
                                ripeti = true;
                            }
                            //Se vengono puntate più biglie rispetto a quelle presenti in mano esegue:
                            else if (biglie_puntate[j] > biglie_rimaste[j])
                            {
                                printf("ATTENZIONE non hai abbastanza biglie\n");
                                ripeti = true;
                            }
                        } while (ripeti==true);

                        //Toglie le biglie puntate dal giocatore da quelle presenti nella sua mano
                        biglie_rimaste[j] -= biglie_puntate[j];

                        do //Ciclo per continuare a far inserire pari o dispari
                        {
                            ripeti = false; //Resetta la variabile per far ripetere il ciclo

                            printf("\nGiocatore %s, secondo te la somma sara' (1)dispari o (2)pari?\n", salvataggio.arrayGiocatori[posizione_utente].nome);
                            scanf("%d", &risp[j]);
                            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

                            //Se la risposta inserita non è ne pari ne dispari esegue:
                            if (risp[j] != PARI && risp[j] != DISPARI)
                            {
                                printf("ATTENZIONE devi inserire uno dei due numeri richiesti\n");
                                ripeti = true;
                            }
                        } while (ripeti==true);
                    }
                    //Altrimenti esegue:
                    else
                    {
                        //Genera randomicamente il numero di biglie da puntare
                        biglie_puntate[j] = 1 + rand() % biglie_rimaste[j];

                        //Toglie le biglie puntate da quelle presenti nella sua mano
                        biglie_rimaste[j] -= biglie_puntate[j];

                        //Sceglie randomicamente tra pari o dispari
                        risp[j] = DISPARI + rand() % PARI;
                    }
                }

                //Somma le biglie puntate da entrambi i giocatori
                somma_puntate = biglie_puntate[GIOCATORE1] + biglie_puntate[GIOCATORE2];
                printf("\nLa somma delle biglie puntate e': %d", somma_puntate);

                //Se entrambi i giocatori hanno scelto la stessa risposta esegue:
                if (risp[GIOCATORE1] == risp[GIOCATORE2])
                {
                    //Se hanno scelto entrambi di essere pari esegue:
                    if (risp[GIOCATORE1] == PARI)
                    {
                        printf("\nEntrambi i giocatori hanno scelto pari, il turno si ripete\n");
                    }
                    //Se hanno scelto entrambi di essere dispari esegue:
                    else
                    {
                        printf("\nEntrambi i giocatori hanno scelto dispari, il turno si ripete\n");
                    }

                    //Aggiunge le biglie puntate nel turno da entrambi i giocatori alle biglie in mano
                    biglie_rimaste[GIOCATORE1] += biglie_puntate[GIOCATORE1];
                    biglie_rimaste[GIOCATORE2] += biglie_puntate[GIOCATORE2];
                }
                //Altrimenti esegue:
                else
                {
                    //Ciclo che si esegue per il numero di giocatori nel gruppo, serve per capire chi ha vinto il turno
                    for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
                    {
                        //Se la somma delle biglie puntate è un numero pari e il giocatore preso in analisi ha scelto pari esegue:
                        if ((somma_puntate % 2 == VUOTO) && risp[j]==PARI)
                        {
                            printf("\nIl giocatore n.%d, ha indovinato e ha preso le biglie\n", partita.gruppiGioco[i][j]);
                            biglie_rimaste[j] += somma_puntate; //Vengono aggiunte tutte le biglie puntate alla mano del giocatore vincente
                        }
                        //Se la somma delle biglie puntate è un numero dispari e il giocatore preso in analisi ha scelto dispari esegue:
                        else if ((somma_puntate % 2 != VUOTO) && risp[j]==DISPARI)
                        {
                            printf("\nIl giocatore n.%d, ha indovinato e ha preso le biglie\n", partita.gruppiGioco[i][j]);
                            biglie_rimaste[j] += somma_puntate; //Vengono aggiunte tutte le biglie puntate alla mano del giocatore vincente
                        }
                    }
                }

                //Se il giocatore 1 ha terminato le biglie in mano esegue:
                if (biglie_rimaste[GIOCATORE1] == VUOTO)
                {
                    printf("\nIl giocatore n.%d ha terminato le biglie\n", partita.gruppiGioco[i][GIOCATORE1]);
                    vincitore = partita.gruppiGioco[i][GIOCATORE2]; //Vince il giocatore 2
                    fine_partita = true;
                }
                //Se il giocatore 2 ha terminato le biglie in mano esegue:
                else if (biglie_rimaste[GIOCATORE2] == VUOTO)
                {
                    printf("\nIl giocatore n.%d ha terminato le biglie\n", partita.gruppiGioco[i][GIOCATORE2]);
                    vincitore = partita.gruppiGioco[i][GIOCATORE1]; //Vince il giocatore 1
                    fine_partita = true;
                }
            } while (fine_partita==false);
        }
        //Altrimenti esegue:
        else
        {
            //Genera randomicamente il vincitore
            vincitore = partita.gruppiGioco[i][rand()%partita.giocatori_per_gruppo];
        }

        //Ciclo per controllare se nel gruppo c'è il giocatore Riccardo Scateni
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Se è presente vince automaticamente
                    vincitore = Frontman_dello_SPR1D_GAME(vincitore, salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].nome, partita.gruppiGioco[i][j]);
                }
            }
        }

        //Ciclo per controllare quale giocatore del gruppo ha vinto
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            //Se il giocatore controllato è il vincitore esegue:
            if (vincitore==partita.gruppiGioco[i][j])
            {
                //Ciclo che controlla se il giocatore vincitore è controllato dall'utente
                for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
                {
                    //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                    if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                    {
                        //Incrementa il numero di mini-giochi vinti del giocatore selezionato
                        salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_tot_minigiochi_vinti++;
                    }
                }

                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = true;
                printf("\nIl giocatore vincitore del gruppo %d e' il n.%d\n", i+1, partita.gruppiGioco[i][j]);
            }
                //Altrimenti esegue:
            else
            {
                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = false;
            }
        }
    }

    return salvataggio;
}

//Funzione gioco Ponte di Vetro
Salvataggio PonteVetro (Salvataggio salvataggio, Partita partita)
{
    //Dichiarazione variabili locali
    int vincitore, ponte[LUNGHEZZA][LARGHEZZA], posizione_fragile, posizione_ponte, scelta, eliminati;
    bool controllo=false, utente=false, spostamento=false, sbaglio=false;

    partita.giocatori_per_gruppo = GRANDEZZA_GRUPPI4;

    //Stampa della descrizione del gioco
    printf("\n--------------------------------------> Ponte di Vetro <---------------------------------------\n"
           " Il gioco consiste nell'attraversamento di un ponte composto da 3 coppie di vetri consecutive,\n"
           "               in cui uno dei due vetri della coppia e' fragile, e l'altro no.\n"
           "              Vince il primo giocatore che riesce ad attraversarlo senza cadere\n"
           "---------------------------------------> BUONA FORTUNA <---------------------------------------\n");

    //Crea i gruppi di giocatori
    partita = creaGruppi_Partita(partita, salvataggio.N_partecipanti);

    //Esegue il gioco per ogni gruppo creato
    for (int i = 0; i < partita.n_gruppi; ++i)
    {
        printf("\nSta giocando il gruppo n: %d\n", i+1);
        printf("---> PREMI INVIO PER CONTINUARE <---");
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        controllo = false; //Resetto la variabile per controllare se nel gruppo un giocatore è controllato dall'utente

        //Ciclo per controllare se esiste un giocatore controllato dall'utente
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Incrementa il numero di mini-giochi giocati del giocatore selezionato
                    salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_tot_minigiochi_giocati++;
                    controllo = true;
                }
            }
        }

        //Se nel gruppo c'è un giocatore controllato dall'utente esegue:
        if (controllo==true)
        {
            posizione_ponte = LUNGHEZZA-1; //Resetta la variabile per controllare a che punto del ponte sono arrivati
            eliminati = VUOTO; //Resetta la variabile per contare i giocatori eliminati per ogni gruppo

            //Ciclo per creare il ponte, in cui in ogni coppia di vetri uno è fragile e l'altro no
            for (int j = 0; j < LUNGHEZZA; ++j)
            {
                //Genera randomicamente quale dei due vetri è fragile
                posizione_fragile = rand() % LARGHEZZA;

                //Ciclo per settare il vetro scelto a fragile e l'altro no
                for (int k = 0; k < LARGHEZZA; ++k)
                {
                    if (k==posizione_fragile)
                    {
                        ponte[j][k] = FRAGILE;
                    }
                    else
                    {
                        ponte[j][k] = VUOTO;
                    }
                }
            }

            //Stampa la tabella di gioco
            printf("\n");
            for (int j = 0; j < LUNGHEZZA; ++j)
            {
                if (posizione_ponte < j)
                {
                    for (int k = 0; k < LARGHEZZA; ++k)
                    {
                        if (ponte[j][k]==FRAGILE)
                        {
                            printf(" *");
                        }
                        else
                        {
                            printf(" +");
                        }
                        printf("\n");
                    }
                }
                else
                {
                    for (int k = 0; k < LARGHEZZA; ++k)
                    {
                        printf(" +");
                    }
                    printf("\n");
                }
            }
            printf(" 1 2 \n");

            //Ciclo per far eseguire il gioco a ogni giocatore del gruppo
            for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
            {
                utente = false; //Resetta per controllare se il giocatore che esegue il turno è controllato dall'utente

                //Ciclo per controllare se il giocatore che sta eseguendo il turno è controllato dall'utente
                for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
                {
                    //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                    if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                    {
                        utente = true;
                    }
                }

                //Se il giocatore che sta eseguendo il turno è controllato dall'utente esegue:
                if (utente==true)
                {
                    do //Ciclo per continuare a far inserire il numero scelto
                    {
                        spostamento = true;

                        printf("\nIn quale vetro della coppia vuoi passare?\n");
                        scanf("%d", &scelta);
                        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio
                        scelta--;  //Decrementa la risposta per ottenere la posizione del vetro scelto nella matrice

                        //Se il vetro scelto non esiste esegue:
                        if (scelta != VETRO_SINISTRA && scelta != VETRO_DESTRA)
                        {
                            printf("\nATTENZIONE, inserire uno dei numeri richiesti\n");
                            spostamento = false;
                        }
                    } while (spostamento==false);
                }
                //Altrimenti esegue:
                else
                {
                    //Se nel turno precedente ha sbagliato qualcuno esegue:
                    if (sbaglio==true)
                    {
                        //Switch per far scegliere alla cpu il vetro opposto rispetto a quale il giocatore precedente è stato eliminato
                        switch (scelta)
                        {
                            //Se è stato scelto il vetro di sinistra
                            case VETRO_SINISTRA:
                                scelta = VETRO_DESTRA; //La cpu sceglie il vetro di destra
                                break;

                            //Se è stato scelto il vetro di destra
                            case VETRO_DESTRA:
                                scelta = VETRO_SINISTRA; //La cpu sceglie il vetro di sinistra
                                break;
                        }
                    }
                    //Altrimenti esegue:
                    else
                    {
                        scelta = rand() % LARGHEZZA; //Sceglie randomicamente uno dei due vetri
                    }

                    //Se il vetro scelto è quello di sinistra esegue:
                    if (scelta==VETRO_SINISTRA)
                    {
                        printf("Il giocatore n.%d ha scelto il vetro di sinistra\n", partita.gruppiGioco[i][j]);
                    }
                    //Se il vetro scelto è quello di destra esegue:
                    else
                    {
                        printf("Il giocatore n.%d ha scelto il vetro di destra\n", partita.gruppiGioco[i][j]);
                    }
                }

                sbaglio = false; //Resetta la variabile per capire se il giocatore precedente ha sbagliato

                //Se il vetro scelto non è fragile esegue:
                if (ponte[posizione_ponte][scelta]!=FRAGILE)
                {
                    printf("\nIl giocatore n.%d ha indovinato\n", partita.gruppiGioco[i][j]);
                    posizione_ponte--; //Decrementa la variabile posizione ponte per passare alla coppia di vetri successivi
                    j--; //Decrementa la variabile j per far rieseguire il turno al giocatore
                }
                //Se il vetro scelto è fragile esegue:
                else
                {
                    printf("\nIl vetro scelto dal giocatore n.%d era fragile ed e' caduto, eliminato\n", partita.gruppiGioco[i][j]);
                    eliminati++; //Incrementa la variabile per contare i giocatori eliminati
                    sbaglio = true;
                }

                //Stampa il ponte aggiornato
                printf("\n");
                for (int k = 0; k < LUNGHEZZA; ++k)
                {
                    if (posizione_ponte < k || (posizione_ponte == k && sbaglio==true))
                    {
                        for (int l = 0; l < LARGHEZZA; ++l)
                        {
                            if (ponte[k][l]==FRAGILE)
                            {
                                printf(" *");
                            }
                            else
                            {
                                printf(" +");
                            }
                        }
                        printf("\n");
                    }
                    else
                    {
                        for (int l = 0; l < LARGHEZZA; ++l)
                        {
                            printf(" +");
                        }
                        printf("\n");
                    }
                }
                printf(" 1 2 \n");

                //Se il giocatore che sta eseguendo il turno ha superato il ponte esegue:
                if (posizione_ponte < VUOTO)
                {
                    printf("\nIl giocatore n.%d ha superato il ponte\n", partita.gruppiGioco[i][j+1]);
                    vincitore = partita.gruppiGioco[i][j+1]; //Setta il giocatore che sta eseguendo il turno vincitore
                    j = partita.giocatori_per_gruppo; //Porta j al valore 4 per uscire dalla partita
                }
                //Se sono stati eliminati 3 giocatori esegue:
                else if (eliminati == LUNGHEZZA)
                {
                    printf("\nIl giocatore n.%d ha vinto perche' tutti prima di lui sono crollati\n", partita.gruppiGioco[i][j+1]);
                    vincitore = partita.gruppiGioco[i][j+1]; //Setta l'ultimo giocatore vincitore
                    j = partita.giocatori_per_gruppo; //Porta j al valore 4 per uscire dalla partita
                }
            }
        }
        //Altrimenti esegue:
        else
        {
            //Genera randomicamente il vincitore
            vincitore = partita.gruppiGioco[i][rand()%partita.giocatori_per_gruppo];
        }

        //Ciclo per controllare se nel gruppo c'è il giocatore Riccardo Scateni
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Se è presente vince automaticamente
                    vincitore = Frontman_dello_SPR1D_GAME(vincitore, salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].nome, partita.gruppiGioco[i][j]);
                }
            }
        }

        //Ciclo per controllare quale giocatore del gruppo ha vinto
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            //Se il giocatore controllato è il vincitore esegue:
            if (vincitore==partita.gruppiGioco[i][j])
            {
                //Ciclo che controlla se il giocatore vincitore è controllato dall'utente
                for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
                {
                    //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                    if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                    {
                        //Incrementa il numero di mini-giochi vinti del giocatore selezionato
                        salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_tot_minigiochi_vinti++;
                    }
                }

                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = true;
                printf("\nIl giocatore vincitore del gruppo %d e' il n.%d\n", i+1, partita.gruppiGioco[i][j]);
            }
                //Altrimenti esegue:
            else
            {
                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = false;
            }
        }
    }

    return salvataggio;
}

//Funzione gioco Impiccato
Salvataggio Impiccato (Salvataggio salvataggio, Partita partita)
{
    //Dichiarazione variabili locali
    Dizionario dizionario;
    int fraseScelta, lunghezza_frase, tentativi[GRANDEZZA_GRUPPI4]={VUOTO}, vincitore, posizione_utente, fine_tentativi, conta_mancanti;
    char lettera, lettere_usate[LETTERE_ALFABETO]={VUOTO}, lettera_analizzata;
    bool controllo=false, utente=false, controllo_lettera=false, controllo_doppia=false, indovinato=false, fine_partita=false;

    partita.giocatori_per_gruppo = GRANDEZZA_GRUPPI4;

    //Stampa della descrizione del gioco
    printf("\n--------------------> Impiccato <---------------------\n"
           " Il gioco consiste nell'indovinare una parola scelta\n"
           "         a caso da un dizionario di parole.\n"
           "      Vince il giocatore che completa la parola\n"
           "-------------------> BUONA FORTUNA <------------------\n");

    //Crea i gruppi di giocatori
    partita = creaGruppi_Partita(partita, salvataggio.N_partecipanti);

    //Funzione per decidere il dizionario da utilizzare
    dizionario = scegliDizionario();

    for (int i = 0; i < partita.n_gruppi; ++i)
    {
        printf("\nSta giocando il gruppo n: %d\n", i+1);
        printf("---> PREMI INVIO PER CONTINUARE <---");
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        controllo = false; //Resetto la variabile per controllare se nel turno sta giocando un giocatore utente

        //Ciclo per controllare se esiste un giocatore controllato dall'utente
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Incrementa il numero di mini-giochi giocati del giocatore selezionato
                    salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_tot_minigiochi_giocati++;
                    controllo = true;
                }
            }
        }

        fraseScelta = rand() % dizionario.n_frasi; //Genera un numero casuale tra 0 e n_frasi-1, il quale sarà la posizione nell'array di frasi della frase scelta per giocare

        lunghezza_frase = strlen(dizionario.frasi[fraseScelta]); //Conta da quanti caratteri è composta la frase scelta

        fine_tentativi = 0; //Resetta la variabile per contare la fine dei tentativi

        //Se nel gruppo c'è un giocatore controllato dall'utente esegue:
        if (controllo==true)
        {
            //Ciclo che serve per stampare la tabella della parola
            printf("\n");
            for (int k = 0; k < lunghezza_frase; ++k)
            {
                controllo_lettera = false; //resetta la variabile per controllare se stampare o meno '_'

                //Assegno la lettera analizzata a una variabile d'appoggio per non modificare la frase originale in caso di conversione
                lettera_analizzata = dizionario.frasi[fraseScelta][k];

                //Se la lettera analizzata è uno spazio esegue:
                if (lettera_analizzata==' ')
                {
                    printf(" ");
                }
                    //Se la lettera analizzata è un punto esegue:
                else if (lettera_analizzata=='.')
                {
                    printf(".");
                }
                    //Se la lettera analizzata è una virgola esegue:
                else if (lettera_analizzata==',')
                {
                    printf(",");
                }
                    //Se la lettera analizzata è un punto e virgola esegue:
                else if (lettera_analizzata==';')
                {
                    printf(";");
                }
                    //Se la lettera analizzata è un punto esclamativo esegue:
                else if (lettera_analizzata=='!')
                {
                    printf("!");
                }
                    //Se la lettera analizzata è un punto di domanda esegue:
                else if (lettera_analizzata=='?')
                {
                    printf("?");
                }
                    //Altrimenti esegue:
                else
                {
                    printf("_");
                }
            }
            printf("\n\n");

            do //Ciclo per continuare a far continuare la partita finché un giocatore non vince
            {
                //Ciclo per far giocare un giocatore di un gruppo
                for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
                {
                    indovinato = false; //Resetta la variabile per capire se un giocatore ha indovinato la lettera scelta

                    //Se il giocatore selezionato ha ancora a disposizione dei tentativi fa giocare il turno
                    if (tentativi[j] < MAX_TENTATIVI)
                    {
                        utente = false; //Resetta la varibile per controllare se il giocatore che sta giocando è un utente

                        //Ciclo per controllare se il giocatore che sta eseguendo il turno è controllato dall'utente
                        for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
                        {
                            //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                            if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                            {
                                utente = true;
                                posizione_utente = salvataggio.giocatoriUtente_partecipanti[k]; //Salva la posizione dell'utente nell'array di giocatori
                            }
                        }

                        do //Ciclo per continuare a far continuare a inserire la lettera al giocatore in caso quella scelta non rispetti le condizioni date oppure nel caso sia già stata inserita
                        {
                            controllo_doppia = false; //Resetta la variabile per controllare se una lettera è gia stata inserita

                            //Se il giocatore che sta eseguendo il turno è controllato dall'utente esegue:
                            if (utente==true)
                            {
                                do //Ciclo per continuare a far continuare a inserire la lettera al giocatore in caso quella scelta non rispetti le condizioni date
                                {
                                    controllo_lettera = false; //Resetta la variabile di controllo della lettera inserita

                                    //Output della domanda
                                    printf("Giocatore %s, id:%d che lettera vuoi inserire?", salvataggio.arrayGiocatori[posizione_utente].nome, salvataggio.arrayGiocatori[posizione_utente].id);
                                    //Richiesta di input
                                    scanf("%c", &lettera);
                                    while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

                                    //Se la lettera scelta non rispetta la condizioni scelte esegue:
                                    if ((lettera < 'A' || lettera > 'Z') && (lettera < 'a' || lettera > 'z'))
                                    {
                                        printf("ATTENZIONE puoi inserire solo lettere non accentate\n");
                                        controllo_lettera = true;
                                    }
                                } while (controllo_lettera==true);

                                //Se la lettera inserita è maiuscola la converte in minuscola per rendere il programma case sensitive
                                if (lettera >= 'A' && lettera <= 'Z')
                                {
                                    lettera+=CONVERSIONE_LETTERA; //Somma 32 (differenza tra A e a nella tabella ASCII) alla lettera scelta per trasformarla in minuscola
                                }
                            }
                            //Altrimenti esegue:
                            else
                            {
                                //Genera randomicamente una lettera compresa tra 'a' e 'z'
                                lettera = 'a' + rand() % ('z'-'a'+1);
                            }

                            //Ciclo per controllare che la lettera scelta non sia già stata inserita
                            for (int k = 0; k < LETTERE_ALFABETO; ++k)
                            {
                                //Se la lettera risulta essere già stata inserita esegue:
                                if (lettera==lettere_usate[k])
                                {
                                    //Se il giocatore che sta esegue il turno è controllato dall'utente esegue:
                                    if (utente==true)
                                    {
                                        printf("ATTENZIONE la lettera scelta e' gia' stata inserita\n");
                                    }
                                    controllo_doppia = true;
                                }
                            }
                        } while (controllo_doppia==true);

                        //Se il giocatore che sta eseguendo il turno non è controllato dall'utente esegue:
                        if (utente==false)
                        {
                            printf("Il giocatore cpu id:%d ha scelto la lettera '%c'\n", partita.gruppiGioco[i][j], lettera);
                        }

                        //Ciclo per inserire la lettera scelta nella prima posizione libera dell'array di lettere usate
                        for (int k = 0; k < LETTERE_ALFABETO; ++k)
                        {
                            //Se la posizione controllata risulta vuota esegue:
                            if (lettere_usate[k]==VUOTO)
                            {
                                lettere_usate[k] = lettera; //Assegna la lettera scelta alla posizione k
                                k = LETTERE_ALFABETO; //porta k allo stesso valore delle lettere dell'alfabeto per non fare rieseguire il ciclo
                            }
                        }

                        //Ciclo per vedere se la lettera scelta dal giocatore è presente all'interno della frase/parola
                        for (int k = 0; k < lunghezza_frase; ++k)
                        {
                            //Assegno la lettera analizzata a una variabile d'appoggio per non modificare la frase originale in caso di conversione
                            lettera_analizzata = dizionario.frasi[fraseScelta][k];

                            //Se la lettera analizzata è maiuscola la converte in minuscola per rendere il programma case sensitive
                            if (lettera_analizzata >= 'A' && lettera_analizzata <= 'Z')
                            {
                                lettera_analizzata += CONVERSIONE_LETTERA; //Somma 32 (differenza tra A e a nella tabella ASCII) alla lettera scelta per trasformarla in minuscola
                            }

                            //Se la lettera scelta corrisponde alla lettera analizzata esegue:
                            if (lettera==dizionario.frasi[fraseScelta][k])
                            {
                                indovinato=true; //porta la variabile indovinato a true per non fare abbassare i tentativi disponibili
                                printf("INDOVINATO, la lettera '%c' e' presente nella parola\n", lettera);
                                k = lunghezza_frase; //porta k allo stesso valore della lunghezza della frase per non fare rieseguire il ciclo
                            }
                        }

                        //Se il giocatore che sta eseguendo il turno non ha indovinato esegue:
                        if(indovinato==false)
                        {
                            tentativi[j]++; //Incrementa la variabile che conta i tentativi del giocatore j
                            printf("Sbagliato, la lettera '%c' non e' presente nella parola\n"
                                   "Utente id:%d, ti restano %d tentativi\n", lettera, partita.gruppiGioco[i][j], MAX_TENTATIVI-tentativi[j]);
                        }

                        conta_mancanti = 0; //Resetta la variabile che conta la lettere mancanti

                        //Ciclo che serve per stampare la tabella della parola
                        for (int k = 0; k < lunghezza_frase; ++k)
                        {
                            controllo_lettera = false; //resetta la variabile per controllare se stampare o meno '_'

                            //Assegno la lettera analizzata a una variabile d'appoggio per non modificare la frase originale in caso di conversione
                            lettera_analizzata = dizionario.frasi[fraseScelta][k];

                            //Se la lettera analizzata è maiuscola la converte in minuscola per rendere il programma case sensitive
                            if (lettera_analizzata >= 'A' && lettera_analizzata <= 'Z')
                            {
                                lettera_analizzata += CONVERSIONE_LETTERA; //Somma 32 (differenza tra A e a nella tabella ASCII) alla lettera scelta per trasformarla in minuscola
                            }

                            //Se la lettera analizzata è uno spazio esegue:
                            if (lettera_analizzata==' ')
                            {
                                printf(" ");
                            }
                            //Se la lettera analizzata è un punto esegue:
                            else if (lettera_analizzata=='.')
                            {
                                printf(".");
                            }
                            //Se la lettera analizzata è una virgola esegue:
                            else if (lettera_analizzata==',')
                            {
                                printf(",");
                            }
                            //Se la lettera analizzata è un punto e virgola esegue:
                            else if (lettera_analizzata==';')
                            {
                                printf(";");
                            }
                            //Se la lettera analizzata è un punto esclamativo esegue:
                            else if (lettera_analizzata=='!')
                            {
                                printf("!");
                            }
                            //Se la lettera analizzata è un punto di domanda esegue:
                            else if (lettera_analizzata=='?')
                            {
                                printf("?");
                            }
                            //Altrimenti esegue:
                            else
                            {
                                //Ciclo per stampare le lettere indovinate
                                for (int l = 0; l < LETTERE_ALFABETO; ++l)
                                {
                                    //Se la lettera analizzata è stata indovinata esegue:
                                    if (lettera_analizzata==lettere_usate[l])
                                    {
                                        printf("%c", dizionario.frasi[fraseScelta][k]); //Stampa la lettera di posizione k
                                        controllo_lettera = true; //Porta il controllo a true per  non far stampare '-'
                                        l = LETTERE_ALFABETO; //porta l allo stesso valore delle lettere dell'alfabeto per non fare rieseguire il ciclo
                                    }
                                }

                                //Se la lettera controllata non è ancora stata indovinata esegue:
                                if (controllo_lettera==false)
                                {
                                    printf("_");
                                    conta_mancanti++;
                                }
                            }
                        }
                        printf("\n\n");

                        //Se sono state indovinate tutte le lettere esegue:
                        if (conta_mancanti==VUOTO)
                        {
                            vincitore = partita.gruppiGioco[i][j]; //Setta il vincitore del gruppo il giocatore che sta eseguendo il turno
                            printf("Il giocatore %d ha indovinato\n", partita.gruppiGioco[i][j]);
                            fine_partita = true; //Setta la variabile fine partita a true per uscire dalla partita del gruppo i
                            j = partita.giocatori_per_gruppo; //porta j al valore dei giocatori per gruppo per uscire dal ciclo
                        }
                    }
                }

                //Ciclo per contare quanti utenti hanno ancora tentativi
                for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
                {
                    //Se i tentativi del giocatore j sono terminati esegue:
                    if (tentativi[j] >= MAX_TENTATIVI)
                    {
                        fine_tentativi++; //Aumenta la variabile fine tentativi per controllare quanti giocatori hanno terminato i tentativi
                    }
                }
            } while ((fine_partita == false) && (fine_tentativi < partita.giocatori_per_gruppo));
        }
        //Altrimenti esegue:
        else
        {
            //Genera randomicamente il vincitore
            vincitore = partita.gruppiGioco[i][rand()%partita.giocatori_per_gruppo];
        }

        //Ciclo per controllare se nel gruppo c'è il giocatore Riccardo Scateni
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Se è presente vince automaticamente
                    vincitore = Frontman_dello_SPR1D_GAME(vincitore, salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].nome, partita.gruppiGioco[i][j]);
                }
            }
        }

        //Ciclo per controllare quale giocatore del gruppo ha vinto
        for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
        {
            //Se il giocatore controllato è il vincitore esegue:
            if (vincitore==partita.gruppiGioco[i][j])
            {
                //Ciclo che controlla se il giocatore vincitore è controllato dall'utente
                for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
                {
                    //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                    if (partita.gruppiGioco[i][j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                    {
                        //Incrementa il numero di mini-giochi vinti del giocatore selezionato
                        salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_tot_minigiochi_vinti++;
                    }
                }

                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = true;
                printf("\nIl giocatore vincitore del gruppo %d e' il n.%d\n", i+1, partita.gruppiGioco[i][j]);
            }
            //Altrimenti esegue:
            else
            {
                salvataggio.giocatori_in_gioco[partita.gruppiGioco[i][j]] = false;
            }
        }
    }

    return salvataggio;
}

//Funzione er scegliere il dizionario utilizzato
Dizionario scegliDizionario ()
{
    //Dichiarazione variabili locali
    Dizionario dizionario; //Variabile in cui salvare i dati leggi dal dizionario
    char dizionarioSelezionato[DIM_NOME_FILE]; //stringa in cui salvare il dizionario scelto
    int risp;

    //Output della domanda
    printf("\nChe dizionario vuoi usare?\n"
           "1) Nuovo dizionario\n"
           "2) Dizionario default\n");
    //Richiesta input
    scanf("%d", &risp);
    while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

    //Ciclo per continuare a far inserire la risposta in caso in cui non sia una delle due richieste
    while (risp!=NUOVO_FILE && risp!=VECCHIO_FILE)
    {
        printf("\nATTENZIONE!\n"
               "Inserire uno dei due numeri richiesti\n");
        scanf("%d", &risp);
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio
    }

    //Se l'utente sceglie d'inserire un nuovo dizionario esegue:
    if (risp==NUOVO_FILE)
    {
        strcat(dizionarioSelezionato, CUSTOM_DICTIONARY); //La variabile dove salvare il dizionario selezionato prende il percorso custom

        //Riempio il dizionario appena creato
        riempiDizionario(dizionarioSelezionato);
    }
    //Se l'utente sceglie un vecchio dizionario esegue:
    if (risp==VECCHIO_FILE)
    {
        strcat(dizionarioSelezionato, DEFAULT_DICTIONARY); //La variabile dove salvare il dizionario selezionato prende il percorso default
    }

    //Richiamo la funzione per riempire l'array di frase da usare per l'impiccato
    dizionario = leggiDizionario (dizionarioSelezionato);

    return dizionario;
}

//Funzione per riempire il dizionario creato di frasi
void riempiDizionario (char dizionarioSelezionato[])
{
    //Dichiarazione variabili locali
    Dizionario dizionario;
    FILE *File_Dizionario=NULL; //variabile FILE che rappresenta il dizionario scelto
    char frase[LUNGHEZZA_FRASI], risp[DIM_SI_NO];
    bool controllo=false, controlloSI=false, controlloNO=false;

    dizionario.n_frasi = 0;

    do //Ciclo per continuare a chiedere se vuole inserire un altra frase/parola
    {
        do //Ciclo per continuare a chiedere la stringa in caso d'inserimento errato
        {
            //Output della domanda
            printf( "\n                            Scegli la parola o la frase n:%d\n"
                    "(MAX 119 caratteri, solo lettere non accentate, spazi e i seguenti caratteri \". , ; ! ?\")\n", dizionario.n_frasi+1);

            scanf(" %119[^\n]", frase); //Richiesta input
            while ((getchar()) != '\n');

            //Se la stringa è accettata restituisce true ed esce dal ciclo
            controllo = controlloFrase(frase);
        } while (controllo==false);

        //Copi nella posizione corrente la frase scritta dall'utente
        strcpy(dizionario.frasi[dizionario.n_frasi], frase);

        //Incremento la variabile che conta le frasi presenti
        dizionario.n_frasi++;

        do //Ciclo per continuare a far inserire la risposta in caso in cui non sia o si o no
        {
            //Ripristina le variabili di controllo
            controlloNO = false;
            controlloSI = false;

            //Output della domanda
            printf("\nVuoi inserire un'altra frase/parola? si/no :");

            scanf("%2s", risp); //Richiesta input
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
            }
            //Altrimenti esegue:
            else
            {
                printf("\nDevi inserire o si o no\n");
            }
        } while (controlloSI==false && controlloNO==false);
    } while (controlloSI==true);

    //Apro il dizionario dove l'utente vuole scrivere la frasi
    File_Dizionario = fopen(dizionarioSelezionato, "w");
    //Controllo che il file sia stato aperto correttamente
    if(File_Dizionario==NULL)
        exit(-1);

    //Scrivo sul file l'intero che rappresenta il numero delle frasi presenti
    fprintf(File_Dizionario, "%d\n", dizionario.n_frasi);

    //Ciclo per scrivere sul file ogni frase
    for (int i = 0; i < dizionario.n_frasi; ++i)
    {
        //Scrivo sul file la frase di posizione i
        fprintf(File_Dizionario, "%s\n", dizionario.frasi[i]);
    }

    //Chiude il file di testo aperto
    fclose(File_Dizionario);
}

//Funzione per controllare che non ci siano caratteri non consentiti
bool controlloFrase (char frase[])
{
    //Dichiarazione variabili locali
    int n_caratteri = strlen(frase); //Conta da quanti caratteri è composta la stringa passata

    //Esegue il ciclo per il numero di caratteri presenti nella stringa
    for (int i = 0; i < n_caratteri; ++i)
    {
        //Se la stringa contiene caratteri che non siano lettere (maiuscole o minuscole), spazi o i caratteri ". , ; ! ?" restituisce false
        if ((frase[i] < 'a' || frase[i] > 'z') && (frase[i] < 'A' || frase[i] > 'Z') && (frase[i] != ' ') && (frase[i] != '.') && (frase[i] != ',') && (frase[i] != ';') && (frase[i] != '!') && (frase[i] != '?'))
        {
            //Se la stringa inserita precedentemente non è accettata stampa un errore
            printf("La frase/parola inserita non è valida\n"
                   "Inserire nuovamente\n");
            return false;
        }
    }

    //Se la stringa è totalmente accettata restituisce true
    return true;
}

//Funzione per leggere i dati presenti all'interno di un file dizionario
Dizionario leggiDizionario (char dizionarioSelezionato[])
{
    //Dichiarazione variabili locali
    Dizionario dizionario;
    FILE *File_Dizionario=NULL; //variabile FILE che rappresenta il dizionario scelto

    //Apro il dizionario scelto dall'utente
    File_Dizionario = fopen(dizionarioSelezionato, "r");
    //Controllo che il file sia stato aperto correttamente
    if(File_Dizionario == NULL)
        exit(-1);

    /*Leggo la prima variabile del file,
     *la variabile letta è un intero, il cui risultato lo assegno alla variabile che conta il numero di frase*/
    fscanf(File_Dizionario, "%d", &dizionario.n_frasi);

    //Salvo tutte le frasi/parole presenti nel file
    for (int i = 0; i < dizionario.n_frasi; ++i)
    {
        fscanf(File_Dizionario, " %[^\n]s", dizionario.frasi[i]);
    }

    //Chiude il file di testo aperto
    fclose(File_Dizionario);

    return dizionario;
}

//Funzione fase finale BlackJack
bool BlackJack (Salvataggio salvataggio, Partita partita)
{
    //Dichiarazioni variabili locali
    Carta carteMano[GRANDEZZA_GRUPPI2][MAX_CARTE_MANO];
    char nomeSemi[N_SEMI][MAX_NOMI_SEMI]={"Cuori", "Quadri", "Picche", "Fiori"};
    char nomeFigura[N_CARTE][MAX_NOMI_FIGURE]={"ASSO", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"}, risp[DIM_SI_NO];
    int sommaCarte[GRANDEZZA_GRUPPI2]={0}, pos_carta=0, vincitore, semeScelto, figuraScelta, contaAssi=0, risp2;
    bool doppia=false, utente=false, continuo[GRANDEZZA_GRUPPI2]={true, true}, controllo=false, vittoria=false;

    partita.giocatori_per_gruppo = GRANDEZZA_GRUPPI2;

    //Stampa della descrizione del gioco
    printf("\n-----------------------> BlackJack <-----------------------\n"
                  "        II 2 giocatori si sfidano uno contro l'altro,\n"
                  " con l'obiettivo di avere in mano delle carte la cui somma\n"
                  "   sia il piu' possibile vicina a 21, ma senza superarlo.\n"
                  "---------------------> BUONA FORTUNA <---------------------\n");

    do //Ciclo per continuare a far continuare la partita finché un giocatore non vince
    {
        //Setta le carte che pescheranno i giocatori in questo turno con un numero che non può essere generato in modo da non dare problemi di doppie
        carteMano[GIOCATORE1][pos_carta].seme = N_SEMI;
        carteMano[GIOCATORE1][pos_carta].figura = N_CARTE;
        carteMano[GIOCATORE2][pos_carta].seme = N_SEMI;
        carteMano[GIOCATORE2][pos_carta].figura = N_CARTE;

        //Ciclo per eseguire il turno di entrambi i giocatori
        for (int i = 0; i < partita.giocatori_per_gruppo; ++i)
        {
            utente=false; //Resetta la variabile per controllare se il giocatore che sta eseguendo il turno è controllato dall'utente

            //Ciclo per controllare se il giocatore che sta eseguendo il turno è controllato dall'utente
            for (int j = 0; j < salvataggio.M_controlloUtente; ++j)
            {
                //Se il giocatore di posizione[i][j] è controllato dall'utente esegue:
                if (partita.arrayGiocatoriRimasti[i] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[j]].id)
                {
                    utente = true;
                }
            }

            //Se il giocatore che sta eseguendo il turno non si è ancora fermato esegue:
            if (continuo[i]==true)
            {
                do //Ciclo per continuare a generare una carta casuale in caso quella scelta sia già stata estratta
                {
                    doppia = false; //Resetta la variabile di controllo

                    semeScelto = rand() % N_SEMI; //Genera casualmente il seme della carta
                    figuraScelta = rand() % N_CARTE; //Genera casualmente la figura della carta

                    //Ciclo per controllare se la carta generata è gia presente tra quelle in mano ai giocatori
                    for (int k = 0; k <= i; ++k)
                    {
                        for (int l = 0; l <= pos_carta ; ++l)
                        {
                            //Se la carta generata è doppia esegue:
                            if ((semeScelto==carteMano[k][l].seme) && (figuraScelta==carteMano[k][l].figura))
                            {
                                doppia=true;
                            }
                        }
                    }
                } while (doppia==true);

                carteMano[i][pos_carta].seme = semeScelto; //Assegna il seme generato alla carta del giocatore
                carteMano[i][pos_carta].figura = figuraScelta; //Assegna il seme generato alla carta del giocatore

                //Se sono già state date 2 carte a entrambi i giocatori esegue:
                if (pos_carta > VUOTO)
                {
                    if (utente==true)
                    {
                        //Stampa le carte in mano al giocatore di pos i
                        printf("\nGiocatore n.%d le carte pescate sono:\n", partita.arrayGiocatoriRimasti[i]);
                        for (int j = 0; j <= pos_carta; ++j)
                        {
                            printf("Carta %d) %s di %s\n", j+1, nomeFigura[carteMano[i][j].figura], nomeSemi[carteMano[i][j].seme]);
                        }
                    }

                    //Resetta la variabile per controllare la somma delle carte in mano al giocatore di pos i
                    sommaCarte[i] = VUOTO;

                    //Ciclo per assegnare il valore alle carte in mano al giocatore (tranne l'asso)
                    for (int j = 0; j <= pos_carta; ++j)
                    {
                        //Switch che assegna a ogni carta il corrispondente valore
                        switch (carteMano[i][j].figura)
                        {
                            case ASSO:
                                contaAssi++; //Incrementa il valore di conta assi per capire quanti assi sono presenti nelle mani del giocatore
                                carteMano[i][j].valore = VUOTO; //Assegna il valore dell'asso a 0 per non compromettere la somma
                                break;
                            case DUE:
                                carteMano[i][j].valore = DUE+1;
                                break;

                            case TRE:
                                carteMano[i][j].valore = TRE+1;
                                break;

                            case QUATRO:
                                carteMano[i][j].valore = QUATRO+1;
                                break;

                            case CINQUE:
                                carteMano[i][j].valore = CINQUE+1;
                                break;

                            case SEI:
                                carteMano[i][j].valore = SEI+1;
                                break;

                            case SETTE:
                                carteMano[i][j].valore = SETTE+1;
                                break;

                            case OTTO:
                                carteMano[i][j].valore = OTTO+1;
                                break;

                            case NOVE:
                                carteMano[i][j].valore = NOVE+1;
                                break;

                            case DIECI:
                            case J:
                            case Q:
                            case K:
                                carteMano[i][j].valore = DIECI+1;
                                break;
                        }

                        //Somma tutti i valori delle carte in mano al giocatore (tranne l'asso) e assegna il valore alla variabile somma
                        sommaCarte[i]+=carteMano[i][j].valore;
                    }

                    //Ciclo per far decidere al giocatore il valore dell'asso
                    for (int j = 0; j <= pos_carta ; ++j)
                    {
                        //Se il giocatore in mano ha un asso esegue:
                        if (carteMano[i][j].figura==ASSO)
                        {
                            //Se il giocatore è controllato dall'utente esegue:
                            if (utente==true)
                            {
                                do //Ciclo per continuare far inserire il valore dell'asso in caso sia diverso da 1 o 11
                                {
                                    printf("\nQuanto vuoi far valere il tuo %s di %s? (1 o 11) :", nomeFigura[carteMano[i][j].figura], nomeSemi[carteMano[i][j].seme]);
                                    scanf("%d", &carteMano[i][j].valore);
                                    while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

                                    //Se il valore inserito è diverso da 1 o 11 esegue:
                                    if (carteMano[i][j].valore!=ASSO1 && carteMano[i][j].valore!=ASSO11)
                                    {
                                        printf("ATTENZIONE devi inserire 1 o 11\n");
                                    }
                                } while (carteMano[i][j].valore!=ASSO1 && carteMano[i][j].valore!=ASSO11);
                            }
                            //Se il giocatore è controllato dalla cpu esegue:
                            else
                            {
                                //Se portando il valore di un asso a 11 non sfora i 21 esegue:
                                if ((sommaCarte[i] <= DIECI+1 && contaAssi==1) || (sommaCarte[i] <= DIECI && contaAssi==2) || (sommaCarte[i] <= NOVE+1 && contaAssi==3) || (sommaCarte[i] <= NOVE && contaAssi==4))
                                {
                                    carteMano[i][j].valore = ASSO11; //Assegna all'asso il valore 11
                                }
                                //Altrimenti esegue:
                                else
                                {
                                    carteMano[i][j].valore = ASSO1; //Assegna all'asso il valore 1
                                }
                            }

                            //Somma AI valori delle carte in mano al giocatore (tranne l'asso), i valore degli assi che ha deciso il giocatore e assegna il valore alla variabile somma
                            sommaCarte[i]+=carteMano[i][j].valore;
                        }
                    }

                    if (utente==true)
                    {
                        printf("La somma delle carte e': %d", sommaCarte[i]);
                    }

                    //Se il giocatore che esegue il turno è controllato dell'utente esegue:
                    if (utente==true)
                    {
                        do //Ciclo per continuare a far inserire la risposta in caso in cui non sia o si o no
                        {
                            //Output della domanda
                            printf("\nVuoi fermarti? si/no :");
                            //Richiesta input
                            scanf("%2s", risp);
                            while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

                            //Se la risposta è uguale a no esegue:
                            if (strcmp(risp, "NO")==false || strcmp(risp, "No")==false || strcmp(risp, "nO")==false || strcmp(risp, "no")==false)
                            {
                                continuo[i] = true;
                                controllo = false;
                            }
                                //Se la risposta è uguale a si esegue:
                            else if (strcmp(risp, "SI")==false || strcmp(risp, "Si")==false || strcmp(risp, "sI")==false || strcmp(risp, "si")==false)
                            {
                                continuo[i] = false;
                                controllo = false;
                            }
                                //Altrimenti esegue:
                            else
                            {
                                printf("\nDevi inserire o si o no\n");
                                controllo = true;
                            }
                        } while (controllo==true);
                    }
                    //Se il giocatore che esegue il turno è controllato dalla cpu esegue:
                    else
                    {
                        //Se la somma delle carte super il rischio massimo esegue:
                        if (sommaCarte[i] > MAX_RISCHIO)
                        {
                            continuo[i] = false; //Il giocatore si ferma
                            printf("\nIl giocatore %d decide di fermarsi\n", partita.arrayGiocatoriRimasti[i]);
                        }
                        //Altrimenti esegue:
                        else
                        {
                            continuo[i] = true; //Il giocatore continua
                            printf("\nIl giocatore %d decide di continuare\n", partita.arrayGiocatoriRimasti[i]);
                        }
                    }
                }
            }
        }

        //Se entrambi i giocatori hanno deciso di fermasi esegue:
        if (continuo[GIOCATORE1]==false && continuo[GIOCATORE2]==false)
        {
            //Stampa le somme di entrambi i giocatori
            printf("\nLe somme dei 2 giocatori sono:\n"
                   "Giocatore n.%d: %d\n"
                   "Giocatore n.%d: %d\n", partita.arrayGiocatoriRimasti[GIOCATORE1], sommaCarte[GIOCATORE1], partita.arrayGiocatoriRimasti[GIOCATORE2], sommaCarte[GIOCATORE2]);
        }

        //Se entrambi i giocatori hanno superato il numero 21 allo stesso turno o se la somma dei giocatori è la stessa esegue:
        if ((sommaCarte[GIOCATORE1] > SOMMA_VITTORIA && sommaCarte[GIOCATORE2] > SOMMA_VITTORIA) || (sommaCarte[GIOCATORE1]==sommaCarte[GIOCATORE2] && pos_carta > VUOTO && continuo[GIOCATORE1]==false && continuo[GIOCATORE2]==false))
        {
            printf("\nLa partita e' finita in parita', si rincomincia\n");
            return true; //Ritorna false per far rieseguire il gioco da capo
        }
        //Se il giocatore 1 ha superato il numero 21 esgeue:
        else if (sommaCarte[GIOCATORE1] > SOMMA_VITTORIA)
        {
            vincitore = partita.arrayGiocatoriRimasti[GIOCATORE2]; //Vince il giocatore 2
            printf("\nHa vinto il giocatore %d\n", partita.arrayGiocatoriRimasti[GIOCATORE2]);
            vittoria = true;
        }
        //Se il giocatore 2 ha superato il numero 21 esgeue:
        else if (sommaCarte[GIOCATORE2] > SOMMA_VITTORIA)
        {
            vincitore = partita.arrayGiocatoriRimasti[GIOCATORE1]; //Vince il giocatore 2
            printf("\nHa vinto il giocatore %d\n", partita.arrayGiocatoriRimasti[GIOCATORE1]);
            vittoria = true;
        }
        //Se entrambi i giocatori hanno deciso di fermarsi esegue:
        else if (continuo[GIOCATORE1]==false && continuo[GIOCATORE2]==false)
        {
            //Se la somma delle carte del giocatore 1 è maggiore della somma del giocatore esegue:
            if (sommaCarte[GIOCATORE1] > sommaCarte[GIOCATORE2])
            {
                vincitore = partita.arrayGiocatoriRimasti[GIOCATORE1]; //Vince il giocatore 1
                printf("\nHa vinto il giocatore %d\n", partita.arrayGiocatoriRimasti[GIOCATORE1]);
                vittoria = true;
            }
            //Altrimenti esegue:
            else
            {
                vincitore = partita.arrayGiocatoriRimasti[GIOCATORE2]; //Vince il giocatore 2
                printf("\nHa vinto il giocatore %d\n", partita.arrayGiocatoriRimasti[GIOCATORE2]);
                vittoria = true;
            }
        }

        //Incrementa la variabile rappresentante il numero di turni eseguiti
        pos_carta++;
    } while (vittoria==false);

    //Ciclo per controllare se nel gruppo c'è il giocatore Riccardo Scateni
    for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
    {
        for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
        {
            //Se il giocatore rimanente di posizione[j] è controllato dall'utente esegue:
            if (partita.arrayGiocatoriRimasti[j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
            {
                //Se è presente vince automaticamente
                vincitore = Frontman_dello_SPR1D_GAME(vincitore, salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].nome, partita.arrayGiocatoriRimasti[j]);
            }
        }
    }

    //Ciclo per controllare quale giocatore del gruppo ha vinto
    for (int j = 0; j < partita.giocatori_per_gruppo; ++j)
    {
        //Se il giocatore controllato è il vincitore esegue:
        if (vincitore==partita.arrayGiocatoriRimasti[j])
        {
            //Ciclo che controlla se il giocatore vincitore è controllato dall'utente
            for (int k = 0; k < salvataggio.M_controlloUtente; ++k)
            {
                //Se il giocatore rimanente di posizione[j] è controllato dall'utente esegue:
                if (partita.arrayGiocatoriRimasti[j] == salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].id)
                {
                    //Incrementa il numero di SPR1D-GAME vinti del giocatore selezionato
                    salvataggio.arrayGiocatori[salvataggio.giocatoriUtente_partecipanti[k]].n_SPR1D_GAME_vinti++;
                }
            }

            salvataggio.giocatori_in_gioco[partita.arrayGiocatoriRimasti[j]] = true;
            printf("\nIl vincitore dell'SPR1D GAME e' il giocatore n.%d\n", partita.arrayGiocatoriRimasti[j]);
        }
        //Altrimenti esegue:
        else
        {
            salvataggio.giocatori_in_gioco[partita.arrayGiocatoriRimasti[j]] = false;
        }
    }

    //Output della domanda
    printf("\nCosa vuoi fare?\n"
           "2) Uscire senza salvare\n"
           "3) Uscire salvando la partita\n");
    //Richiesta input
    scanf("%d", &risp2);
    while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

    //Ciclo per continuare a far inserire la risposta in caso in cui non sia una delle due richieste
    while (risp2!=RISP_SALVARE && risp2!=RISP_USCITA)
    {
        printf("\nATTENZIONE!\n"
               "Inserire uno dei due numeri richiesti\n");
        scanf("%d", &risp2);
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio
    }

    //Se il giocatore vuole salvare esegue:
    if (risp2==RISP_SALVARE)
    {
        salvataggio.partita_in_corso=false; //Setta la variabile della partita in corso a 0 perché è terminata la partita
        salva(salvataggio); //Salva la partita

        //Ritorna false per non far rieseguire il gioco
        return false;
    }
    //Se il giocatore vuole uscire esegue:
    else
    {
        //Ritorna false per non far rieseguire il gioco
        return false;
    }
}