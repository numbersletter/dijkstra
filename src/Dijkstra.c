#include "Dijkstra.h"
#include "Graph.h"
#include <limits.h>

void InitializeSingleSource(Graph *g, int srcVertex)
{
  if(!checkGraph(g, "Error in Dijkstra.c : InitializeSingleSource - Graph is NULL.\n"))
    return;

  // initialize single source cost array in g with the given source vertex
  for(int i = 0; i < g->vertexCnt; i++)
  {
    if(i != srcVertex)
      g->singleSourceCosts[i] = INT_MAX;     // infinite cost at the start
    else
      g->singleSourceCosts[i] = 0;
  }
}

void Dijkstra(Graph *g, int srcVertexInd)
{
  // initialize the single-source min distance array and the minimum priority
  // queue (which is the heap)
  g->sourceInd = srcVertexInd;
  InitializeSingleSource(g, srcVertexInd);
  Heap *heap = createHeap(g->vertexCnt);
  for(int i = 0; i < g->vertexCnt; i++)
    MinHeap_Insert(heap, i, g->singleSourceCosts[i]);

  while(heap->heap_size > 0)
  {
    // newly discovered node with min distance
    HeapNode *extractedVertex = MinHeap_ExtractMin(heap);

    // update the single source cost
    g->singleSourceCosts[extractedVertex->vertexInd] = extractedVertex->distance;

    // iterate over adjacent vertices
    for(int i = 0; i < g->vertexCnt; i++)
    {
      if(edgeExists(g, extractedVertex->vertexInd, i))
        if(Dijkstra_Relax(g, extractedVertex->vertexInd, i))
          MinHeap_DecreaseKey(heap, i, g->singleSourceCosts[i]);
    }
  }
  freeHeap(heap);
}

int Dijkstra_Relax(Graph *g, int srcVertex, int adjVertex)
{
  // relax the cost to get to adjVertex only if it's distance is infinite
  // or if the src_dist + weight < the current distance at adj.
  if(g->singleSourceCosts[adjVertex] == INT_MAX || (g->singleSourceCosts[srcVertex] + getWeight(g, srcVertex, adjVertex) < g->singleSourceCosts[adjVertex]))
  {
    g->singleSourceCosts[adjVertex] = g->singleSourceCosts[srcVertex] + getWeight(g, srcVertex, adjVertex);
    return 1;
  }
  return 0;
}