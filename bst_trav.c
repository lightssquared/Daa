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

// Function to insert a node in the BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);  // Insert in the left subtree
    } else if (data > root->data) {
        root->right = insert(root->right, data);  // Insert in the right subtree
    }

    return root;
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
    struct Node* root = NULL;

    // Creating a binary search tree
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorder(root);
    printf("\n");

    // Freeing dynamically allocated memory (optional)
    // Freeing the tree nodes would require a postorder traversal to properly delete nodes.
    return 0;
}
