#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Inorder traversal (Left, Root, Right)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);   // Visit left subtree
        printf("%d ", root->data); // Visit root
        inorder(root->right);  // Visit right subtree
    }
}

// Preorder traversal (Root, Left, Right)
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data); // Visit root
        preorder(root->left);   // Visit left subtree
        preorder(root->right);  // Visit right subtree
    }
}

// Postorder traversal (Left, Right, Root)
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);  // Visit left subtree
        postorder(root->right); // Visit right subtree
        printf("%d ", root->data); // Visit root
    }
}

int main() {
    // Dynamically creating the binary tree nodes
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorder(root);
    printf("\n");

    // Freeing dynamically allocated memory
    free(root->left->left);
    free(root->left->right);
    free(root->right->left);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
