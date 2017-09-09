#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "lib1617.h"

/**
	Array Globale.
	Contiene la percentuale di presenza delle sigolo lettere nelle parole del dizionario Italiano.
	La posizione 27 e' occupata del valore relativo allo spazio.
*/
int frequenzaLettereItaliane[] = { 110, 8, 44, 36, 115, 7, 15, 14, 112,
									3, 10, 64, 24, 69, 97, 29, 4, 63,
									49, 55, 29, 20, 3, 8, 7, 5, 90 };

int hashFunction(char* word)
{
	return (((int)word[0]) % MOD_ASCII_CODE);
}

int inizializzazioneTabellaHash(NODO* dictionary)
{
	if (dictionary != NULL)
	{
		for (int i = 0; i < NUM_ELEMENTI; i++)
		{
			dictionary[i].countWord = 0;
			dictionary[i].TestaLis = NULL;
		}

		return NOT_ERROR;
	}

	return ERROR_FIND;
}

NODO* createFromFile(char* nameFile)
{
	NODO* dictionary = (NODO*) malloc(NUM_ELEMENTI * sizeof(NODO));
	FILE* file = fopen(nameFile, "r");

	int i = -1, tempChar;
	char* word = NULL;

	if (inizializzazioneTabellaHash(dictionary) == ERROR_FIND || file == NULL) return NULL;

	while ((tempChar = fgetc(file)) != EOF)
	{
		if (isalpha(tempChar) != 0)
		{
			i++;

			if (i == 0)
				word = (char*)malloc(sizeof(char));
			else
				word = (char*)realloc(word, (i + 1) * sizeof(char));

			if (word == NULL) return NULL;

			word[i] = (char)tolower(tempChar);
		}

		if (isspace(tempChar) != 0)
		{
			if (i >= MIN_WORD - 1)
			{
				word[i + 1] = '\0';
				if (insertWord(&dictionary, word) == ERROR_FIND) return NULL;
			}

			i = -1;
			word = NULL;
		}
	}

	fclose(file);

	return dictionary;
}

void printDictionary(NODO* dictionary)
{
	if (dictionary != NULL)
	{
		printf("\n\n");

		for (int i = 0; i < NUM_ELEMENTI; i++)
		{
			TipoListaChaining temp = dictionary[i].TestaLis;

			while (temp != NULL)
			{
				printf("\"%s\":[%s]\n", temp->word, temp->def == NULL ? "(null)" : temp->def);
				temp = temp->next;
			}
		}
	}
	else
		printf("\n\n\tDizionario VUOTO !!!\n\n");
	
}

int countWord(NODO* dictionary)
{
	int somma = 0;

	for (int i = 0; i < NUM_ELEMENTI; i++)
		somma += dictionary[i].countWord;

	return somma;
}

/**
	Funzione AUSILIARIA.
*/
char* getWord(TipoListaChaining node)
{
	if (node != NULL)
		return node->word;
	else
		return NULL;
}

/**
	Funzione AUSILIARIA.
*/
void auxFunction(TipoListaChaining temp, TipoListaChaining nuovo)
{
	if (temp != NULL)
		temp->prec = nuovo;
}

int insertWord(NODO** d, char* word)
{
	NODO* dictionary = *d;

	if (strlen(word) >= MIN_WORD && strlen(word) <= MAX_WORD)
	{
		TipoListaChaining nuovo = (TipoListaChaining)malloc(sizeof(CELLA));
		NODO* tab = &(dictionary[hashFunction(word)]);

		if (nuovo == NULL) return ERROR_FIND;

		nuovo->word = word;
		nuovo->def = NULL;
		nuovo->next = NULL;
		nuovo->prec = NULL;

		if (tab->TestaLis == NULL)
		{
			tab->TestaLis = nuovo;
			tab->countWord++;

			return NOT_ERROR;
		}

		TipoListaChaining temp = tab->TestaLis;

		if (strcmp(word, temp->word) < 0)
		{
			tab->TestaLis = nuovo;
			temp->prec = nuovo;
			nuovo->next = temp;
			tab->countWord++;

			return NOT_ERROR;
		}
		else if (strcmp(word, temp->word) == 0) 
			return UNDEFINED;

		while (temp->next != NULL && strcmp(word, getWord(temp->next)) > 0)
			temp = temp->next;

		if (temp->next != NULL && strcmp(word, getWord(temp->next)) == 0) return UNDEFINED;

		nuovo->next = temp->next;
		nuovo->prec = temp;
		auxFunction(temp->next, nuovo);
		temp->next = nuovo;
		tab->countWord++;

		return NOT_ERROR;
	}

	return ERROR_FIND;
}

int cancWord(NODO** d, char* word)
{
	NODO* dictionary = *d;
	NODO* tab = &(dictionary[hashFunction(word)]);
	TipoListaChaining temp = tab->TestaLis;

	if (temp == NULL) return ERROR_FIND;

	if (strcmp(temp->word, word) == 0)
	{
		tab->TestaLis = temp->next;
		auxFunction(temp->next, NULL);
		tab->countWord--;

		free(temp);

		return NOT_ERROR;
	}
	else
	{
		while (temp->next != NULL && strcmp(getWord(temp->next), word) != 0)
			temp = temp->next;

		if (strcmp(getWord(temp->next), word) == 0)
		{
			TipoListaChaining canc = temp->next;
			temp->next = canc->next;
			auxFunction(temp->next, temp);
			tab->countWord--;

			free(canc);

			return NOT_ERROR;
		}
	}

	return ERROR_FIND;
}

char* getWordAt(NODO* dictionary, int index)
{
	if (index <= countWord(dictionary))
	{
		int somma = 0, conta;
		int i = 0, j = 0;

		do
		{
			somma += dictionary[i].countWord;
			i++;
		} while (i < NUM_ELEMENTI && somma - 1 < index);

		i--;
		conta = dictionary[i].countWord - (somma - index);

		TipoListaChaining aux = dictionary[i].TestaLis;

		while (j < conta)
		{
			aux = aux->next;
			j++;
		}

		return aux->word;
	}

	return NULL;
}

int insertDef(NODO* dictionary, char* word, char* def)
{
	if (strlen(def) <= MAX_DEF)
	{
		TipoListaChaining temp = dictionary[hashFunction(word)].TestaLis;

		if (temp != NULL)
		{
			while (temp->next != NULL && strcmp(temp->word, word) != 0)
				temp = temp->next;

			if (strcmp(temp->word, word) == 0)
			{
				if (temp->def == NULL)
				{
					temp->def = def;
					return NOT_ERROR;
				}
				else
				{
					free(temp->def);
					temp->def = def;
				}
			}
		}
	}

	return ERROR_FIND;
}

char* searchDef(NODO* dictionary, char* word)
{
	TipoListaChaining temp = dictionary[hashFunction(word)].TestaLis;

	if (temp != NULL) {

		while (strcmp(temp->word, word) != 0 && temp->next != NULL)
			temp = temp->next;

		if (strcmp(temp->word, word) == 0)
			return temp->def;
	}
	return NULL;
}

int saveDictionary(NODO* dictionary, char* fileOutput)
{
	FILE* file = fopen(fileOutput, "w");

	if (file == NULL || dictionary == NULL) return UNDEFINED;

	for (int i = 0; i < NUM_ELEMENTI; i++)
	{
		TipoListaChaining temp = dictionary[i].TestaLis;

		while (temp != NULL)
		{
			fprintf(file, "\"%s\" : [%s]\n", temp->word, temp->def != NULL ? temp->def : "(null)");
			temp = temp->next;
		}
	}

	fclose(file);

	return NOT_ERROR;
}

NODO* importDictionary(char* fileInput)
{
	NODO* dictionary = (NODO*) malloc(NUM_ELEMENTI * sizeof(NODO));
	FILE* file = fopen(fileInput, "r");
	char* temp = (char*)malloc(MAX_STRING * sizeof(char));

	if (inizializzazioneTabellaHash(dictionary) == ERROR_FIND || file == NULL || temp == NULL) return NULL;

	while (fgets(temp, MAX_STRING, file) != NULL)
	{
		char* word = NULL;
		char* def = NULL;
		int i = 1, j = 0;
		bool check = true;

		if (strlen(temp) < MAX_STRING)
			temp[strlen(temp) - 1] = '\0';
		
		while (temp[i] != '"')
		{
			if (word == NULL)
				word = (char*)malloc(sizeof(char));
			else
				word = (char*)realloc(word, (i + 1) * sizeof(char));

			if (word == NULL) return NULL;

			word[i - 1] = temp[i];
			word[i++] = '\0';
		}

		insertWord(&dictionary, word);

		i += 4;

		do{
			if (temp[i + 1] == '(') {	//definizione = NULL, usciamo
				check = false; 
				break;
			}

			if (def == NULL)
				def = (char*)malloc(sizeof(char));
			else
				def = (char*)realloc(def, (j + 1) * sizeof(char));

			if (def == NULL) return NULL;

			def[j] = temp[++i];
			def[++j] = '\0';
		} while (temp[i + 1] != ']');

		if (check == true)
			insertDef(dictionary, word, def);
	}

	fclose(file);

	return dictionary;
}

/**
	Funzione.
	Restituisce il minore dei tre valori pessati per input.
*/
int minimum(int a, int b, int c)
{
	int min = a;

	if (b < min) min = b;
	if (c < min) min = c;

	return min;
}

/**
	Funzione.
	Restituisce la distnaza di Levenshtein di due parole.
*/
int Levenshtein_distance(char *x, char *y)
{
	int m = strlen(x), n = strlen(y), i, j, distance;

	int *prev = malloc((n + 1) * sizeof(int));
	int *curr = malloc((n + 1) * sizeof(int));
	int *tmp = 0;

	for (i = 0; i <= n; i++)
		prev[i] = i;

	for (i = 1; i <= m; i++) 
	{
		curr[0] = i;
		for (j = 1; j <= n; j++)
		{
			if (x[i - 1] != y[j - 1]) 
			{
				int k = minimum(curr[j - 1], prev[j - 1], prev[j]);
				curr[j] = k + 1;
			}
			else
				curr[j] = prev[j - 1];			
		}

		tmp = prev;
		prev = curr;
		curr = tmp;

		memset((void*)curr, 0, sizeof(int) * (n + 1));
	}

	distance = prev[n];

	free(curr);
	free(prev);

	return distance;

}

/**
Input:
- dictionary: la struttura dati in cui avete memorizzato il dizionario
- word: la parola da cercare nel dizionare per verificare la sua presenza.
Output:
- 0 in caso di assenza 
- 1 in caso di presenza 
*/
int searchWord(NODO* dictionary, char* word)
{
	TipoListaChaining temp = dictionary[hashFunction(word)].TestaLis;

	while (temp != NULL)
	{
		if (strcmp(temp->word, word) == 0) return ERROR_FIND;
		temp = temp->next;
	}

	return NOT_ERROR;
}

int searchAdvance(NODO* dictionary, char* word, char** primoRis, char** secondoRis, char** terzoRis)
{
	if(countWord(dictionary) ==  0) return UNDEFINED;
	
	int distPrimo, distSecondo, distTerzo, ret = searchWord(dictionary, word);
	bool checkInizialia = true;

	for(int i = 0; i < NUM_ELEMENTI; i++)
	{
		TipoListaChaining temp = dictionary[i].TestaLis;
		
		if(temp != NULL && strcmp(temp->word, word) == 0) temp = temp->next;

		while(temp != NULL)
		{
			int distanza = Levenshtein_distance(temp->word, word);

			if(distanza < 7)
			{
				if (checkInizialia)
				{
					if (*primoRis == NULL)
					{
						*primoRis = temp->word;
						distPrimo = distanza;
					}
					else if (*secondoRis == NULL)
					{
						*secondoRis = temp->word;
						distSecondo = distanza;
					}
					else if(*terzoRis == NULL)
					{
						*terzoRis = temp->word;
						distTerzo = distanza;
						checkInizialia = false;
					}
				}
				else
				{
					if (distanza < distPrimo)
					{
						*primoRis = temp->word;
						distPrimo = distanza;
					}
					else if (distanza < distSecondo)
					{
						*secondoRis = temp->word;
						distSecondo = distanza;
					}
					else if (distanza < distTerzo)
					{
						*terzoRis = temp->word;
						distTerzo = distanza;
					}
				}
			}

			temp = temp->next;
		}
	}
	
	return ret;
}

/**
	Funzione AUSILIARIA.
*/
int getFrequesnza(huffmanNODO* temp) {
	return temp->frequenza;
}

/**
	Funzione AUSILIARIA.
*/
int getLetter(huffmanNODO* temp) {
	return temp->letter;
}

huffmanNODO* buildHuffmanTree()
{
	int heapsize = NUM_ELEMENTI - 1;

	huffmanNODO *array = (huffmanNODO*) malloc(NUM_ELEMENTI * sizeof(huffmanNODO));

	if (array == NULL) return NULL;

	for (int i = 0; i < NUM_ELEMENTI; i++)
	{
		array[i].frequenza = frequenzaLettereItaliane[i];
		array[i].letter = i;
		array[i].left = NULL;
		array[i].right = NULL;
	}

	buildHeap(array, heapsize);

	while (heapsize > 0)
	{
		huffmanNODO* temp = (huffmanNODO*)malloc(sizeof(huffmanNODO));

		if (temp == NULL) return NULL;

		temp->left = extractMin(array, &heapsize);
		temp->right = extractMin(array, &heapsize);
		temp->frequenza = getFrequesnza(temp->left) + getFrequesnza(temp->right);
		temp->letter = getLetter(temp->left) + getLetter(temp->right);

		insert(array, temp, &heapsize);
	}

	return extractMin(array, &heapsize);
}

void createTable(huffmanNODO *tree, char* codeTable[], char* Code, int Level) {
	
	if (tree->left == NULL && tree->right == NULL) {
		codeTable[(int) tree->letter] = (char*) malloc(strlen(Code) * sizeof(char));

		if (codeTable[(int) tree->letter] == NULL) return NULL;

		strcpy(codeTable[(int) tree->letter], Code);
	}
	else {
		if (Code == NULL)
			Code = (char*)malloc(sizeof(char));
		else
			Code = (char*)realloc(Code, (Level + 1) * sizeof(char));

		if (Code == NULL) return NULL;

		Code[Level] = '0';
		Code[Level + 1] = '\0';
		createTable(tree->left, codeTable, Code, Level + 1);
		Code[Level] = '1';
		Code[Level + 1] = '\0';
		createTable(tree->right, codeTable, Code, Level + 1);
	}
}

int compressHuffman(NODO* dictionary, char* fileOutput, char* codeTable[]) {

	int originalBits = 0, compressedBits = 0;
	FILE *out = fopen(fileOutput, "w");

	if (out == NULL || dictionary == NULL) return UNDEFINED;

	for (int i = 0; i < NUM_ELEMENTI; i++)
	{
		TipoListaChaining temp = dictionary[i].TestaLis;

		while (temp != NULL)
		{
			originalBits += strlen(temp->word);

			for (int j = 0; j < strlen(temp->word); j++)
			{
				compressedBits += strlen(codeTable[((int) temp->word[j]) - MOD_ASCII_CODE]);
				fprintf(out, "%s", codeTable[((int) temp->word[j]) - MOD_ASCII_CODE]);
			}

			compressedBits += 3;
			fprintf(out, "%s", codeTable[NUM_ELEMENTI - 1]);

			if (temp->def != NULL)
			{
				originalBits += strlen(temp->def);

				for (int j = 0; j < strlen(temp->def); j++) {
					if (temp->def[j] != ' ')
					{
						compressedBits += strlen(codeTable[((int) temp->def[j]) - MOD_ASCII_CODE]);
						fprintf(out, "%s", codeTable[((int) temp->def[j]) - MOD_ASCII_CODE]);
					}
					else
					{
						compressedBits += 3;
						fprintf(out, "%s", codeTable[NUM_ELEMENTI - 1]);
					}
				}
			}

			fprintf(out, "%s", "\n");
			temp = temp->next;
		}
	}

	fclose(out);

	//Visualizzare a monitor !!!
	printf("\n\n\nOriginal bits = %d \n", originalBits * BYTE);
	printf("Compressed bits = %d \n", compressedBits);
	printf("Saved %.5f\% of memory \n", ((float) compressedBits / (originalBits * BYTE)) * 100);

	return NOT_ERROR;
}

/**
	Funzione.
	Restituisce un carattere. 
*/
char getCharByHuffman(huffmanNODO* tree, char* temp, int* index)
{
	if (tree->left == NULL && tree->right == NULL) {
		if (tree->letter == NUM_ELEMENTI)
			return ' ';
		else
			return ((char)tree->letter + MOD_ASCII_CODE);
	}		
	else if (temp[(*index)] == '0'){
		(*index)++;
		return getCharByHuffman(tree->left, temp, index);
	}
	else{
		(*index)++;
		return getCharByHuffman(tree->right, temp, index);
	}
}

int decompressHuffman(NODO* dictionary, char* fileInput, huffmanNODO* tree) {
	
	FILE* file = fopen(fileInput, "r");
	char* temp = (char*) malloc(MAX_STRIGN_HUFFMAN * sizeof(char));

	if (inizializzazioneTabellaHash(dictionary) == ERROR_FIND || file == NULL || temp == NULL) return UNDEFINED;

	while(fgets(temp, MAX_STRIGN_HUFFMAN, file) != NULL)
	{
		char* word = NULL;
		char* def = NULL;
		int i = 0, j = 0, k = 0;
		bool finishSetWord = true;

		if(strlen(temp) < MAX_STRIGN_HUFFMAN)
			temp[strlen(temp)-1] = '\0';

		while (finishSetWord)
		{
			char auxChar = getCharByHuffman(tree, temp, &j);
			
			if (isalpha(auxChar) != 0)
			{
				if (word == NULL)
					word = (char*)malloc(sizeof(char));
				else
					word = (char*)realloc(word, (i + 1) * sizeof(char));

				if (word == NULL) return UNDEFINED;
				
				word[i] = auxChar;
				word[++i] = '\0';
			}
			else
				finishSetWord = false;
		}

		insertWord(&dictionary, word);

		while (temp[j] != '\0')
		{
			if (def == NULL)
				def = (char*)malloc(sizeof(char));
			else
				def = (char*)realloc(def, (k + 1) * sizeof(char));

			if (def == NULL) return UNDEFINED;

			char auxChar = getCharByHuffman(tree, temp, &j);

			def[k] = auxChar;
			def[++k] = '\0';
		}

		if (def != NULL)
			insertDef(dictionary, word, def);
	}

	fclose(file);

	return NOT_ERROR;
}
