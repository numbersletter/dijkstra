#include "Dijkstra.h"
#include "Graph.h"
#include <stdio.h>

int main()
{
  // test by making a graph, adding some vertices, running dijkstra wrt a source
  // vertex and printing the resulting singleSourceCosts

  Graph *g = createGraph();
  addVertex(g, 'A');        // ind = 0
  addVertex(g, 'B');        // ind = 1
  addVertex(g, 'C');        // ind = 2
  addVertex(g, 'D');        // ind = 3
  addVertex(g, 'E');        // ind = 4
  addEdge(g, 0, 1, 7);      // A ~ B
  addEdge(g, 0, 4, 1);      // A ~ E
  addEdge(g, 1, 2, 3);      // B ~ C
  addEdge(g, 1, 4, 8);      // B ~ E
  addEdge(g, 2, 3, 6);      // C ~ D
  addEdge(g, 2, 4, 2);      // C ~ E
  addEdge(g, 3, 4, 7);      // D ~ E

  /*    b -- c
   *  / |  / |
   * a  | /  |
   *  \ e -- d
   */

  // select source as A and minimize paths
  Dijkstra(g, 0);
  // now print the resulting distances to each node
  printf("Minimum distances from A to each node:\n");
  for(int i = 0; i < g->vertexCnt; i++)
  {
    printf("%c : %d\n", g->vertexLabels[i], g->singleSourceCosts[i]);
  }

  freeGraph(g);
}