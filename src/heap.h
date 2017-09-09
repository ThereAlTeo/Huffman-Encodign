/** 
	Struttura dati.
	Rappresenta il singolo nodo che verrà utilizzato per realizzare l'albero di Huffman. 
*/
typedef struct {
	int frequenza;
	char letter;
	struct huffmanNODO* left;
	struct huffmanNODO* right;
} huffmanNODO;

/**
	Funzione.
	Costruisce l'HEAP utilizzato come start per la realizzazione dell'albero di Huffman.
*/
void buildHeap(huffmanNODO* array, int lenght);

/**
	Funzione.
	Ogni volta che viene invocata, restituisce l'elemento in testa all'HEAP.
*/
huffmanNODO* extractMin(huffmanNODO* array, int* heapsize);

/**
	Funzione.
	Ogni volta che viene invocata, inserisce un nuovo elemento nell'HEAP.
*/
void insert(huffmanNODO* array, huffmanNODO* temp, int* heapsize);
