#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

#define MAX_VERTICES 26

/*
 * Graph G implemented using an adjacency matrix where each element (u,v) in the
 * matrix represents a connected edge between vertices u and v. In particular,
 * labels can be assigned to these vertices inside vertexLabels. The value
 * in the adjacency matrix can be weight of the edge between the given
 * two vertices. Both the weight and the inherent edge connections are
 * summarized by the adjacency matrix.
 */
typedef struct {
  int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES]; // Stores edge weights
  char vertexLabels[MAX_VERTICES]; // Maps indices to characters
  int vertexCnt; // Current number of vertices

  int singleSourceCosts[MAX_VERTICES];  // stores min distance wrt a source
  int sourceInd;

} Graph;

// to be used in Heap
typedef struct {
  int vertexInd;
  int cost;
} Vertex;

/*
 * Create and initialize a new graph
 */
Graph* createGraph();

/*
 * Free the graph from memory.
 */
void freeGraph(Graph *g);

/*
 * Add a vertex with the given label to the graph which simply adds the
 * character to the vertex labels array (so no connections).
 */
void addVertex(Graph *g, char label);

/*
 * Complete an edge between two vertices indexed by U and V with the given
 * weight between the vertices (this is an undirected graph so both directions
 * are set).
 */
void addEdge(Graph *g, int vertexU, int vertexV, int weight);

/*
 * Deletes the edge between vertex U and vertex V. This amounts to setting
 * the adjacency matrix value at these indices to 0.
 */
void deleteEdge(Graph *g, int vertexU, int vertexV);

/*
 * Prints the graph which amounts to printing the adjacency matrix.
 * Any '0' element represents no connection between the corresponding
 * vertices.
 */
void printGraph(Graph *g);

/*
 * Returns the weight between the two vertices.
 */
int getWeight(Graph *g, int vertexU, int vertexV);

/*
 * Returns 1 if there is a connection between the two vertices. Returns
 * 0 otherwise.
 */
int edgeExists(Graph *g, int vertexU, int vertexV);

// error reporting
int checkGraph(Graph *g, char *error_msg);

#endif