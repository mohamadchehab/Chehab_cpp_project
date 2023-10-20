

#ifndef _heaps_H
#define _heaps_H 1

// Declaring element struct with double key
typedef struct TAG_ELEMENT{
    double key;
}ELEMENT;

// Declaring minheap struct with int capacity and size as well as element pointers array 
typedef struct TAG_HEAP{
    int capacity; /* capacity of the heap */
    int size; /* current size of the heap */
    ELEMENT **H; /* array of pointers to ELEMENT */
}HEAP;

// Declaration of all functions required for the MinHeap
void resetHeapify();
void DecreaseKey(HEAP* heap, int index, double newKey);
void BuildHeap(HEAP* heap);
bool isMinHeap(HEAP* heap);
int getHeapifyCount();
int Heapify(HEAP* heap, int index);
int Insertion(HEAP* heap, ELEMENT* element);
ELEMENT* ExtractMin(HEAP* heap);



#endif
