#include <stdio.h>
#include <stdlib.h>

// Function to merge two halves of an array
void merge(int* array, int* tempArray, int left, int mid, int right) {
    int i = left;    // Starting index for left subarray
    int j = mid + 1; // Starting index for right subarray
    int k = left;    // Starting index to be sorted

    // Merge the two subarrays into tempArray[]
    while (i <= mid && j <= right) {
        if (array[i] <= array[j]) {
            tempArray[k] = array[i];
            i++;
        } else {
            tempArray[k] = array[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of the left subarray, if any
    while (i <= mid) {
        tempArray[k] = array[i];
        i++;
        k++;
    }

    // Copy the remaining elements of the right subarray, if any
    while (j <= right) {
        tempArray[k] = array[j];
        j++;
        k++;
    }

    // Copy the sorted subarray into the original array
    for (i = left; i <= right; i++) {
        array[i] = tempArray[i];
    }
}

// Function to implement merge sort
void mergeSort(int* array, int* tempArray, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        // Recursively sort the two halves
        mergeSort(array, tempArray, left, mid);
        mergeSort(array, tempArray, mid + 1, right);

        // Merge the sorted halves
        merge(array, tempArray, left, mid, right);
    }
}

int main() {
    int n;

    // Read the size of the array
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Dynamically allocate memory for the array and temporary array
    int* array = (int*)malloc(n * sizeof(int));
    int* tempArray = (int*)malloc(n * sizeof(int));

    if (array == NULL || tempArray == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Read the elements of the array
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    // Perform merge sort
    mergeSort(array, tempArray, 0, n - 1);

    // Print the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Free dynamically allocated memory
    free(array);
    free(tempArray);

    return 0;
}
