#include <stdio.h>
#include <stdlib.h>

#define INFINITY 9999
#define MAX_NODES 10

typedef struct {
  int distance[MAX_NODES];
  int nextHop[MAX_NODES];
} RoutingTable;

int main() {
  int nodes, i, j, k;
  RoutingTable rt[MAX_NODES];
  int costMatrix[MAX_NODES][MAX_NODES];

  // Input: Number of routers
  printf("Enter number of routers: ");
  scanf("%d", &nodes);

  // Input: Cost adjacency matrix
  printf("Enter the cost matrix: ");
  for (i = 0; i < nodes; i++) {
    for (j = 0; j < nodes; j++) {
      scanf("%d", &costMatrix[i][j]);
      if (i == j)
      costMatrix[i][j] = 0;
      rt[i].distance[j] = costMatrix[i][j];
      rt[i].nextHop[j] = (costMatrix[i][j] == INF) ? -1 : j;
    } 
  }
  return 0;
}
