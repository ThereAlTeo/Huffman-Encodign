#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "lib1617.h"

/* 81 = 8.1%, 128 = 12.8% and so on. The 27th frequency is the space. */
int frequenzaLettereItaliane[] = { 110, 8, 44, 36, 115, 7, 15, 14, 112,
									3, 10, 64, 24, 69, 97, 29, 4, 63,
									49, 55, 29, 20, 3, 8, 7, 5, 90 };

void inizializzazioneTabellaHash(NODO* dictionary)
{
	for (int i = 0; i < NUM_ELEMENTI; i++)
	{
		dictionary[i].countWord = 0;
		dictionary[i].TestaLis = NULL;
	}
}

NODO* createFromFile(char* nameFile)
{
	NODO* dictionary = (NODO*) malloc(NUM_ELEMENTI * sizeof(NODO));
	FILE* file = fopen(nameFile, "r");

	int i = -1, tempChar;
	char* word = NULL;

	if (dictionary == NULL || file == NULL) return NULL;

	inizializzazioneTabellaHash(dictionary);

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

int countWord(NODO* dictionary)
{
	int somma = 0;

	for (int i = 0; i < NUM_ELEMENTI; i++)
		somma += dictionary[i].countWord;

	return somma;
}

char* getWord(TipoListaChaining node)
{
	if (node != NULL)
		return node->word;
	else
		return NULL;
}

void finalChain(TipoListaChaining nuovo, TipoListaChaining temp)
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
		NODO* tab = &(dictionary[hashFuction(word)]);

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
		finalChain(nuovo, temp->next);
		temp->next = nuovo;
		tab->countWord++;

		return NOT_ERROR;

	}

	return ERROR_FIND;
}

void finalCanc(TipoListaChaining temp, TipoListaChaining nuovo)
{
	if (temp != NULL)
		temp->prec = nuovo;
}

int cancWord(NODO** d, char* word)
{
	NODO* dictionary = *d;
	NODO* tab = &(dictionary[hashFuction(word)]);
	TipoListaChaining temp = tab->TestaLis;

	if (temp == NULL) return ERROR_FIND;

	if (strcmp(temp->word, word) == 0)
	{
		tab->TestaLis = temp->next;
		finalCanc(temp->next, NULL);
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
			finalCanc(temp->next, temp);
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
		TipoListaChaining temp = dictionary[hashFuction(word)].TestaLis;

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
	TipoListaChaining temp = dictionary[hashFuction(word)].TestaLis;

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

	if (file == NULL) return UNDEFINED;

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
	NODO* dictionary = (NODO*)malloc(NUM_ELEMENTI * sizeof(NODO));
	FILE* file = fopen(fileInput, "r");

	if (dictionary == NULL || file == NULL) return NULL;

	inizializzazioneTabellaHash(dictionary);

	while (feof(file) != EOF)
	{
		char* word = NULL;
		char* def = NULL;
		char* temp = NULL;
		int i = 1, j = 0;
		bool check = true;

		if (fgets(temp, MAX_STRING, file) == NULL)
			return NULL;

		while (temp[i] != '"')
		{
			if (word == NULL)
				word = (char*)malloc(sizeof(char));
			else
				word = (char*)realloc(word, (i + 1) * sizeof(char));

			if (word == NULL) return NULL;

			word[i - 1] = temp[i];

			i++;
		}

		insertWord(&dictionary, word);

		i += 4;

		while (temp[i] != ']')
		{
			if (temp[i + 1] == '(')	//definizione = NULL, usciamo
			{
				check = false;
				break;
			}

			if (def == NULL)
				def = (char*)malloc(sizeof(char));
			else
				def = (char*)realloc(def, (j + 1) * sizeof(char));

			if (def == NULL) return NULL;

			def[j] = temp[i];

			i++;
			j++;
		}

		if (check == true)
			insertDef(dictionary, word, def);
	}

	fclose(file);

	return dictionary;
}

int searchAdvance(NODO* dictionary, char* word, char** primoRis, char** secondoRis, char** terzoRis)
{
	return 0;
}

int hashFuction(char* word)
{
	return (((int) word[0]) % MOD_ASCII_CODE);
}

int getFrequesnza(huffmanNODO* temp) {
	return temp->frequenza;
}

int getLetter(huffmanNODO* temp) {
	return temp->letter;
}

/*builds the huffman tree and returns its address by reference*/
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


/* builds the table with the bits for each letter. 1 stands for binary 0 and 2 for binary 1 (used to facilitate arithmetic)*/
void createTable(huffmanNODO *tree, char* codeTable[], char *Code, int Level) {
	
	if (tree->left == NULL && tree->right == NULL)
	{
		codeTable[(int)tree->letter] = (char*)malloc(strlen(Code) * sizeof(char));

		if (codeTable[(int)tree->letter] == NULL) return NULL;

		strcpy(codeTable[(int)tree->letter], Code);
	}
	else {
		if (Code == NULL)
			Code = (char*)malloc(sizeof(char));
		else
			Code = (char*)realloc(Code, (Level + 1) * sizeof(char));

		if (Code == NULL) return NULL;
		
		Code[Level] = '0';
		Code[Level+1] = '\0';
		createTable(tree->left, codeTable, Code, Level+1);
		Code[Level] = '1';
		Code[Level + 1] = '\0';
		createTable(tree->right, codeTable, Code, Level+1);
	}
}

/*function to compress the input*/
int compressHuffman(NODO* dictionary, char* fileOutput, char* codeTable[]) {

	int originalBits = 0, compressedBits = 0;
	FILE *out = fopen(fileOutput, "w");

	if (out == NULL) return NULL;

	for (int i = 0; i < NUM_ELEMENTI; i++)
	{
		TipoListaChaining temp = dictionary[i].TestaLis;

		while (temp != NULL)
		{
			originalBits += (int)strlen(temp->word);

			for (int j = 0; j < strlen(temp->word); j++)
			{
				compressedBits += strlen(codeTable[temp->word[j] - MOD_ASCII_CODE]);
				fprintf(out, "%s", codeTable[temp->word[j] - MOD_ASCII_CODE]);
			}

			compressedBits += 3;
			fprintf(out, "%s", codeTable[NUM_ELEMENTI - 1]);

			if (temp->def != NULL)
			{
				originalBits += strlen(temp->def);

				for (int j = 0; j < strlen(temp->def); j++)
					if (temp->def[j] != ' ')
					{
						compressedBits += strlen(codeTable[ temp->def[j] - MOD_ASCII_CODE]);
						fprintf(out, "%s", codeTable[temp->def[j] - MOD_ASCII_CODE]);
					}
					else
					{
						compressedBits += 3;
						fprintf(out, "%s", codeTable[NUM_ELEMENTI - 1]);
					}
			}

			fprintf(out, "%s", "\n");
			temp = temp->next;
		}
	}

	fclose(out);

	//Visualizzare a monitor !!!
	/*print details of compression on the screen*/
	printf("Original bits = %d \n", originalBits * BYTE);
	printf("Compressed bits = %d \n", compressedBits);
	printf("Saved %.5f\% of memory \n", ((float)compressedBits / (originalBits * BYTE)) * 100);
}

char getCharByHuffman(huffmanNODO* tree, char* temp, int* index)
{
	if (tree->left == NULL && tree->right == NULL) {
		if (tree->letter == NUM_ELEMENTI)
			return (char) 32;
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

/*function to decompress the input*/
int decompressHuffman(NODO* dictionary, char* fileInput, huffmanNODO* tree) {
	
	FILE* file = fopen(fileInput, "r");
	char* temp = (char*) malloc(MAX_STRIGN_HUFFMAN * sizeof(char));;

	if (dictionary == NULL || file == NULL || temp == NULL) return UNDEFINED;

	while (fgets(temp, MAX_STRIGN_HUFFMAN, file) != NULL)
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

			if (def == NULL) return NULL;

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
