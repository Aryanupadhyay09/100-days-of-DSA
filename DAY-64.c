#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Queue structure
struct Queue {
    int items[100];
    int front, rear;
};

// Create a new node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Initialize queue
void initQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// Check if queue is empty
bool isEmpty(struct Queue* q) {
    return q->front == -1;
}

// Enqueue
void enqueue(struct Queue* q, int value) {
    if(q->rear == 99) return; // queue full
    if(q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

// Dequeue
int dequeue(struct Queue* q) {
    if(isEmpty(q)) return -1;
    int item = q->items[q->front];
    if(q->front >= q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}

// BFS function
void BFS(struct Node* adj[], int n, int source) {
    bool visited[n];
    for(int i = 0; i < n; i++) visited[i] = false;

    struct Queue q;
    initQueue(&q);

    visited[source] = true;
    enqueue(&q, source);

    printf("BFS Traversal: ");
    while(!isEmpty(&q)) {
        int u = dequeue(&q);
        printf("%d ", u);

        struct Node* temp = adj[u];
        while(temp) {
            int v = temp->vertex;
            if(!visited[v]) {
                visited[v] = true;
                enqueue(&q, v);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

int main() {
    int n, m, u, v;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &m);

    struct Node* adj[n];
    for(int i = 0; i < n; i++) adj[i] = NULL;

    printf("Enter edges (u v):\n");
    for(int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        struct Node* newNode = createNode(v);
        newNode->next = adj[u];
        adj[u] = newNode;

        // For undirected graph, add reverse edge
        newNode = createNode(u);
        newNode->next = adj[v];
        adj[v] = newNode;
    }

    int source;
    printf("Enter source vertex: ");
    scanf("%d", &source);

    BFS(adj, n, source);

    return 0;
}
