#include <stdio.h>
#include <stdlib.h>

#define INF 9999
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

  // Output: Cost matrix
  for (i=0; i<nodes; i++) {
    for(j=0; j<nodes; j++) {
      printf("%d\t", costMatrix[i][j]);
    }
    printf("\n");
  }

  // Routing algorithm
  int updated;
  do {
    updated = 0;
      for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
          for (k = 0; k < nodes; k++) {
            if (rt[i].distance[k] != INF && costMatrix[k][j] != INF) {
              if (rt[i].distance[j] > rt[i].distance[k] + costMatrix[k][j]) {
                rt[i].distance[j] = rt[i].distance[k] + costMatrix[k][j];
                rt[i].nextHop[j] = k;
                updated = 1;
              } 
            } 
          } // k loop
        } // j loop
      } // i loop
    } while (updated); 
  
    // Output: Final Routing Tables
    printf("\nRouting Tables after Convergence:\n");
    for (i = 0; i < nodes; i++) {
      printf("\nRouter %d:\n", i);
      printf("Destination\tNext Hop\tDistance\n");
      for (j = 0; j < nodes; j++) {
        if (rt[i].distance[j] == INF) {
          printf("%d\t\t-\t\tINF\n", j);
        } else {
          printf("%d\t\t%d\t\t%d\n", j, rt[i].distance[j], rt[i].nextHop[j]);
        } 
      } //j loop
    } //i loop
  return 0;
}
