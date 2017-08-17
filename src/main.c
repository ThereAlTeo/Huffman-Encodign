#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lib1617.h"
#include "management.h"

/**

*/
void getHuffman(NODO* dictionary, huffmanNODO *tree)
{
	if(tree == NULL)
		tree = buildHuffmanTree();
	
	char *codetable[NUM_ELEMENTI], *code = (char*)malloc(sizeof(char));
	int Level = 0;

	createTable(tree, codetable, code, Level);

	compressHuffman(dictionary, returnWord("Digitare l'indirizzo nel quale salvare il dizionario"), codetable);
}

/**

*/
void getImportDictionary(NODO* dictionary)
{

}

/*

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
				case 1: printDictionary(dictionary);
					endMethod(); break;
				case 2: printf("\n\nIl numero di parole contenute nel dizionario e': %d\n\n", countWord(dictionary));
					endMethod(); break;
				case 3: insertWord(&dictionary, returnWord("Digitare la parola da inserire"));
					endMethod(); break;
				case 4: cancWord(&dictionary, returnWord("Digitare la parola da cancellare"));
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
				case 6: insertDef(dictionary, returnWord("Digitare la parola per la quale si deve inserire la definizione"), returnWord("Digitare la definizione"));
					endMethod(); break;
				case 7: searchDef(dictionary, returnWord("Digitare la parola per la quale si deve ricercare la definizione"));
					endMethod(); break;
				case 8: saveDictionary(dictionary, returnWord("Digitare l'indirizzo nel quale salvare il dizionario"));
					endMethod(); break;
				case 9: getHuffman(dictionary, tree);
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

