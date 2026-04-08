#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Adjacency list node
struct Node {
    int vertex;
    struct Node* next;
};

// Graph structure
struct Graph {
    int V;
    struct Node** adj;
};

// Create a new node
struct Node* newNode(int v) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->vertex = v;
    node->next = NULL;
    return node;
}

// Create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adj = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; i++) {
        graph->adj[i] = NULL;
    }
    return graph;
}

// Add edge u -> v
void addEdge(struct Graph* graph, int u, int v) {
    struct Node* node = newNode(v);
    node->next = graph->adj[u];
    graph->adj[u] = node;
}

// DFS utility
void dfsUtil(struct Graph* graph, int v, bool visited[], int stack[], int* top) {
    visited[v] = true;

    struct Node* temp = graph->adj[v];
    while (temp != NULL) {
        if (!visited[temp->vertex]) {
            dfsUtil(graph, temp->vertex, visited, stack, top);
        }
        temp = temp->next;
    }

    stack[(*top)++] = v;  // push to stack
}

// Topological Sort
void topologicalSort(struct Graph* graph) {
    int V = graph->V;
    bool visited[V];
    for (int i = 0; i < V; i++) visited[i] = false;

    int stack[V];
    int top = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfsUtil(graph, i, visited, stack, &top);
        }
    }

    // Print in reverse order
    for (int i = top - 1; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

// Driver code
int main() {
    struct Graph* graph = createGraph(6);
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    printf("Topological Sort of the given DAG:\n");
    topologicalSort(graph);

    return 0;
}
