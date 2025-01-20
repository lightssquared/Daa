#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;         // Number of vertices and edges
    struct Edge* edge; // Array of edges
};

// Function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    if (!graph) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    if (!graph->edge) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    return graph;
}

// Function to implement Bellman-Ford algorithm
void bellmanFord(struct Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int* dist = (int*)malloc(V * sizeof(int));
    if (!dist) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Step 1: Initialize distances from src to all other vertices as a large value
    for (int i = 0; i < V; i++) {
        dist[i] = 1000000; // Use a large value to simulate infinity
    }
    dist[src] = 0;

    // Step 2: Relax all edges (V - 1) times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != 1000000 && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: Check for negative weight cycles
    for (int j = 0; j < E; j++) {
        int u = graph->edge[j].src;
        int v = graph->edge[j].dest;
        int weight = graph->edge[j].weight;
        if (dist[u] != 1000000 && dist[u] + weight < dist[v]) {
            printf("Graph contains a negative weight cycle\n");
            free(dist);
            return;
        }
    }

    // Print the distance from the source to all vertices
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] == 1000000) {
            printf("%d \t\t INF\n", i);
        } else {
            printf("%d \t\t %d\n", i, dist[i]);
        }
    }

    // Free allocated memory
    free(dist);
}

int main() {
    int V, E, src;

    // Input number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    // Create the graph
    struct Graph* graph = createGraph(V, E);

    // Input edges
    printf("Enter the edges in the format (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
    }

    // Input source vertex
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    // Run Bellman-Ford algorithm
    bellmanFord(graph, src);

    // Free allocated memory
    free(graph->edge);
    free(graph);

    return 0;
}
