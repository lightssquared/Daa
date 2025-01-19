#include <stdio.h>
#include <stdlib.h>

// Function to find the vertex with the minimum distance
int minDistance(int dist[], int sptSet[], int V) {
    int min = 1000000;  // Use a large value to represent infinity
    int minIndex = -1;

    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function to implement Dijkstra's algorithm
void dijkstra(int graph[][5], int src, int V) {
    int dist[V];  // Array to store shortest distance from source
    int sptSet[V]; // Shortest path tree set (to track vertices already processed)

    // Initialize all distances to a large value (infinity)
    for (int i = 0; i < V; i++) {
        dist[i] = 1000000; // Large value to simulate infinity
        sptSet[i] = 0;     // All vertices are initially not included in the shortest path tree
    }

    dist[src] = 0;  // Distance from the source to itself is always 0

    // Calculate the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Select the vertex with the minimum distance
        int u = minDistance(dist, sptSet, V);
        
        // Mark the selected vertex as processed
        sptSet[u] = 1;

        // Update the distance value of the adjacent vertices of the selected vertex
        for (int v = 0; v < V; v++) {
            // Update dist[v] if the current distance is smaller and v is not in the shortest path tree
            if (!sptSet[v] && graph[u][v] && dist[u] != 1000000 && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the shortest distance from the source to all vertices
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] == 1000000) {
            printf("%d \t\t INF\n", i);
        } else {
            printf("%d \t--->\t %d\n", i, dist[i]);
        }
    }
}

int main() {
    // Example graph represented as an adjacency matrix
    // 5 vertices: 0, 1, 2, 3, 4
    int graph[5][5] = {
        {0, 10, 0, 0, 0},
        {10, 0, 20, 0, 0},
        {0, 20, 0, 10, 10},
        {0, 0, 10, 0, 30},
        {0, 0, 10, 30, 0}
    };

    // Run Dijkstra's algorithm starting from vertex 0
    dijkstra(graph, 0, 5);

    return 0;
}
