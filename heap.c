#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

int leftSon(int index) {
	return (index*2) + 1;
}

int rightSon(int index) {
	return (index*2) + 2;
}

int parent(int index) {
	return (int) (index-1)/2;
}

void assegnamento(huffmanNODO* first, huffmanNODO* second)
{
	first->frequenza = second->frequenza;
	first->letter = second->letter;
	first->right = second->right;
	first->left = second->left;
}

void swap(huffmanNODO* first, huffmanNODO* second)
{
	huffmanNODO temp;

	assegnamento(&temp, second);
	assegnamento(second, first);
	assegnamento(first, &temp);
}

void heapify(huffmanNODO* array, int index, int lenght)
{
	int l = leftSon(index), r = rightSon(index), largest;

	if (l <= lenght && array[l].frequenza <= array[index].frequenza)
		largest = l;
	else 
		largest = index;

	if (r <= lenght && array[r].frequenza <= array[largest].frequenza)
		largest = r;

	if (largest != index)
	{
		swap(&array[index], &array[largest]);
		heapify(array, largest, lenght);
	}
}

void buildHeap(huffmanNODO* array, int lenght)
{
	int mid = (int) lenght / 2;
	
	for (int i = mid; i >= 0; i--)
		heapify(array, i, lenght);
}

huffmanNODO* extractMin(huffmanNODO* array, int* heapsize)
{
	if (*heapsize < 0) return NULL;

	huffmanNODO* ret = (huffmanNODO*) malloc(sizeof(huffmanNODO));

	if (ret == NULL) return NULL;

	assegnamento(ret, &array[0]);
	assegnamento(&array[0], &array[*heapsize]);
	(*heapsize)--;
	heapify(array, 0, *heapsize);

	return ret;
}

void insert(huffmanNODO* array, huffmanNODO* temp, int* heapsize)
{
	(*heapsize)++;
	int i = *heapsize;

	assegnamento(&array[i], temp);

	while (i > 1 && array[parent(i)].frequenza >= array[i].frequenza)
	{
		swap(&array[i], &array[parent(i)]);
		i = parent(i);
	}
}
