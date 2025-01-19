#include <stdio.h>
#include <stdlib.h>

void subtractMatrices(int rows, int cols, int **A, int **B, int **result) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] - B[i][j];
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

    // Subtract the matrices
    subtractMatrices(rows, cols, A, B, result);

    printf("Resultant matrix after subtraction:\n");
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
