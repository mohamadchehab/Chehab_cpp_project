

#ifndef _heaps_H
#define _heaps_H 1

typedef struct TAG_ELEMENT{
    double key;
}ELEMENT;

typedef struct TAG_HEAP{
    int capacity; /* capacity of the heap */
    int size; /* current size of the heap */
    ELEMENT **H; /* array of pointers to ELEMENT */
}HEAP;
void resetHeapify();
bool isMinHeap(HEAP* heap);
int getHeapifyCount();
int Heapify(HEAP* heap, int index);
void BuildHeap(HEAP* heap);
ELEMENT* ExtractMin(HEAP* heap);
void DecreaseKey(HEAP* heap, int index, double newKey);
int Insertion(HEAP* heap, ELEMENT* element);

#endif
