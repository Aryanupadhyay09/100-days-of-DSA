#include <stdio.h>
#include <stdlib.h>

// Node structure for adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

int main() {
    int n, m, u, v, directed;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &m);
    printf("Is the graph directed? (1 for Yes, 0 for No): ");
    scanf("%d", &directed);

    // Array of adjacency lists
    struct Node* adj[n];
    for(int i = 0; i < n; i++) {
        adj[i] = NULL;
    }

    // Input edges
    for(int i = 0; i < m; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);

        // Add v to u's list
        struct Node* newNode = createNode(v);
        newNode->next = adj[u];
        adj[u] = newNode;

        // If undirected, add u to v's list
        if(!directed) {
            newNode = createNode(u);
            newNode->next = adj[v];
            adj[v] = newNode;
        }
    }

    // Print adjacency list
    printf("Adjacency List:\n");
    for(int i = 0; i < n; i++) {
        printf("%d -> ", i);
        struct Node* temp = adj[i];
        while(temp) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }

    return 0;
}
