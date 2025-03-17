#include <stdio.h>
#include "Graph.h"

Graph* createGraph() {
  Graph *g = (Graph*)malloc(sizeof(Graph));
  if (!g) {
    fprintf(stderr, "Error in Graph.c: createGraph() - Memory allocation failed for graph.\n");
    exit(EXIT_FAILURE);
  }
  g->vertexCnt = 0;
  for (int i = 0; i < MAX_VERTICES; i++) {
    for (int j = 0; j < MAX_VERTICES; j++) {
      g->adjacencyMatrix[i][j] = 0; // No edges initially
    }
    g->vertexLabels[i] = '\0';
  }
  return g;
}

void freeGraph(Graph *g) {
  if (!g) {
    fprintf(stderr, "Error in Graph.c: freeGraph() - Graph is NULL.\n");
    return;
  }
  free(g);
}

void addVertex(Graph *g, char label) {
  if (!g) {
    fprintf(stderr, "Error in Graph.c: addVertex() - Graph is NULL.\n");
    return;
  }
  // add the vertex if there's space left in the graph and increment
  // vertex cnt after insert
  if (g->vertexCnt < MAX_VERTICES)
    g->vertexLabels[g->vertexCnt++] = label;
  else
    fprintf(stderr, "Error in Graph.c: addVertex() - Maximum vertex limit reached.\n");
}

void addEdge(Graph *g, int vertexU, int vertexV, int weight)
{
  if (!g)
  {
    fprintf(stderr, "Error in Graph.c: addEdge() - Graph is NULL.\n");
    return;
  }
  if (vertexU < g->vertexCnt && vertexV < g->vertexCnt)
  {
    g->adjacencyMatrix[vertexU][vertexV] = weight;
    g->adjacencyMatrix[vertexV][vertexU] = weight; // Undirected graph
  } else
    fprintf(stderr, "Error in Graph.c: addEdge() - Invalid vertex index.\n");
}

void deleteEdge(Graph *g, int vertexU, int vertexV)
{
  if (!g)
  {
    fprintf(stderr, "Error in Graph.c: deleteEdge() - Graph is NULL.\n");
    return;
  }
  if (vertexU < g->vertexCnt && vertexV < g->vertexCnt)
  {
    g->adjacencyMatrix[vertexU][vertexV] = 0;
    g->adjacencyMatrix[vertexV][vertexU] = 0;
  } else
    fprintf(stderr, "Error in Graph.c: deleteEdge() - Invalid vertex index.\n");
}

void printGraph(Graph *g)
{
  if (!g)
  {
    fprintf(stderr, "Error in Graph.c: printGraph() - Graph is NULL.\n");
    return;
  }
  printf("  ");
  for (int i = 0; i < g->vertexCnt; i++)
    printf(" %c", g->vertexLabels[i]);

  printf("\n");

  for (int i = 0; i < g->vertexCnt; i++)
  {
    printf("%c ", g->vertexLabels[i]);
    for (int j = 0; j < g->vertexCnt; j++)
      printf(" %d", g->adjacencyMatrix[i][j]);
    printf("\n");
  }
}

int getWeight(Graph *g, int vertexU, int vertexV)
{
  if(!g)
  {
    fprintf(stderr, "Error in Graph.c: getWeight() - Graph is NULL.\n");
    return 0;
  }
  if(vertexU < 0 || vertexU >= g->vertexCnt || vertexV < 0 || vertexV >= g->vertexCnt)
  {
    fprintf(stderr, "Error in Graph.c: getWeight() - invalid vertex indices.\n");
    return 0;
  }
  return g->adjacencyMatrix[vertexU][vertexV];
}

int edgeExists(Graph *g, int vertexU, int vertexV)
{
  if(!g)
  {
    fprintf(stderr, "Error in Graph.c: edgeExists() - Graph is NULL.\n");
    return 0;
  }
  if(vertexU < 0 || vertexU >= g->vertexCnt || vertexV < 0 || vertexV >= g->vertexCnt)
  {
    fprintf(stderr, "Error in Graph.c: edgeExists() - invalid vertex indices.\n");
    return 0;
  }

  if(g->adjacencyMatrix[vertexU][vertexV] != 0)
    return 1;
  return 0;
}



// error reporting
int checkGraph(Graph *g, char *error_msg)
{
  if (!g)
  {
    fprintf(stderr, "%s", error_msg);
    return 0;
  }
  return 1;
}