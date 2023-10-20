

#include <cstddef>
#include "heap.h"
int heapifyCount = 0;

// Function that returns the number of heapify calls done by an operation such as BuildHeap and ExtractMin
int getHeapifyCount() {
    return heapifyCount;
}
// Function that resets the number of heapify calls before another operation
void resetHeapify() {
    heapifyCount = 0;
}

// Function that performs the Heapify operation to preserve the MinHeap operation
int Heapify(HEAP* heap, int index) {
    int leftchild = 2 * index +1;
    int rightchild = 2 * index +2;
    int smallest = index;

    if(leftchild < heap->size && heap->H[leftchild]->key < heap->H[smallest]->key) {
	smallest = leftchild;
}
    if(rightchild < heap->size && heap->H[rightchild]->key < heap->H[smallest]->key) {
	smallest = rightchild;
}

    if(smallest != index) {
	ELEMENT* temp = heap->H[index];
	heap->H[index] = heap->H[smallest];
	heap->H[smallest] = temp;
	heapifyCount++;
	return Heapify(heap, smallest);
    }
    return index;
}

// Functions that forms a MinHeap after an unordered array has been input by the user
void BuildHeap(HEAP* heap) {
    int n = heap->size;
    heapifyCount = 0;
    for(int i = (n/2)-1; i>=0; i--) {
	Heapify(heap, i);
	heapifyCount++;
    }
}

// Function to extract the minimum element of the heap, which is the first element and reorders the MinHeap
ELEMENT* ExtractMin(HEAP* heap) {
   if(heap->size <= 0)
	return NULL;

   ELEMENT* minElement = heap->H[0];

   heap->H[0] = heap->H[heap->size - 1];
   heap->size--;

   heapifyCount = 1;

   Heapify(heap,0);
   return minElement;
}

// Function that takes in an index and updates the value at that index with a new key 
void DecreaseKey(HEAP* heap, int index, double newKey) {
    heap->H[index-1]->key = newKey;
    int n = heap->size;
    for(int i = (n/2); i>=0;i--) {
         Heapify(heap, i);
    }
}

// Function that checks whether the array elements have the MinHeap property
bool isMinHeap(HEAP *heap) {
    int n = heap->size;
    int lastNonLeaft = (heap->size / 2) -1;
    for(int i = 0; i<= lastNonLeaft; i++) {
         int leftChild = 2 * i + 1;
  	 int rightChild = 2 * i + 2;

 	 if(leftChild < n && heap->H[leftChild]->key < heap->H[i]->key) {
	     return false;
	 }
   
         if(rightChild < n && heap->H[rightChild]->key < heap->H[i]->key) {
	     return false;
	 }
    }
    return true;
}
// Function to insert a new element into the MinHeap while preserving the property
int Insertion(HEAP* heap, ELEMENT* element) {
    int index = heap->size;
    heap->H[index] = element;
    heap->size++;

    while(index > 0) {
        int parent = (index - 1)/2;
	    if(heap->H[index]->key < heap->H[parent]->key) {
            ELEMENT* temp = heap->H[index];
   	        heap->H[index] = heap->H[parent];
    	    heap->H[parent] = temp;
            index = parent;
        } else {
            break;
        }
    }
    return index;
}
