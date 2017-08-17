#include <stdbool.h>
#include <stdio.h>

#include "management.h"

/**
Funzione che interrompe temporaneamente l'esecuzione del programma
Per rendere la funzione riutilizzabile, durante la chiamata, deve essere specificato il tempo di interruzione.
*/
void stop(int val) {
	_sleep(val);
}

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

void endMethod()
{
	printf("\n\n\nPremi un tasto per continuare ...");
	getchar();
}

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

char* returnWord(char valore[])
{
	int ch;

	printf("\n\n%s: ", valore);
	do {
		ch = getchar();
		if (j < MAX_CHAR_NOME_COGN)
			arrayGestioneStudenti[index].nome[j++] = ch;
	} while (ch != '\n');
	arrayGestioneStudenti[index].nome[j] = '\0';
	fflush(stdin);
}

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
