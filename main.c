//Programma che prende una lista di studenti dal file "studenti.txt" e li ordina per matricola

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //serve per strdup in newStudente();
#define nome_file "studenti.txt"
#define N 256 //la massima size che può avere una riga di file
#define M 20

typedef struct
{
	char *nome;
	char *cognome;
	int matricola;
} Studente;

Studente newStudente(char *, char *, int);
void printStudenti(Studente *, int);
void swap(Studente *, Studente *);
void bubbleSort(Studente *, int);

int main(void)
{
	FILE *fp;

	//righe di controllo standard per l'apertura dei file
	if((fp = fopen(nome_file, "r")) == NULL){ //se l'apertura del file in lettura non riesce (NULL)
		fprintf(stderr, "Impossibile aprire il file %s\n", nome_file); //stampa un messaggio di errore su standard error(output)
		exit(EXIT_FAILURE); //e poi chiude il programma
	}

	Studente *s = calloc(30, sizeof(Studente)); //dichiaro un array di studenti da 30 posti max
	char line[N+1], nome[M+1], cognome[M+1];
	//stringhe che servono per salvare i parametri dal file, il +1 serve per "\0" (carattere terminatore) nel peggiore dei casi
	int matricola, i = 0;

	for(i = 0; fgets(line, sizeof line, fp) != NULL; i++){
	//fgets assegna riga per riga del file alla stringa line, continua fino alla fine (!= NULL)
		sscanf(line, "%s %[^,], %d", nome, cognome, &matricola);
		//%s prende le stringhe e si ferma allo spazio, %[^,] prende tutto ciò che non è (^ tra le parentesi) una virgola
		*(s + i) = newStudente(nome, cognome, matricola); //crea uno studente con questi parametri e lo mette nell'array
	}
	i--; //decrementa la i, aumentata inutilmente all'ultima iterazione del ciclo (ci serve come dimensione dell'array)

	s = realloc(s, i * sizeof(Studente)); //adatta la dimensione dell'array alla sua dimensione effettiva (i)

	bubbleSort(s, i); //ordina l'array per matricola
	printStudenti(s, i); //stampa l'intero array di studenti

	fclose(fp); //chiude il file

	return 0;
}

Studente newStudente(char *nome, char *cognome, int matricola) //crea un nuovo elemento del tipo "Studente" con i tre parametri
{
	//prende in input nome, cognome e matricola dal file "studenti.txt"
	Studente s;

	s.nome = strdup(nome); //duplica la stringa in input e la salva nella variabile di s
	s.cognome = strdup(cognome);
	s.matricola = matricola;

	return s;
}

void printStudenti(Studente *s, int n) //stampa tutto l'array di studenti, prende in input l'array stesso (s) e la sua dimensione n;
{
	//l'array viene passato come puntatore, quindi per accedere alle celle si usa l'aritmetica dei puntatori, es: s+i (= s[i])
	int i;

	for(i = 0; i < n; i++)
		printf("%d - %s %s\n", (s+i)->matricola, (s+i)->cognome, (s+i)->nome); //stampa cella per cella
}

void swap(Studente *a, Studente *b) //inverte il contenuto di due celle
{
	 Studente temp; //si dichiara una variabile d'appoggio e lo si usa per lo scambio
	 temp = *a;
	 *a = *b;
	 *b = temp;
}

void bubbleSort(Studente *s, int n) //algoritmo di ordinamento standard, adattato per la struct Studente
{
	int i, j;

	for(i = 1; i < n; i++)
		for( j = 0; j < n - i; j++)
			if((s+j)->matricola > (s+j+1)->matricola) //anche qui uso l'aritmetica dei puntatori
				swap(s+j, s+j+1);
}
