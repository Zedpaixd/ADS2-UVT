#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* array;    
    int capacity;  
    int size;       
} Heap;

Heap* createHeap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->array = (int*)malloc(capacity * sizeof(int));
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(Heap* heap, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->array[left] > heap->array[largest])
        largest = left;

    if (right < heap->size && heap->array[right] > heap->array[largest])
        largest = right;

    if (largest != i) {
        swap(&heap->array[i], &heap->array[largest]);
        maxHeapify(heap, largest);
    }
}

void insert(Heap* heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap-ul este plin\n");
        return;
    }

    int i = heap->size++;
    heap->array[i] = value;

    while (i != 0 && heap->array[(i - 1) / 2] < heap->array[i]) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int deleteMax(Heap* heap) {
    if (heap->size == 0) {
        printf("Heap-ul este gol.\n");
        return -1;
    }

    int max = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    maxHeapify(heap, 0);
    return max;
}

void deleteElement(Heap* heap, int value) {
    int i;
    for (i = 0; i < heap->size; i++) {
        if (heap->array[i] == value)
            break;
    }
    if (i == heap->size) {
        printf("Element not found in the heap.\n");
        return;
    }

    heap->array[i] = heap->array[heap->size - 1];
    heap->size--;

    maxHeapify(heap, i);
}

void printHeap(Heap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}

void destroyHeap(Heap* heap) {
    free(heap->array);
    free(heap);
}

int main() {
    Heap* heap = createHeap(10);
    insert(heap, 35);
    insert(heap, 33);
    insert(heap, 42);
    insert(heap, 10);
    insert(heap, 14);
    insert(heap, 19);
    insert(heap, 27);
    insert(heap, 44);
    insert(heap, 26);
    insert(heap, 31);

    printf("Heap elements before deletion: ");
    printHeap(heap);

    int max = deleteMax(heap);
    printf("Maximum element: %d\n", max);
    printf("Heap elements after deletion: ");
    printHeap(heap);

    deleteElement(heap, 27);
    printf("Heap elements after deleting 27 : ");
    printHeap(heap);

    destroyHeap(heap);
    return 0;
}
