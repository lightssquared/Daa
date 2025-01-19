#include <stdio.h>
#include <stdlib.h>

// Structure for the adjacency list node
struct Node {
    int vertex;
    struct Node* next;
};

// Structure for the graph
struct Graph {
    int V; // Number of vertices
    struct Node** adjList; // Adjacency list
};

// Function to create a new adjacency list node
struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    if (graph == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    graph->V = V;
    graph->adjList = (struct Node**)malloc(V * sizeof(struct Node*));
    if (graph->adjList == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < V; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

// Function to add an edge to the graph (undirected graph)
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// DFS function to generate the spanning tree
void DFS(struct Graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* adjList = graph->adjList[vertex];
    while (adjList != NULL) {
        int adjVertex = adjList->vertex;
        if (!visited[adjVertex]) {
            DFS(graph, adjVertex, visited);
        }
        adjList = adjList->next;
    }
}

int main() {
    int V = 6;  // Number of vertices in the graph
    struct Graph* graph = createGraph(V);

    // Add edges to the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);

    // Array to track visited vertices
    int* visited = (int*)malloc(V * sizeof(int));
    if (visited == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Initialize visited array
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }

    printf("Spanning Tree (DFS traversal): ");
    DFS(graph, 0, visited);  // Starting DFS from vertex 0
    printf("\n");

    free(visited);
    return 0;
}
