#include <stdio.h>
#include <stdlib.h>

void multiplyMatrices(int rowsA, int colsA, int **A, int rowsB, int colsB, int **B, int **result) {
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
            for (int k = 0; k < colsA; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
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

    // Multiply the matrices
    multiplyMatrices(rowsA, colsA, A, rowsB, colsB, B, result);

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
