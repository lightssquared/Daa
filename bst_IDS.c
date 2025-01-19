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

// Function to search for a value in the BST
struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;  // Data found or empty tree
    }

    if (data < root->data) {
        return search(root->left, data);  // Search in the left subtree
    }

    return search(root->right, data);  // Search in the right subtree
}

// Function to find the minimum node in a BST (for deletion)
struct Node* findMin(struct Node* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL) {
        return root;  // Tree is empty
    }

    if (data < root->data) {
        root->left = deleteNode(root->left, data);  // Delete from the left subtree
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);  // Delete from the right subtree
    } else {
        // Node to be deleted is found

        // Case 1: Node has only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 2: Node has two children
        struct Node* temp = findMin(root->right);  // Find the smallest node in the right subtree
        root->data = temp->data;  // Replace root's data with the smallest node in the right subtree
        root->right = deleteNode(root->right, temp->data);  // Delete the smallest node
    }

    return root;
}

// Function to display the BST in inorder (for visualization)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);   // Visit left subtree
        printf("%d ", root->data); // Visit root
        inorder(root->right);  // Visit right subtree
    }
}

int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert an element\n");
        printf("2. Delete an element\n");
        printf("3. Search for an element\n");
        printf("4. Display BST (Inorder Traversal)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Enter the value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Enter the value to search: ");
                scanf("%d", &value);
                struct Node* result = search(root, value);
                if (result != NULL) {
                    printf("Element %d found in the BST.\n", value);
                } else {
                    printf("Element %d not found in the BST.\n", value);
                }
                break;
            case 4:
                printf("BST Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
