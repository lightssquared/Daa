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

// Inorder traversal (Left, Root, Right) for ascending order
void inorderAscending(struct Node* root) {
    if (root != NULL) {
        inorderAscending(root->left);   // Visit left subtree
        printf("%d ", root->data); // Visit root
        inorderAscending(root->right);  // Visit right subtree
    }
}

// Inorder traversal (Right, Root, Left) for descending order
void inorderDescending(struct Node* root) {
    if (root != NULL) {
        inorderDescending(root->right);   // Visit right subtree
        printf("%d ", root->data);  // Visit root
        inorderDescending(root->left);  // Visit left subtree
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

    // Displaying BST elements in ascending order
    printf("BST in Ascending Order: ");
    inorderAscending(root);
    printf("\n");

    // Displaying BST elements in descending order
    printf("BST in Descending Order: ");
    inorderDescending(root);
    printf("\n");

    return 0;
}
