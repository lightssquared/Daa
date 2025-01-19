#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000  // A large number to represent infinity

void matrixChainOrder(int *p, int n) {
    // Create a table to store the minimum number of multiplications
    int **m = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        m[i] = (int *)malloc(n * sizeof(int));
    }

    // Cost is zero when multiplying one matrix (diagonal elements are 0)
    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    // Chain length l is the subproblem size
    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INF;  // Initialize with a large number
            for (int k = i; k < j; k++) {
                // q is the cost of multiplying the two subchains
                int q = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                }
            }
        }
    }

    // The result is in m[1][n-1], i.e., the minimum number of multiplications
    printf("Minimum number of multiplications is %d\n", m[1][n-1]);

    // Free dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(m[i]);
    }
    free(m);
}

int main() {
    int n;

    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    int *p = (int *)malloc((n + 1) * sizeof(int));

    printf("Enter the dimensions of the matrices:\n");
    for (int i = 0; i < n + 1; i++) {
        scanf("%d", &p[i]);
    }

    // Call the matrix chain multiplication function
    matrixChainOrder(p, n);

    // Free dynamically allocated memory
    free(p);

    return 0;
}
