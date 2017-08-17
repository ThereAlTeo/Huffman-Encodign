#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lib1617.h"

#define CLEAR system("cls")

/**
	Funzione che interrompe temporaneamente l'esecuzione del programma
	Per rendere la funzione riutilizzabile, durante la chiamata, deve essere specificato il tempo di interruzione.
*/
void stop(int val)
{ 
	_sleep(val);
}

/**
	Allo scopo di rendere piu' leggibile in codice, si scrive l'operazione una sola volta.
	Essa viene utilizzata varie volte e viene eseguita SOLAMENTE quando l'utente nel momento di una specifica
	scelta effettua un'operazione non prevista o indesiderata. E' seguita da una seconda scelta da parte dell'utente.
*/
void warning(char valore[])
{
	int i;
	CLEAR;
	printf("\n%s", valore);

	for (i = 0; i < 3; i++)
	{
		stop(750);
		printf(". ");
	}

	printf("\n");
}

/**
	Funzione finale.
	Consente all'utente di leggere con piu' calma l'output.
*/
void endMethod()
{
	printf("\n\n\nPremi un tasto per continuare ...");
	getchar();
}

/**
	Funzione eseguita quando si vogliono effettuare domande all'utente per comprendere quale comportamento deve avere il programma
*/
bool checkRequest(char valore[])
{
	char valMenuRet;
	bool check = false;

	CLEAR;

	do
	{
		if (check == true)
			warning("WARNING: Carattere non valido. Si prega di inserirlo correttamente. ");

		printf("\n\n%s?? (S/N)\n -->  ", valore);
		valMenuRet = getchar();
		fflush(stdin);

		check = true;
	} while ((valMenuRet != 'S' && valMenuRet != 's') && (valMenuRet != 'N' && valMenuRet != 'n'));

	if (valMenuRet == 'S' || valMenuRet == 's')
		return true;
	else
		return false;
}

/**

*/
int menuIniziale()
{
	int scelta = 0;
	bool check = false;

	do
	{
		CLEAR;
		if (check == true)
			warning("WARNING: Valore non valido. Si prega di inserirlo correttamente. ");

		printf("\n\t\tMENU'\n  1) Visualizzare le parole contenute nel dizionario.\n  2) Visualizzare il numero di parole contenute nel dizionario.\n  3) Inserisci nuova parola nel dizionario.\n  ");
		printf("4) Cancella parola dal dizionario.\n  5) Visualizzare la parola -iesima.\n  6) Inserisci definizione relativa ad una parola.\n  ");
		printf("7) Visualizza definizione relativa ad una parola.\n  8) Salvataggio su file del dizionario (CLASSICO).\n  9) Salvataggio su file del dizionario (CODIFICA DI HUFFMAN).\n  10) Visualizzare risultati della ricerca avanzata.\n 11) USCIRE.\n\n--> ");
		scanf("%3d", &scelta);
		fflush(stdin);

		check = true;
	} while (scelta < 1 || scelta > 11);

	return scelta;
}

/**

*/
void primaryFunction(NODO* dictionary)
{
	char* stringTemp;
	srand(time(NULL));

	dictionary = createFromFile("fileTest1617.txt");

	printf("\nSTAMPA DEL DIZIONARIO:\n");
	printDictionary(dictionary);

	printf("\nNumero di parole salvate nel dizionario : %d\n\n", countWord(dictionary));

	insertWord(&dictionary, "tavolo");
	insertWord(&dictionary, "b");
	insertWord(&dictionary, "zoo");

	printf("\nNumero di parole salvate nel dizionario : %d\n\n", countWord(dictionary));

	printf("\nSTAMPA DEL DIZIONARIO dopo 3 inserimenti:\n");
	printDictionary(dictionary);

	cancWord(&dictionary, getWordAt(dictionary, 5));
	cancWord(&dictionary, getWordAt(dictionary, 1));
	cancWord(&dictionary, getWordAt(dictionary, 0));
	printf("\nSTAMPA DEL DIZIONARIO dopo 3 cancellazioni:\n");
	printDictionary(dictionary);

	insertDef(dictionary, getWordAt(dictionary, 2), "una definizione");
	insertDef(dictionary, getWordAt(dictionary, 4), "altra definizione");
	printf("\nSTAMPA DEL DIZIONARIO dopo inserimento definizioni:\n");
	printDictionary(dictionary);
	printf("\nNumero di parole salvate nel dizionario : %d\n\n", countWord(dictionary));

	printf("\nRicerca Parola \"%s\" -> definizione : [%s]\n\n", getWordAt(dictionary, 2), searchDef(dictionary, getWordAt(dictionary, 2)));
	printf("\nRicerca Parola \"%s\" -> definizione : [%s]\n\n", getWordAt(dictionary, 7), searchDef(dictionary, getWordAt(dictionary, 7)));
	stringTemp = "eftd";
	printf("\nRicerca Parola \"%s\" -> definizione : [%s]\n\n", stringTemp, searchDef(dictionary, stringTemp));

	endMethod();
}

/**

*/
void getImportDictionary(NODO* dictionary)
{

}

/**

*/
void run()
{
	NODO* dictionary = NULL;
	huffmanNODO *tree = NULL;
	bool checkExit = false;

	warning("\t\tWELCOME ");

	if (checkRequest("Iniziare l'esecuzione del programma partendo dalle SOLE funzionalità base") == true)
		primaryFunction(dictionary);
	else if(checkRequest("Importare parole e/o definizioni da file") == true)
		getImportDictionary(dictionary);

	if (checkRequest("Proseguire eseguendo tutte le funzioni implementate") == true)
	{
		do
		{
			switch (menuIniziale())
			{
				case 1: 
					endMethod(); break;
				case 2:
					endMethod(); break;
				case 3:
					endMethod(); break;
				case 4:
					endMethod(); break;
				case 5:
					endMethod(); break;
				case 6:
					endMethod(); break;
				case 7:
					endMethod(); break;
				case 8:
					endMethod(); break;
				case 9:
					endMethod(); break;
				case 10:
					endMethod(); break;
				case 11: checkExit = true;
					break;
			}

			CLEAR;
		} while(!checkExit);
	}

	warning("\t\tARRIVEDERCI ");
}

int main()
{
	run();	
	endMethod();

	return 0;
}

