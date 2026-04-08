#include <stdio.h>
#include <stdlib.h>

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

// Check if two subtrees are mirror images
int isMirror(struct Node* t1, struct Node* t2) {
    if (t1 == NULL && t2 == NULL) return 1;
    if (t1 == NULL || t2 == NULL) return 0;
    return (t1->data == t2->data) &&
           isMirror(t1->left, t2->right) &&
           isMirror(t1->right, t2->left);
}

// Check if tree is symmetric
int isSymmetric(struct Node* root) {
    if (root == NULL) return 1;
    return isMirror(root->left, root->right);
}

int main() {
    int N;
    scanf("%d", &N);

    int arr[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    struct Node* root = buildTree(arr, N);

    if (isSymmetric(root)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}
