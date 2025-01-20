#include <stdio.h>
#include <stdlib.h>

#define INF 1000000  // A large value representing infinity

// Function to print the shortest distance matrix
void printMatrix(int** dist, int V) {
    printf("Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) {
                printf("INF\t");
            } else {
                printf("%d\t", dist[i][j]);
            }
        }
        printf("\n");
    }
}

// Function to implement Floyd-Warshall algorithm
void floydWarshall(int** graph, int V) {
    // Allocate memory for the distance matrix
    int** dist = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        dist[i] = (int*)malloc(V * sizeof(int));
    }

    // Initialize the distance matrix with the input graph values
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Main Floyd-Warshall algorithm
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the shortest distance matrix
    printMatrix(dist, V);

    // Free allocated memory for the distance matrix
    for (int i = 0; i < V; i++) {
        free(dist[i]);
    }
    free(dist);
}

int main() {
    int V;

    // Input the number of vertices
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    // Dynamically allocate memory for the graph
    int** graph = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int));
    }

    // Input the graph as an adjacency matrix
    printf("Enter the adjacency matrix (use %d for infinity):\n", INF);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Run Floyd-Warshall algorithm
    floydWarshall(graph, V);

    // Free allocated memory for the graph
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
