#include "Salvataggi.h"

//Funzione per salvare la partita
void salva (Salvataggio salvataggio)
{
    //Dichiarazione variabili locali
    char **nomiSave=NULL; //array di stringhe in cui si memorizzeranno i nomi letti dal file
    int contaSave; //variabile int in cui salvare il numero dei file di salvataggio presenti
    char salvataggioSelezionato[DIM_NOME_FILE]; //stringa in cui salvare il file scelto
    int risp;

    //Richiamo la funzione per leggere il nome dei file di salvataggio presenti e riempio l array di stringhe con i nomi dei file di salvataggio presenti
    nomiSave = leggiFileSalvataggi(nomiSave, &contaSave);

    //Se non vengono trovati dei file di salvataggio esegue:
    if (contaSave==VUOTO)
    {
        risp = NUOVO_FILE; //Aggiorna la variabile risp per far inserire un nuovo salvataggio
    }
    //Altrimenti esegue:
    else
    {
        //Output della domanda
        printf("\nDove vuoi salvare?\n"
               "1) Nuovo file di salvataggio\n"
               "2) Vecchio file di salvataggio\n");
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
    }

    //Se l'utente sceglie d'inserire un nuovo salvataggio esegue:
    if (risp==NUOVO_FILE)
    {
        //Richiamo la funzione per inserire il nome del salvataggio
        inserisciSalvataggio(nomiSave, &contaSave, salvataggioSelezionato);
        strcat(salvataggioSelezionato, ".bin"); //Aggiungo al nome scelto l'estensione .bin
    }
    //Se l'utente sceglie di sovrascrivere un vecchio salvataggio esegue:
    if (risp==VECCHIO_FILE)
    {
        //Richiamo la funzione per far scegliere il salvataggio
        selezionaSalvataggio(nomiSave, contaSave, salvataggioSelezionato);
        strcat(salvataggioSelezionato, ".bin"); //Aggiungo al nome scelto l'estensione .bin
    }

    //Richiamo la funzione per salvare i dati nel file di salvataggio selezionato
    salvaDati(salvataggioSelezionato,salvataggio);

    //Rilascia la memoria allocata dinamicamente per la variabile nomiSave
    free(nomiSave);
}

//Funzione per leggere il nome dei file di salvataggio presenti
char** leggiFileSalvataggi (char **nomiSave, int *contaSave)
{
    //Dichiarazione variabili locali
    FILE *File_nomiSave=NULL; //variabile FILE dove sono presenti i nomi dei salvataggi presenti

    //Apro il file dove sono presenti i nomi di tutti i salvataggi in modalità di lettura
    File_nomiSave = fopen(INDIRIZZO_FILE_SALVATAGGI, "r");
    //Controllo che il file sia stato aperto correttamente
    if(File_nomiSave == NULL)
        exit(-1);

    /*Leggo la prima variabile del file,
     *la variabile letta è un intero, il cui risultato lo assegno alla variabile contaSave*/
    fscanf(File_nomiSave, "%d", contaSave);

    //Alloco dinamicamente lo spazio necessario per salvare tutti i nomi dei file nell array di vettori nomiSave
    nomiSave = (char**) malloc(*contaSave*sizeof(char*));
    //Controllo se la memoria per il puntatore è stata allocata correttamente
    if( nomiSave == NULL )
        exit(-1);

    //Ciclo per allocare dinamicamente lo spazio necessario per contenere le stringa
    for(int i=0; i< *contaSave; i++)
    {
        nomiSave[i] = (char*) malloc(DIM_NOME_FILE*sizeof(char));
        //Controllo se la memoria per il puntatore è stata allocata correttamente
        if( nomiSave[i] == NULL )
            exit(-1);
    }

    //Salvo tutti i nomi presenti nel file nell array di stringhe nomiSave
    for (int i = 0; i < *contaSave; ++i)
    {
        fscanf(File_nomiSave, " %s", nomiSave[i]);
    }

    //Chiude il file aperto
    fclose(File_nomiSave);

    //Ritorna l'indirizzo dell array di stringhe
    return nomiSave;
}

//Funzione per inserire il nome del salvataggio
void inserisciSalvataggio (char **nomiSave, int *contaSave, char *salvataggioSelezionato)
{
    //Dichiarazione variabili locali
    FILE *File_nomiSave=NULL; //variabile FILE dove sono presenti i nomi dei salvataggi presenti
    char nomeNewFile[DIM_NOME_FILE]; //stringa in cui scrivere il nome del salvataggio da inserire
    bool controllo=false;

    //Apro il file dove sono presenti i nomi di tutti i salvataggi in modalità di scrittura
    File_nomiSave = fopen(INDIRIZZO_FILE_SALVATAGGI, "w");
    //Controllo che il file sia stato aperto correttamente
    if(File_nomiSave==NULL)
        exit(-1);

    do //Ciclo per continuare a far inserire il nome in caso sia già stato usato per un altro salvataggio
    {
        controllo = false; //Resetta la variabile di controllo

        //Output della domanda
        printf("\nCome vuoi chiamare il tuo file di salvataggio?\n"
               "       (no spazzi, MAX 30 caratteri)\n");
        //Richiesta input
        scanf("%30s", nomeNewFile);
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        /*Ciclo che si esegue un numero di volte pari al numero di file di salvataggio presenti,
          per controllare che il nuovo nome inserito non sia già presente*/
        for (int i = 0; i < *contaSave; ++i)
        {
            //Se il nome appena inserito è già presente nel file esegue:
            if (strcmp(nomeNewFile, nomiSave[i])==false)
            {
                controllo = true; //Aggiorna la variabile di controllo a true per far ripetere il ciclo
            }
        }

        //Se la variabile di controllo è settata su true esegue:
        if (controllo==true)
        {
            //Stampa un messaggio di errore
            printf("\nATTENZIONE il nome e' gia presente tra i file di salvataggio\n");
        }
    } while (controllo==true);

    //Incrementa il valore di contaSave per contare anche il file appena aggiunto
    (*contaSave)++;

    //Rialloco all array di stringhe la quantità di memoria necessaria per poter contenere il nome del nuovo file
    nomiSave = (char**) realloc(nomiSave,sizeof(char*)*(*contaSave));
    //Controllo se la memoria per il puntatore è stata allocata correttamente
    if( nomiSave == NULL )
        exit(-1);

    //Alloco all array di stringhe di posizione *contaSave-1 la quantità di memoria necessaria per poter contenere il nome del nuovo file
    nomiSave[*contaSave-1] = (char*) malloc(sizeof(char)*DIM_NOME_FILE);
    //Controllo se la memoria per il puntatore è stata allocata correttamente
    if( nomiSave[*contaSave-1] == NULL )
        exit(-1);

    //Copio il nome del file inserito dall'utente all'interno della porzione di memoria appena allocata (nuova posizione dell array)
    strcpy(nomiSave[*contaSave-1], nomeNewFile);

    //Scrivo nel file l'intero contaSave come prima cosa
    fprintf(File_nomiSave, "%d\n", *contaSave);
    //Scrivo nel file tutti i nomi dei file già presenti piu quello inserito dall'utente
    for (int i = 0; i < *contaSave; ++i)
    {
        fprintf(File_nomiSave, "%s\n", nomiSave[i]);
    }

    //Chiude il file aperto
    fclose(File_nomiSave);

    //Copio il nome del file inserito dall'utente all'interno della stringa che mi serve per passare esso alla funzione di salvataggio
    strcpy(salvataggioSelezionato, nomeNewFile);
}

//Funzione per stampare i nomi dei file di salvataggio presenti
void stampaFileSalvataggi ()
{
    //Dichiarazione variabili locali
    FILE *File_nomiSave=NULL; //variabile FILE dove sono presenti i nomi dei salvataggi presenti
    char **nomiSave=NULL; //array di stringhe in cui si memorizzeranno i nomi letti dal file
    int contaSave; //variabile int in cui salvare il numero dei file di salvataggio presenti

    //Apro il file dove sono presenti i nomi di tutti i salvataggi in modalità di lettura
    File_nomiSave = fopen(INDIRIZZO_FILE_SALVATAGGI, "r");
    //Controllo che il file sia stato aperto correttamente
    if(File_nomiSave == NULL)
        exit(-1);

    /*Leggo la prima variabile del file,
     *la variabile letta è un intero, il cui risultato lo assegno alla variabile contaSave*/
    fscanf(File_nomiSave, "%d", &contaSave);

    //Alloco dinamicamente lo spazio necessario per salvare tutti i nomi dei file nell array di vettori nomiSave
    nomiSave = (char**) malloc(contaSave*sizeof(char*));
    //Controllo se la memoria per il puntatore è stata allocata correttamente
    if( nomiSave == NULL )
        exit(-1);

    //Ciclo per allocare i caratteri necessari alla stringa
    for(int i=0; i< contaSave; i++)
    {
        //Alloco all array di stringhe di posizione i la quantità di memoria necessaria per poter contenere il nome del file
        nomiSave[i] = (char*) malloc(DIM_NOME_FILE*sizeof(char));
        //Controllo se la memoria per il puntatore è stata allocata correttamente
        if( nomiSave[i] == NULL )
            exit(-1);
    }

    //Salvo tutti i nomi presenti nel file nell array di stringhe nomiSave
    for (int i = 0; i < contaSave; ++i)
    {
        fscanf(File_nomiSave, "%s", nomiSave[i]);
        printf("%s\n", nomiSave[i]); //Stampo ogni nome salvato
    }

    //Rilascia la memoria allocata dinamicamente per la variabile nomiSave
    free(nomiSave);

    //Chiude il file aperto
    fclose(File_nomiSave);
}

//Funzione per far scegliere il salvataggio
void selezionaSalvataggio (char **nomiSave, int contaSave, char *salvataggioSelezionato)
{
    //Dichiarazione variabili locali
    char nomeSaveSovrascrivere[DIM_NOME_FILE]; //stringa in cui scrivere il nome del salvataggio da sovrascrivere
    bool controllo=false;

    printf("\nQuale salvataggio vuoi usare?\n");
    //Richiamo la funzione per stampare i nomi dei file di salvataggio presenti
    stampaFileSalvataggi();

    do //Ciclo per continuare a far inserire il nome del salvataggio in caso quello inserito non esista
    {
        //Output della domanda
        printf("\nNome Salvataggio:");
        //Richiesta input
        scanf("%30s", nomeSaveSovrascrivere);
        while ((getchar()) != '\n'); //Ciclo di getchar per eliminare dalla console tutte le lettere scritte dall'utente fino all'invio

        /*Ciclo che si esegue un numero di volte pari al numero di file di salvataggio presenti,
          per controllare se il nome inserito è presente tra i salvataggi*/
        for (int i = 0; i < contaSave; ++i)
        {
            //Se il nome appena inserito è già presente nel file esegue:
            if (strcmp(nomeSaveSovrascrivere, nomiSave[i])==false)
            {
                controllo = true; //Aggiorna la variabile di controllo a true per non far ripetere il ciclo
            }
        }

        //Se la variabile di controllo è settata su false esegue:
        if (controllo==false)
        {
            //Stampa un messaggio di errore
            printf("\nATTENZIONE il nome non e' presente tra i file di salvataggio\n");
        }
    } while (controllo==false);

    //Copio il nome del file selezionato dall'utente, all'interno della stringa che mi serve per passare esso alla funzione di salvataggio
    strcpy(salvataggioSelezionato, nomeSaveSovrascrivere);
}

//Funzione per salvare i dati nel file di salvataggio selezionato
void salvaDati (char *salvataggioSelezionato, Salvataggio salvataggio)
{
    FILE *File_Salvataggio=NULL; //variabile FILE che rappresenta il file dove l'utente vuole salvare i dati
    char Destinazione[DIM_NOME_FILE]; //stringa in cui salvare il percorso del file in cui salvare il salvataggio

    strcpy(Destinazione, "Salvataggi/"); //Inserisco nella stringa di destinazione il percorso del file
    strcat(Destinazione, salvataggioSelezionato); //Aggiungo alla stringa di destinazione il nome del file selezionato

    //Apro il file dove l'utente vuole salvare in modalità di scrittura
    File_Salvataggio = fopen(Destinazione, "wb");
    //Controllo che il file sia stato aperto correttamente
    if(File_Salvataggio==NULL)
        exit(-1);

    //Scrive sul file il numero dei giocatori creati presenti
    fwrite(&salvataggio.K_giocatoriCreati, sizeof(int), QUANTITA, File_Salvataggio);

    //Ciclo per scrivere sul file tutti i giocatori creati
    for (int i = 0; i < salvataggio.K_giocatoriCreati; ++i)
    {
        //Scrive sul file il giocatore di posizione i
        fwrite(&salvataggio.arrayGiocatori[i], sizeof(Giocatore), QUANTITA, File_Salvataggio);
    }

    //Scrive sul file l'intero che controlla se la partita è in corso
    fwrite(&salvataggio.partita_in_corso, sizeof(int), QUANTITA, File_Salvataggio);

    //Se la partita è in corso esegue:
    if (salvataggio.partita_in_corso!=VUOTO)
    {
        //Scrive sul file il numero dei partecipanti
        fwrite(&salvataggio.N_partecipanti, sizeof(int), QUANTITA, File_Salvataggio);

        //Scrive sul file il numero dei giocatori utente partecipanti alla partita in corso
        fwrite(&salvataggio.M_controlloUtente, sizeof(int), QUANTITA, File_Salvataggio);

        //Ciclo per scrivere sul file tutti i giocatori utente che stanno partecipando alla partita
        for (int i = 0; i < salvataggio.M_controlloUtente; ++i)
        {
            //Scrive sul file il giocatore di posizione i
            fwrite(&salvataggio.giocatoriUtente_partecipanti[i], sizeof(int), QUANTITA, File_Salvataggio);
        }

        //Ciclo per scrivere sul file se un giocatore è in gioco oppure eliminato
        for (int i = 0; i < salvataggio.N_partecipanti; ++i)
        {
            //Scrive sul file se il giocatore di posizione i è eliminato o no
            fwrite(&salvataggio.giocatori_in_gioco[i], sizeof(int), QUANTITA, File_Salvataggio);
        }
    }

    printf("\nDATI SALVATI\n");

    //Chiude il file binario aperto
    fclose(File_Salvataggio);
}

//Funzione per caricare i file di salvataggio
Salvataggio caricaSalvataggio (Salvataggio salvataggio)
{
    FILE *File_Salvataggio= NULL;
    char **nomiSave=NULL; //array di stringhe in cui si memorizzeranno i nomi letti dal file
    int contaSave; //variabile int in cui salvare il numero dei file di salvataggio presenti
    char salvataggioSelezionato[DIM_NOME_FILE]; //stringa in cui salvare il file scelto
    char scelta[DIM_NOME_FILE]; //stringa in cui salvare il percorso del file da caricare

    //Richiamo la funzione per leggere il nome dei file di salvataggio presenti e riempio l array di stringhe con i nomi dei file di salvataggio presenti
    nomiSave = leggiFileSalvataggi(nomiSave, &contaSave);

    //Richiamo la funzione per far scegliere il salvataggio
    selezionaSalvataggio(nomiSave, contaSave, salvataggioSelezionato);
    strcat(salvataggioSelezionato, ".bin"); //Aggiungo al nome scelto l'estensione .bin

    strcpy(scelta, "Salvataggi/"); //Inserisco nella stringa di scelta il percorso del file
    strcat(scelta, salvataggioSelezionato); //Aggiungo alla stringa di scelta il nome del file selezionato

    //Apro il file dove l'utente vuole salvare in modalità di lettura
    File_Salvataggio = fopen( scelta, "rb" );
    //Controllo che il file sia stato aperto correttamente
    if(File_Salvataggio== NULL)
        exit(-1);

    //Leggo dal file il numero dei giocatori creati presenti e assegna il numero alla variabile k giocatori creati
    fread(&salvataggio.K_giocatoriCreati, sizeof(int), QUANTITA, File_Salvataggio);

    //Alloca la memoria ad array giocatori per poter contenere tutti i giocatori presenti nel file
    salvataggio.arrayGiocatori = (Giocatore*) malloc(sizeof(Giocatore)*salvataggio.K_giocatoriCreati);
    //Controllo se la memoria per il puntatore è stata allocata correttamente
    if( salvataggio.arrayGiocatori == NULL )
        exit(-1);

    //Ciclo per leggere dal file tutti i giocatori creati
    for (int i = 0; i < salvataggio.K_giocatoriCreati; ++i)
    {
        //Legge dal file il giocatore di posizione i e lo assegna alla posizione i dell'array dei giocatori
        fread(&salvataggio.arrayGiocatori[i], sizeof(Giocatore), QUANTITA, File_Salvataggio);
    }

    //Legge dal file l'intero che controlla se la partita è in corso
    fread(&salvataggio.partita_in_corso, sizeof(int), QUANTITA, File_Salvataggio);

    //Se la partita è in corso esegue:
    if (salvataggio.partita_in_corso!=VUOTO)
    {
        //Legge dal file il numero dei partecipanti
        fread(&salvataggio.N_partecipanti, sizeof(int), QUANTITA, File_Salvataggio);

        //Legge dal file il numero dei giocatori utente partecipanti alla partita in corso
        fread(&salvataggio.M_controlloUtente, sizeof(int), QUANTITA, File_Salvataggio);

        //Alloca la memoria all array contenente gli indici dei giocatori utenti partecipanti per poter contenere tutti quelli presenti nel file
        salvataggio.giocatoriUtente_partecipanti = (int*) malloc(sizeof(int)*salvataggio.M_controlloUtente);
        //Controllo se la memoria per il puntatore è stata allocata correttamente
        if( salvataggio.giocatoriUtente_partecipanti == NULL )
            exit(-1);

        //Ciclo per leggere dal file tutti i giocatori utente che stanno partecipando alla partita
        for (int i = 0; i < salvataggio.M_controlloUtente; ++i)
        {
            //Legge dal file l'indice del giocatore di posizione i e lo assegna alla posizione i dell'array dei giocatori utente partecipanti
            fread(&salvataggio.giocatoriUtente_partecipanti[i], sizeof(int), QUANTITA, File_Salvataggio);
        }

        //Alloca la memoria all array contenente i giocatori in gioco per poter contenere tutti quelli presenti nel file
        salvataggio.giocatori_in_gioco = (int*) malloc(sizeof(int)*salvataggio.N_partecipanti);
        //Controllo se la memoria per il puntatore è stata allocata correttamente
        if( salvataggio.giocatori_in_gioco == NULL )
            exit(-1);

        //Ciclo per leggere dal file se un giocatore è in gioco oppure eliminato
        for (int i = 0; i < salvataggio.N_partecipanti; ++i)
        {
            //Lagge dal file se il giocatore di posizione i è eliminato o no
            fread(&salvataggio.giocatori_in_gioco[i], sizeof(int), QUANTITA, File_Salvataggio);
        }
    }

    fclose(File_Salvataggio);

    //Rilascia la memoria allocata dinamicamente per la variabile nomiSave
    free(nomiSave);

    return salvataggio;
}