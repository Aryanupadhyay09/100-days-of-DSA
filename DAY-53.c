#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define a node in the Binary Tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Queue structure for building tree from level-order
struct Queue {
    struct Node** arr;
    int front, rear, size;
};

// Create a new node
struct Node* newNode(int value) {
    if (value == -1) return NULL;  // NULL node
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = value;
    node->left = node->right = NULL;
    return node;
}

// Initialize queue
struct Queue* createQueue(int size) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->arr = (struct Node**)malloc(size * sizeof(struct Node*));
    q->front = q->rear = 0;
    q->size = size;
    return q;
}

// Enqueue
void enqueue(struct Queue* q, struct Node* node) {
    if (node != NULL) {
        q->arr[q->rear++] = node;
    }
}

// Dequeue
struct Node* dequeue(struct Queue* q) {
    if (q->front == q->rear) return NULL;
    return q->arr[q->front++];
}

// Build tree from level-order input
struct Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;

    struct Node* root = newNode(arr[0]);
    struct Queue* q = createQueue(n);
    enqueue(q, root);

    int i = 1;
    while (i < n) {
        struct Node* current = dequeue(q);
        if (current != NULL) {
            // Left child
            current->left = newNode(arr[i++]);
            enqueue(q, current->left);

            if (i < n) {
                // Right child
                current->right = newNode(arr[i++]);
                enqueue(q, current->right);
            }
        }
    }
    return root;
}

// Structure to store nodes with their horizontal distance
struct List {
    int data;
    int hd;
    struct List* next;
};

// Add node to list
void addNode(struct List** head, int data, int hd) {
    struct List* newNode = (struct List*)malloc(sizeof(struct List));
    newNode->data = data;
    newNode->hd = hd;
    newNode->next = *head;
    *head = newNode;
}

// Traverse tree and store nodes with horizontal distance
void storeNodes(struct Node* root, int hd, struct List** head) {
    if (root == NULL) return;

    addNode(head, root->data, hd);
    storeNodes(root->left, hd - 1, head);
    storeNodes(root->right, hd + 1, head);
}

// Print vertical order traversal
void printVerticalOrder(struct Node* root) {
    struct List* head = NULL;
    storeNodes(root, 0, &head);

    // Find min and max horizontal distance
    int minHD = INT_MAX, maxHD = INT_MIN;
    struct List* temp = head;
    while (temp != NULL) {
        if (temp->hd < minHD) minHD = temp->hd;
        if (temp->hd > maxHD) maxHD = temp->hd;
        temp = temp->next;
    }

    // Print nodes column by column
    for (int hd = minHD; hd <= maxHD; hd++) {
        temp = head;
        while (temp != NULL) {
            if (temp->hd == hd) {
                printf("%d ", temp->data);
            }
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int N;
    scanf("%d", &N);

    int arr[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    struct Node* root = buildTree(arr, N);
    printVerticalOrder(root);

    return 0;
}
