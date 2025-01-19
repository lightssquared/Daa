#include <stdio.h>
#include <stdlib.h>

// Structure to represent a 3-ary minheap
struct MinHeap {
    int* heapArray;   // Array to store heap elements
    int size;         // Number of elements in the heap
    int capacity;     // Capacity of the heap
};

// Function to create a 3-ary minheap
struct MinHeap* createHeap(int capacity) {
    struct MinHeap* heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    if (!heap) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    heap->capacity = capacity;
    heap->size = 0;
    heap->heapArray = (int*)malloc(capacity * sizeof(int));
    if (!heap->heapArray) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    return heap;
}

// Function to get the index of the ith child of a node
int getChildIndex(int parentIndex, int i) {
    return parentIndex * 3 + i + 1;
}

// Function to heapify the heap
void heapify(struct MinHeap* heap, int index) {
    int smallest = index;
    int leftChild, middleChild, rightChild;

    // Check for the three children of the current node
    for (int i = 0; i < 3; i++) {
        int childIndex = getChildIndex(index, i);
        if (childIndex < heap->size) {
            if (heap->heapArray[childIndex] < heap->heapArray[smallest]) {
                smallest = childIndex;
            }
        }
    }

    // If the smallest child is smaller than the current node, swap and heapify the affected subtree
    if (smallest != index) {
        int temp = heap->heapArray[index];
        heap->heapArray[index] = heap->heapArray[smallest];
        heap->heapArray[smallest] = temp;

        heapify(heap, smallest);
    }
}

// Function to insert an element into the 3-ary minheap
void insert(struct MinHeap* heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap is full\n");
        return;
    }

    // Insert the new element at the end of the heap
    heap->heapArray[heap->size] = value;
    int index = heap->size;
    heap->size++;

    // Fix the heap property by moving the new element up the heap
    while (index > 0) {
        int parentIndex = (index - 1) / 3;
        if (heap->heapArray[parentIndex] > heap->heapArray[index]) {
            // Swap the values
            int temp = heap->heapArray[parentIndex];
            heap->heapArray[parentIndex] = heap->heapArray[index];
            heap->heapArray[index] = temp;

            index = parentIndex;
        } else {
            break;
        }
    }
}

// Function to remove the root (min) from the heap
int removeRoot(struct MinHeap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty\n");
        return -1;
    }

    int root = heap->heapArray[0];
    heap->heapArray[0] = heap->heapArray[heap->size - 1];
    heap->size--;

    // Restore the heap property by heapifying the root
    heapify(heap, 0);

    return root;
}

// Function to print the heap
void printHeap(struct MinHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->heapArray[i]);
    }
    printf("\n");
}

int main() {
    int capacity;

    // Get user input for heap capacity
    printf("Enter the capacity of the heap: ");
    scanf("%d", &capacity);

    // Create the 3-ary minheap
    struct MinHeap* heap = createHeap(capacity);

    // Inserting elements into the heap
    insert(heap, 30);
    insert(heap, 20);
    insert(heap, 50);
    insert(heap, 10);
    insert(heap, 40);
    insert(heap, 60);
    insert(heap, 5);

    // Print the heap
    printf("Heap elements: ");
    printHeap(heap);

    // Remove root (min)
    int root = removeRoot(heap);
    printf("Removed root (min): %d\n", root);

    // Print the heap after removal
    printf("Heap elements after removing root: ");
    printHeap(heap);

    // Free dynamically allocated memory
    free(heap->heapArray);
    free(heap);

    return 0;
}
