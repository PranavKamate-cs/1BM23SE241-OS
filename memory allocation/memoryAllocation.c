#include <stdio.h>

void firstFit(int blockSize[], int b, int processSize[], int f) {
    int allocation[f];
    for (int i = 0; i < f; i++)
        allocation[i] = -1;

    for (int i = 0; i < f; i++) {
        for (int j = 0; j < b; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                break;
            }
        }
    }

    printf("\nMemory Management Scheme - First Fit\n");
    printf("\nFile_no\tFile_size\tBlock_no\tBlock_size:\n");
    for (int i = 0; i < f; i++) {
        printf("%d\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\t\t%d\n", allocation[i] + 1, blockSize[allocation[i]]);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int b, int processSize[], int f) {
    int allocation[f];
    for (int i = 0; i < f; i++)
        allocation[i] = -1;

    for (int i = 0; i < f; i++) {
        int bestIdx = -1;
        for (int j = 0; j < b; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
        }
    }

    printf("\nMemory Management Scheme - Best Fit\n");
    printf("\nFile_no\tFile_size\tBlock_no\tBlock_size:\n");
    for (int i = 0; i < f; i++) {
        printf("%d\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\t\t%d\n", allocation[i] + 1, blockSize[allocation[i]]);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int b, int processSize[], int f) {
    int allocation[f];
    for (int i = 0; i < f; i++)
        allocation[i] = -1;

    for (int i = 0; i < f; i++) {
        int worstIdx = -1;
        for (int j = 0; j < b; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
        }
    }
    printf("\nMemory Management Scheme - Worst Fit\n");
    printf("\nFile_no\tFile_size\tBlock_no\tBlock_size:\n");
    for (int i = 0; i < f; i++) {
        printf("%d\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\t\t%d\n", allocation[i] + 1, blockSize[allocation[i]]);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blockSize[10], processSize[10];
    int b, f, i, j, choice;

    printf("Memory Management Scheme\n");
    printf("Enter the number of blocks: ");
    scanf("%d", &b);
    printf("Enter the number of processes: ");
    scanf("%d", &f);

    printf("\nEnter the size of the blocks:\n");
    for (i = 0; i < b; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the size of the files:\n");
    for (i = 0; i < f; i++) {
        printf("File %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }
    int b1[10];

    do {

        printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        for (int i = 0; i < b; i++) {
            b1[i] = blockSize[i];
        }
        switch (choice) {
            case 1:
                firstFit(b1, b, processSize, f);
                break;

            case 2:
                bestFit(b1, b, processSize, f);
                break;

            case 3:
                worstFit(b1, b, processSize, f);
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice.\n");
                continue;
        }

    } while (choice != 4);

    return 0;
}