#include "Heap.h"
#include <stdio.h>
#include <stdlib.h>

Heap* createHeap(int size)
{
  Heap* heap = (Heap*)malloc(sizeof(Heap));
  if(!heap)
  {
    fprintf(stderr, "Failed allocating heap.\n");
    return NULL;
  }

  // allocate nodes array storing heap
  heap->nodes = (HeapNode**)malloc(size * sizeof(HeapNode*));
  if(!heap->nodes)
  {
    fprintf(stderr, "Failed allocating nodes in heap.\n");
    return NULL;
  }
  heap->capacity = size;
  heap->heap_size = 0;
  return heap;
}

HeapNode *createHeapNode(int vertexInd, int distance)
{
  HeapNode *node = (HeapNode*)malloc(sizeof(HeapNode));
  if(!node)
  {
    fprintf(stderr, "Error in Heap.c - createHeapNode(): Memory allocation error.\n");
    return NULL;
  }
  node->vertexInd = vertexInd;
  node->distance = distance;
  return node;
}

Heap* insert(Heap* heap, int vertexInd, int distance)
{
  if(!heap)
  {
    fprintf(stderr, "Error in Heap.c - insert(): Null heap passed.\n");
    return NULL;
  }
  if(heap->heap_size == heap->capacity)
  {
    fprintf(stderr, "Error in Heap.c - insert(): Heap overflow.\n");
    return NULL;
  }
  // create new node and add to heap
  HeapNode *node = createHeapNode(vertexInd, distance);
  heap->nodes[heap->heap_size++] = node;
  return heap;
}

int leftChild(Heap* heap, int i)
{
  int left = 2 * i + 1;
  return (left < heap->heap_size) ? left : -1;
}

int rightChild(Heap* heap, int i)
{
  int right = 2 * i + 2;
  return (right < heap->heap_size) ? right : -1;
}

int parent(Heap* heap, int i)
{
  if(i < 0 || i > heap->heap_size)
    return -1;
  if(i == 0)
    return 0;
  return (i - 1) / 2;
}

void printHeap(Heap* heap, Graph *g)
{
  printf("[");
  for(int i = 0; i < heap->heap_size; i++)
  {
    printf(" %c/%d ", g->vertexLabels[heap->nodes[i]->vertexInd], heap->nodes[i]->distance);
  }
  printf("]\n");
}

void freeHeap(Heap* heap)
{
  if(heap)
  {
    // free each node first then free the array and the whole heap
    for(int i = 0; i < heap->heap_size; i++)
    {
      if(heap->nodes[i])
        free(heap->nodes[i]);
    }
    free(heap->nodes);
    free(heap);
  }
}

void freeHeapNode(HeapNode *node)
{
  if(node)
    free(node);
}

// min-priority queue methods:
void MinHeapify(Heap* heap, int i)
{
  int L = leftChild(heap, i);
  int R = rightChild(heap, i);
  int smallest = i;
  HeapNode *temp;

  // compare children of A[i] to A[i]. we can assume a distance of -1 (in this
  // case) is an infinite distance, so it is safe to ignore
  if((L != -1) && (heap->nodes[L]->distance < heap->nodes[smallest]->distance))
    smallest = L;
  if((R != -1) && (heap->nodes[R]->distance < heap->nodes[smallest]->distance))
    smallest = R;

  // Cast min heapify if a swap with a child. This is done to ensure
  // the min-heap property of the descendent tree remains true.
  if(smallest != i)
  {
    // swap
    temp = heap->nodes[i];
    heap->nodes[i] = heap->nodes[smallest];
    heap->nodes[smallest] = temp;
    // recur into next level
    MinHeapify(heap, smallest);
  }
}

static int findIndex(Heap *heap, int vertexInd)
{
  for(int i = 0; i < heap->heap_size; i++)
    if(heap->nodes[i]->vertexInd == vertexInd)
      return i;

  return -1;
}

void MinHeap_DecreaseKey(Heap *heap, int vertexInd, int newDist)
{
  // first find the corresponding node
  int i = findIndex(heap, vertexInd);
  if(i == -1)
  {
    fprintf(stderr, "Error in Graph.c: decreaseKey() - Vertex not found in heap.\n");
    return;
  }
  if(newDist > heap->nodes[i]->distance)
  {
    fprintf(stderr, "Error in Graph.c: decreaseKey() - new key is larger.\n");
    return;
  }

  heap->nodes[i]->distance = newDist;

  // bubble the newly decreased node upward the heap
  while(i > 0 && heap->nodes[parent(heap, i)]->distance > heap->nodes[i]->distance)
  {
    // propagate upward
    HeapNode *temp = heap->nodes[i];
    heap->nodes[i] = heap->nodes[parent(heap,i)];
    heap->nodes[parent(heap, i)] = temp;
    i = parent(heap, i);
  }

}

void MinHeap_Insert(Heap *heap, int vertexInd, int distance)
{
  if(!heap)
  {
    fprintf(stderr, "Error in MinHeap_Insert(): Null heap passed.\n");
    return;
  }

  // insert normally and bubble upward to satisfy min heap property
  if(insert(heap, vertexInd, distance))
  {
    int i = heap->heap_size - 1;      // where the node was installed
    while(i > 0 && (heap->nodes[parent(heap,i)]->distance > heap->nodes[i]->distance))
    {
      // swap with parent
      HeapNode *temp = heap->nodes[i];
      heap->nodes[i] = heap->nodes[parent(heap,i)];
      heap->nodes[parent(heap, i)] = temp;
      i = parent(heap, i);
    }
  }
}

HeapNode *MinHeap_Minimum(Heap *heap)
{
  if(!heap)
  {
    fprintf(stderr, "Error in Heap.c - MinHeap_Minimum(): Null heap passed.\n");
    return NULL;
  }
  if(heap->heap_size < 0)
  {
    fprintf(stderr, "Error in Heap.c - MinHeap_Minimum(): Heap underflow.\n");
    return NULL;
  }
  return heap->nodes[0];
}

HeapNode *MinHeap_ExtractMin(Heap *heap)
{
  if (heap->heap_size <= 0) {
    fprintf(stderr, "Error in Heap.c - MinHeap_ExtractMin(): Heap underflow.\n");
    return NULL;
  }

  HeapNode *minNode = heap->nodes[0];
  heap->nodes[0] = heap->nodes[--heap->heap_size];
  MinHeapify(heap, 0);
  return minNode;
}