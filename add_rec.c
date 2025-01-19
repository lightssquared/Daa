#include <stdio.h>
#include <stdlib.h>

void addMatricesRecursive(int rows, int cols, int **A, int **B, int **result, int i, int j) {
    // Base case: If we've added all elements
    if (i == rows) return;

    // If we haven't reached the end of the current row, add the current element
    if (j < cols) {
        result[i][j] = A[i][j] + B[i][j];
        addMatricesRecursive(rows, cols, A, B, result, i, j + 1);
    }
    // Move to the next row once the current row is done
    else {
        addMatricesRecursive(rows, cols, A, B, result, i + 1, 0);
    }
}

void printMatrix(int rows, int cols, int **matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rows, cols;

    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    // Dynamically allocate memory for matrices
    int **A = (int **)malloc(rows * sizeof(int *));
    int **B = (int **)malloc(rows * sizeof(int *));
    int **result = (int **)malloc(rows * sizeof(int *));
    
    // Allocating memory for each row in the matrices
    for (int i = 0; i < rows; i++) {
        A[i] = (int *)malloc(cols * sizeof(int));
        B[i] = (int *)malloc(cols * sizeof(int));
        result[i] = (int *)malloc(cols * sizeof(int));
    }

    printf("Enter elements of the first matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of the second matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // Add the matrices using recursion
    addMatricesRecursive(rows, cols, A, B, result, 0, 0);

    printf("Resultant matrix after addition:\n");
    printMatrix(rows, cols, result);

    // Free dynamically allocated memory
    for (int i = 0; i < rows; i++) {
        free(A[i]);
        free(B[i]);
        free(result[i]);
    }
    free(A);
    free(B);
    free(result);

    return 0;
}
