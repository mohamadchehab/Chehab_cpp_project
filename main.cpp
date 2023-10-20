
// Library and header files imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "util.h"

// Main function
int main(int argc, char **argv) {
	// Declaration of pointer variables fp and MinHeap
    FILE *fp; 
    HEAP *MinHeap;

	// Declaration of variables
    int returnV;
    double key;
    double nextKey;
    int flag;

	// Declaration of arrays
    char Word[100];

	// Checking whether there are too many arguments
    if(argc < 4) {
	fprintf(stderr, "Usage: %s <ifile> <ofile> flag\n", argv[0]);
	exit(0);
    }

    flag = atoi(argv[3]);
    while(1) {
	returnV = nextInstruction(Word, &key, &nextKey);
	if(returnV == 0) {
            fprintf(stderr, "Warning: Invalid instruction: %s\n", Word);
	    continue;
        }

	if(strcmp(Word, "Stop")==0) {
	    fprintf(stdout, "Instruction: Stop\n");
	    return 0;
	}

	// Runs code for initializing the minheap
    if(strcmp(Word, "Init")==0) {
	    fprintf(stdout, "Instruction: Init %d\n", (int) key);
	    MinHeap = (HEAP *) calloc(1, sizeof(HEAP));
	    if(!MinHeap) {
		fprintf(stderr, "Error: Memory allocation failed\n");
		continue;
	    }       
	    MinHeap->capacity = key;
	    MinHeap->H = (ELEMENT **)calloc(key, sizeof(ELEMENT *));
	    if(!MinHeap->H) {
		free(MinHeap);
		continue;
	    }	
            MinHeap->size =0;
	}

	// Displays all the minheap elements
	if(strcmp(Word,"Print") == 0) {
	    fprintf(stdout, "Instruction: Print\n");
	    if(!MinHeap) {
		fprintf(stdout,"Error: heap is NUll\n");
		continue;
	    }		
	    fprintf(stdout, "%d\n",(int) MinHeap->size);
	    for(int i = 0; i < MinHeap->size; i++) {
		fprintf(stdout, "%lf\n", MinHeap->H[i]->key);
	    }
	}

	// Write minheap elements to file
	if(strcmp(Word, "Write") == 0) {
	    fprintf(stdout, "Instruction: Write\n");
	    if(!MinHeap) {
		fprintf(stdout, "Error: heap is NULL\n");
		continue;
 	    }
	    fp = fopen(argv[2], "w");
	    if(!fp) {
		fprintf(stderr, "Error: cannot open file %s\n", argv[2]);
		continue;	
            }
	    fprintf(fp, "%d\n", MinHeap->size);
	    for(int i = 0; i <MinHeap->size; i++) {
		fprintf(fp, "%lf\n", MinHeap->H[i]->key);
	    }
	    fclose(fp);	
	}

	// Reads in minheap elements from input file
	if(strcmp(Word, "Read") == 0) {
	    fprintf(stdout, "Instruction: Read\n");
	    if(!MinHeap) {
		fprintf(stdout, "Error: heap is NULL\n");
		continue;
	    }
	    fp = fopen(argv[1], "r");
	    if(!fp) {
		fprintf(stderr, "Error: cannot open file %s\n", argv[2]);
		continue;
	    }	
	    int n;
	    fscanf(fp, "%d", &n);
	    if(MinHeap->capacity < n) {
		fprintf(stderr, "Error: entries exceed MinHeap capacity\n");
		fclose(fp);
		continue;
	    }
	    int i = 0;
	    while((returnV = fscanf(fp, "%lf", &key)) == 1) {
		ELEMENT * el = (ELEMENT *) calloc(1, sizeof(ELEMENT *));
		el->key = key;
	 	MinHeap->H[i] = el;
	        MinHeap->size++;
	 //     	Insertion(MinHeap,el);
		i++;
	    } 
	    fclose(fp);
            if(!isMinHeap(MinHeap)) {
		BuildHeap(MinHeap);
		int count = getHeapifyCount();
		if(flag == 1 || flag == 3) {
		     fprintf(stdout, "Input array is NOT a MinHeap\n");
		     fprintf(stdout, "Call BuildHeap\n");
	             fprintf(stdout, "Number of Heapify calls triggered by BuildHeap: %d\n", count);
		}
	    }   
	}	
	// Inserts new element into minheap using Insertion function
	if(strcmp(Word, "Insert") == 0) {
	    fprintf(stdout, "Instruction: Insert %lf\n", key);
            if(!MinHeap) {
		fprintf(stderr, "Error: heap is NULL\n");
		continue;
	    }	
	    if(MinHeap->size == MinHeap->capacity) {
		fprintf(stderr, "Error: heap is full\n");
		continue;
	    }
	    ELEMENT * el = (ELEMENT *) calloc(1, sizeof(ELEMENT *));
	    el->key = key;
	    int index =Insertion(MinHeap, el);
	    if(flag == 0 || flag == 1) {
		fprintf(stdout, "Element with key %lf inserted into the heap\n", key);
	    } else if (flag == 2 || flag == 3) {
		fprintf(stdout, "Element with key %lf inserted at location %d of the heap array\n", key, index+1);
	    }
		
	}
	// Extracts the minimum element from the minheap 
	if(strcmp(Word, "ExtractMin") == 0) {
	    fprintf(stdout, "Instruction: ExtractMin\n");
	    if(!MinHeap) {
		fprintf(stderr, "Error: heap is NULL\n");
		continue;
	    }
	    if(MinHeap->size == 0) {
	 	fprintf(stderr, "Error: heap is empty\n");
		continue;
	    }
	    ELEMENT * el=  ExtractMin(MinHeap);
	    if(flag == 0 || flag == 2) {
	         fprintf(stdout, "Element with key %lf extracted from the heap\n", el->key);
	    }
	    if(flag == 1 || flag == 3) {
		int count = getHeapifyCount();
 		fprintf(stdout, "Element with key %lf extracted from the heap\n", el->key);
		fprintf(stdout, "Number of Heapify calls triggered by ExtractMin: %d\n", count);
	    }
	}

	// Code that decreases key at index using DecreaseKey function
	if(strcmp(Word, "DecreaseKey") == 0) {
	    int pos = (int) key;
	    fprintf(stdout, "Instruction: DecreaseKey %d %lf\n", pos, nextKey);
	    if(!MinHeap) {
		fprintf(stderr, "Error: heap is NULL\n");
		continue;
	    }
	    if(MinHeap->size == 0) {
		fprintf(stderr, "Error: heap is empty\n");
		continue;
	    }
	  
	    if (nextKey > MinHeap->H[pos-1]->key || pos < 0 || pos > MinHeap->size){
        	fprintf(stderr, "Error: invalid call to DecreaseKey\n");
     		continue;
   	    }	   
	    DecreaseKey(MinHeap, pos, nextKey);
	
	}	
    }
} 
