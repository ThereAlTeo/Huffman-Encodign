#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lib1617.h"
#include "management.h"

/**

*/
void getDecompressHuffman(NODO** dictionary, huffmanNODO** tree)
{
	*dictionary = (NODO*) malloc(NUM_ELEMENTI * sizeof(NODO));

	inizializzazioneTabellaHash(*dictionary);

	(decompressHuffman(*dictionary, returnWord("Digitare l'indirizzo del file"), *tree) == UNDEFINED) ? PRNT_ERROR : PRNT_NOT_ERROR;
}

/**

*/
void getImportDictionary(NODO** dictionary, huffmanNODO** tree)
{
	int scelta = 0;
	bool check = false;

	do
	{
		CLEAR;
		if(check == true)
			warning("WARNING: Valore non valido. Si prega di inserirlo correttamente. ");

		printf("\n  1) Utilizzare la funzione importDictionary .\n  2) Utilizzare la codifca di HUFFMAN.\n\n--> ");
		scanf("%3d", &scelta);
		FREE_BUFFER;

		check = true;
	} while (scelta < 1 || scelta > 2);

	if (scelta == 1)
		*dictionary = importDictionary(returnWord("Digitare l'indirizzo del file"));
	else
		getDecompressHuffman(dictionary, tree);
}

/*

*/
void primaryFunction(NODO** aux)
{
	char* stringTemp;
	NODO* dictionary = createFromFile("fileTest1617.txt");
	*aux = dictionary;

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
int run()
{
	NODO* dictionary = NULL;
	huffmanNODO *tree = buildHuffmanTree();
	bool checkExit = false;
	char* codetable[NUM_ELEMENTI], *code = (char*)malloc(sizeof(char));
	int Level = 0;

	createTable(tree, codetable, code, Level);

	warning("\t\tWELCOME ");

	if (checkRequest("Iniziare l'esecuzione del programma partendo dalle SOLE funzionalita' base") == true)
		primaryFunction(&dictionary);
	else if(checkRequest("Importare parole e relative definizioni da file") == true)
		getImportDictionary(&dictionary, &tree);

	if(dictionary == NULL)
	{
		dictionary = (NODO*)malloc(NUM_ELEMENTI * sizeof(NODO));

		if(inizializzazioneTabellaHash(dictionary) == ERROR_FIND) return ERROR_FIND;
	}

	if (checkRequest("Proseguire eseguendo tutte le funzioni implementate") == true)
	{
		do
		{
			switch (menuIniziale())
			{
				case 1: printDictionary(dictionary);
					endMethod(); break;
				case 2: printf("\n\nIl numero di parole contenute nel dizionario e': %d\n\n", countWord(dictionary));
					endMethod(); break;
				case 3: (insertWord(&dictionary, returnWord("Digitare la parola da inserire")) == NOT_ERROR) ? PRNT_NOT_ERROR : PRNT_ERROR;
					endMethod(); break;
				case 4: (cancWord(&dictionary, returnWord("Digitare la parola da cancellare")) == NOT_ERROR) ? PRNT_NOT_ERROR : PRNT_ERROR;
					endMethod(); break;
				case 5: {
					unsigned int index;
					char* word;

					printf("Inserire l'index della parola da ricercare: ");
					scanf("%d", &index);

					word = getWordAt(dictionary, index);

					if (word != NULL)
						printf("\n\nLa parola all'index %d e': %s !! \n\n", index, word);
					else
						printf("\n\nL'index selezionato non presenta parole !! \n\n");

					endMethod(); break;
				}
				case 6: (insertDef(dictionary, returnWord("Digitare la parola per la quale si deve inserire la definizione"), returnWord("Digitare la definizione")) == NOT_ERROR) ? PRNT_NOT_ERROR : PRNT_ERROR;
					endMethod(); break;
				case 7: searchDef(dictionary, returnWord("Digitare la parola per la quale si deve ricercare la definizione"));
					endMethod(); break;
				case 8: (saveDictionary(dictionary, returnWord("Digitare l'indirizzo nel quale salvare il dizionario")) == UNDEFINED) ? PRNT_ERROR: PRNT_NOT_ERROR;
					endMethod(); break;
				case 9:(compressHuffman(dictionary, returnWord("Digitare l'indirizzo nel quale salvare il dizionario"), codetable) == UNDEFINED) ? PRNT_ERROR : PRNT_NOT_ERROR;
					endMethod(); break;
				case 10:{
					char *primoRis = NULL, *secondoRis = NULL, *terzoRis = NULL;

					searchAdvance(dictionary, returnWord("Digitare la parola per la quale si deve efettuare la ricerca avanzata"), &primoRis, &secondoRis, &terzoRis);
					
					printf("Le tre parole simili a quela ricercata sono\n1) %s\n2) %s\n3) %s\n\n", primoRis, secondoRis, terzoRis);

					endMethod(); break;
				}
				case 11: checkExit = true; break;
			}

			CLEAR;
		} while(!checkExit);
	}
	
	return NOT_ERROR;
}

int main()
{
	run();
	endMethod();
	warning("\t\tARRIVEDERCI ");
	
	return 0;
}
