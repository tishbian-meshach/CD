#include <stdio.h>

void firstFit(int blockSize[], int m, int processSize[], int n) {
    // Array to store the block allocated to a process
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1; // Initialize as not allocated
    }

    // Loop through each process to allocate memory
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                // Allocate block j to process i
                allocation[i] = j;
                blockSize[j] -= processSize[i]; // Reduce available memory in this block
                break;
            }
        }
    }

    // Output the allocation results
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};
    int m = sizeof(blockSize) / sizeof(blockSize[0]); // Number of blocks
    int n = sizeof(processSize) / sizeof(processSize[0]); // Number of processes

    firstFit(blockSize, m, processSize, n);

    return 0;
}
