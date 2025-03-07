#include <stdio.h>

#define MAX_NODES 10
#define INF 9999

struct RoutingTable {
    int distance[MAX_NODES];
    int next_hop[MAX_NODES];
};

int num_nodes;
int cost_matrix[MAX_NODES][MAX_NODES];
struct RoutingTable routing_table[MAX_NODES];

void initialize() {
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            cost_matrix[i][j] = (i == j) ? 0 : INF;
            routing_table[i].distance[j] = cost_matrix[i][j];
            routing_table[i].next_hop[j] = (cost_matrix[i][j] != INF) ? j : -1;
        }
    }
}

void input_router_data() {
    printf("Enter the number of routers: ");
    scanf("%d", &num_nodes);
    
    printf("Enter the cost matrix (%d x %d):\n", num_nodes, num_nodes);
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            printf("Enter cost from router %d to router %d: ", i, j);
            scanf("%d", &cost_matrix[i][j]);
            if (i != j && cost_matrix[i][j] == 0)
                cost_matrix[i][j] = INF;
            routing_table[i].distance[j] = cost_matrix[i][j];
            routing_table[i].next_hop[j] = (cost_matrix[i][j] != INF) ? j : -1;
        }
    }
}

void distance_vector_routing() {
    int updated;
    do {
        updated = 0;
        for (int i = 0; i < num_nodes; i++) {
            for (int j = 0; j < num_nodes; j++) {
                for (int k = 0; k < num_nodes; k++) {
                    if (routing_table[i].distance[k] > cost_matrix[i][j] + routing_table[j].distance[k]) {
                        routing_table[i].distance[k] = cost_matrix[i][j] + routing_table[j].distance[k];
                        routing_table[i].next_hop[k] = j;
                        updated = 1;
                    }
                }
            }
        }
    } while (updated);
}

void print_routing_tables() {
    for (int i = 0; i < num_nodes; i++) {
        printf("Routing table for router %d:\n", i);
        printf("Destination\tDistance\tNext Hop\n");
        for (int j = 0; j < num_nodes; j++) {
            printf("%d\t\t%d\t\t%d\n", j, routing_table[i].distance[j], routing_table[i].next_hop[j]);
        }
        printf("\n");
    }
}

int main() {
    input_router_data();
    initialize();
    distance_vector_routing();
    print_routing_tables();
    
    return 0;
}
