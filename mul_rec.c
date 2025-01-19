#include <stdio.h>
#include <stdlib.h>

void multiplyMatricesRecursive(int rowsA, int colsA, int **A, int rowsB, int colsB, int **B, int **result, int i, int j, int k) {
    // Base case: If all rows and columns are processed
    if (i == rowsA) return;
    
    // If all columns in the current row are processed
    if (j == colsB) {
        multiplyMatricesRecursive(rowsA, colsA, A, rowsB, colsB, B, result, i + 1, 0, 0);
        return;
    }

    // If all elements in the current row-column pair are processed
    if (k == colsA) {
        multiplyMatricesRecursive(rowsA, colsA, A, rowsB, colsB, B, result, i, j + 1, 0);
        return;
    }

    // Recursively calculate the result for the current position
    result[i][j] += A[i][k] * B[k][j];

    // Move to the next element in the current row-column
    multiplyMatricesRecursive(rowsA, colsA, A, rowsB, colsB, B, result, i, j, k + 1);
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
    int rowsA, colsA, rowsB, colsB;

    printf("Enter the number of rows and columns for matrix A: ");
    scanf("%d %d", &rowsA, &colsA);

    printf("Enter the number of rows and columns for matrix B: ");
    scanf("%d %d", &rowsB, &colsB);

    // Matrix multiplication is only possible if colsA == rowsB
    if (colsA != rowsB) {
        printf("Matrix multiplication is not possible: number of columns in A must equal number of rows in B.\n");
        return 0;
    }

    // Dynamically allocate memory for matrices
    int **A = (int **)malloc(rowsA * sizeof(int *));
    int **B = (int **)malloc(rowsB * sizeof(int *));
    int **result = (int **)malloc(rowsA * sizeof(int *));
    
    // Allocating memory for each row in the matrices
    for (int i = 0; i < rowsA; i++) {
        A[i] = (int *)malloc(colsA * sizeof(int));
    }
    for (int i = 0; i < rowsB; i++) {
        B[i] = (int *)malloc(colsB * sizeof(int));
    }
    for (int i = 0; i < rowsA; i++) {
        result[i] = (int *)malloc(colsB * sizeof(int));
    }

    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsA; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < rowsB; i++) {
        for (int j = 0; j < colsB; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // Initialize the result matrix with 0
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
        }
    }

    // Multiply the matrices using recursion
    multiplyMatricesRecursive(rowsA, colsA, A, rowsB, colsB, B, result, 0, 0, 0);

    printf("Resultant matrix after multiplication:\n");
    printMatrix(rowsA, colsB, result);

    // Free dynamically allocated memory
    for (int i = 0; i < rowsA; i++) {
        free(A[i]);
        free(result[i]);
    }
    for (int i = 0; i < rowsB; i++) {
        free(B[i]);
    }
    free(A);
    free(B);
    free(result);

    return 0;
}
