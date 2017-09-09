/** 
	 
*/
typedef struct {
	int frequenza;
	char letter;
	struct huffmanNODO* left;
	struct huffmanNODO* right;
} huffmanNODO;

/**
	
*/
void buildHeap(huffmanNODO* array, int lenght);

/**

*/
huffmanNODO* extractMin(huffmanNODO* array, int* heapsize);

/**

*/
void insert(huffmanNODO* array, huffmanNODO* temp, int* heapsize);
