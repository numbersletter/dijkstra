#ifndef HEAP_H
#define HEAP_H

#include "Graph.h"

typedef struct {
  int vertexInd;
  int distance;
} HeapNode;

typedef struct {
  HeapNode **nodes;      // key/data of the Heap (distances)
  int capacity;         // capacity of the array
  int heap_size;        // number of elements in heap stored in array
} Heap;


/*
 * Constructs the heap with initial capacity size.
 * Returns null if any memory errors arise.
 */
Heap* createHeap(int size);

/*
 * Allocate heap node.
 */
HeapNode *createHeapNode(int vertexInd, int distance);

/*
 * Helper method to insert elements into the array which is subsequently
 * represented and contained by the heap.
 * Returns null if any memory errors or heap overflow arises.
 */
Heap* insert(Heap* heap, int vertexInd, int distance);

/*
 * Deallocates the heap.
 */
void freeHeap(Heap* heap);

/*
 * Deallocate heapnode.
 */
void freeHeapNode(HeapNode *node);

/*
 * index of left child of element at i
 * if A[i] is a leaf, return -1
 */
int leftChild(Heap* heap, int i);

/*
 * index of right child of element at i
 * if A[i] is a leaf, return -1
 */
int rightChild(Heap* heap, int i);

/*
 * Returns parent of the node at index i.
 * If index is out of bounds, returns -1.
 * If the i = 0 (the root), returns -1.
 */
int parent(Heap* heap, int i);

/*
 * Prints the keys of the elements of the heap (which are stored in
 * containing array).
 */
void printHeap(Heap* heap, Graph *g);


//Min priority queue methods below:
/*
 * Min-heapifies the ith element in the heap.
 */
void MinHeapify(Heap* heap, int i);

/*
 * Decrease key of a node in the minimum heap while maintaining the min-heap
 * property.
 */
void MinHeap_DecreaseKey(Heap *heap, int vertexInd, int newDist);

/*
 * Insert new node into heap while maintaining the min-heap property.
 */
void MinHeap_Insert(Heap *heap, int vertexInd, int distance);

/*
 * Find minimum of the min heap. Returns NULL if the heap is empty.
 */
HeapNode *MinHeap_Minimum(Heap *heap);

/*
 * Find and extract the minimum of the heap. The node does not exist in the
 * min heap afterward.
 */
HeapNode *MinHeap_ExtractMin(Heap *heap);


#endif
