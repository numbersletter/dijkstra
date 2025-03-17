#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include "Heap.h"

/*
 * This file shows the function prototypes to implement Dijkstra's minimum
 * cost algorithm for a graph. The weights of the graph are assumed to be
 * non-negative.
 */

/*
 * Initialize the single-source cost array in g (with respect to source vertex).
 */
void InitializeSingleSource(Graph *g, int srcVertex);

/*
 * Finds the minimum cost to traverse from the srcVertex to all other vertices
 * in graph g. The costs are stored in MinCost[] where each element at index
 * i is the cost to the ith vertex from the srcVertex.
 */
void Dijkstra(Graph *g, int srcVertex);

/*
 * Relaxes the cost between a source and one of its adjacent vertices.
 * This is accomplished by comparing the cost in MinCost to the one given in
 * the weight of the edge between the vertices in graph g.
 */
int Dijkstra_Relax(Graph *g, int srcVertex, int adjVertex);

#endif