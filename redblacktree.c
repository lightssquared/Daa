#include <stdio.h>
#include <stdlib.h>

// Define colors for the Red-Black Tree nodes
#define RED 1
#define BLACK 0

// Define the structure for a Red-Black Tree Node
struct Node {
    int data;                 // Data stored in the node
    int color;                // Node color: RED or BLACK
    struct Node *left, *right, *parent; // Pointers to child and parent nodes
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->color = RED; // New nodes are initially RED
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

// Function to perform a left rotation
void leftRotate(struct Node** root, struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;

    if (y->left != NULL) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

// Function to perform a right rotation
void rightRotate(struct Node** root, struct Node* y) {
    struct Node* x = y->left;
    y->left = x->right;

    if (x->right != NULL) {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == NULL) {
        *root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}

// Fix violations of Red-Black Tree properties after insertion
void fixInsertion(struct Node** root, struct Node* z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            struct Node* y = z->parent->parent->right; // Uncle node
            if (y != NULL && y->color == RED) {
                // Case 1: Uncle is RED
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // Case 2: z is a right child
                    z = z->parent;
                    leftRotate(root, z);
                }
                // Case 3: z is a left child
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            struct Node* y = z->parent->parent->left; // Uncle node
            if (y != NULL && y->color == RED) {
                // Case 1: Uncle is RED
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    // Case 2: z is a left child
                    z = z->parent;
                    rightRotate(root, z);
                }
                // Case 3: z is a right child
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

// Function to insert a new node into the Red-Black Tree
void insert(struct Node** root, int data) {
    struct Node* newNode = createNode(data);
    struct Node* y = NULL;
    struct Node* x = *root;

    // Standard Binary Search Tree insertion
    while (x != NULL) {
        y = x;
        if (newNode->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    newNode->parent = y;

    if (y == NULL) {
        *root = newNode; // Tree was empty
    } else if (newNode->data < y->data) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }

    // Fix Red-Black Tree violations
    fixInsertion(root, newNode);
}

// Function to find the minimum node in a subtree
struct Node* findMin(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Fix violations of Red-Black Tree properties after deletion
void fixDeletion(struct Node** root, struct Node* x) {
    while (x != *root && (x == NULL || x->color == BLACK)) {
        if (x == x->parent->left) {
            struct Node* w = x->parent->right; // Sibling node
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == BLACK) &&
                (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == NULL || w->right->color == BLACK) {
                    if (w->left != NULL) w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != NULL) w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            struct Node* w = x->parent->left; // Sibling node
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if ((w->right == NULL || w->right->color == BLACK) &&
                (w->left == NULL || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == NULL || w->left->color == BLACK) {
                    if (w->right != NULL) w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != NULL) w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    if (x != NULL) x->color = BLACK;
}

// Function to delete a node from the Red-Black Tree
void deleteNode(struct Node** root, int data) {
    // Find the node to delete
    struct Node* z = *root;
    struct Node* y;
    struct Node* x;
    while (z != NULL && z->data != data) {
        if (data < z->data) {
            z = z->left;
        } else {
            z = z->right;
        }
    }

    if (z == NULL) {
        printf("Node not found in the tree.\n");
        return;
    }

    y = z;
    int yOriginalColor = y->color;

    if (z->left == NULL) {
        x = z->right;
        if (z->parent == NULL) {
            *root = x;
        } else if (z == z->parent->left) {
            z->parent->left = x;
        } else {
            z->parent->right = x;
        }
        if (x != NULL) x->parent = z->parent;
    } else if (z->right == NULL) {
        x = z->left;
        if (z->parent == NULL) {
            *root = x;
        } else if (z == z->parent->left) {
            z->parent->left = x;
        } else {
            z->parent->right = x;
        }
        if (x != NULL) x->parent = z->parent;
    } else {
        y = findMin(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL) x->parent = y;
        } else {
            if (y->parent != NULL) y->parent->left = x;
            if (x != NULL) x->parent = y->parent;
            y->right = z->right;
            if (z->right != NULL) z->right->parent = y;
        }
        if (z->parent == NULL) {
            *root = y;
        } else if (z == z->parent->left) {
            z->parent->left = y;
        } else {
            z->parent->right = y;
        }
        y->parent = z->parent;
        y->left = z->left;
        if (z->left != NULL) z->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK && x != NULL) {
        fixDeletion(root, x);
    }

    free(z);
}

// In-order traversal of the Red-Black Tree
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    struct Node* root = NULL;

    int choice, value;
    do {
        printf("\nRed-Black Tree Menu:\n");
        printf("1. Insert\n2. Delete\n3. Display (In-order Traversal)\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            insert(&root, value);
            break;
        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            deleteNode(&root, value);
            break;
        case 3:
            printf("In-order Traversal: ");
            inorderTraversal(root);
            printf("\n");
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
