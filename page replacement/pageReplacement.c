#include <stdio.h>

#define MAX 100

void printFrame(int frame[], int frames) {
    for (int i = 0; i < frames; i++) {
        if (frame[i] == -1)
            printf("_ ");
        else
            printf("%d ", frame[i]);
    }
    printf("\n");
}

void fifo(int pages[], int n, int frames) {
    int frame[MAX], front = 0, count = 0, i, j, found;
    for (i = 0; i < frames; i++) frame[i] = -1;

    printf("FIFO Page Replacement Process:\n");
    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frame[front] = pages[i];
            front = (front + 1) % frames;
            count++;
            printf("PF No. %d: ", count);
            printFrame(frame, frames);
        }
    }
    printf("FIFO Page Faults: %d\n\n", count);
}

void lru(int pages[], int n, int frames) {
    int frame[MAX], recent[MAX], count = 0, i, j, k, found, least;
    for (i = 0; i < frames; i++) frame[i] = -1;

    printf("LRU Page Replacement Process:\n");
    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (i < frames) {
                frame[i] = pages[i];
            } else {
                for (j = 0; j < frames; j++) {
                    recent[j] = -1;
                    for (k = i - 1; k >= 0; k--) {
                        if (frame[j] == pages[k]) {
                            recent[j] = k;
                            break;
                        }
                    }
                }

                least = 0;
                for (j = 1; j < frames; j++) {
                    if (recent[j] < recent[least])
                        least = j;
                }

                frame[least] = pages[i];
            }
            count++;
            printf("PF No. %d: ", count);
            printFrame(frame, frames);
        }
    }
    printf("LRU Page Faults: %d\n\n", count);
}

void optimal(int pages[], int n, int frames) {
    int frame[MAX], future[MAX], count = 0, i, j, k, found, farthest;
    for (i = 0; i < frames; i++) frame[i] = -1;

    printf("Optimal Page Replacement Process:\n");
    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (i < frames) {
                frame[i] = pages[i];
            } else {
                for (j = 0; j < frames; j++) {
                    future[j] = -1;
                    for (k = i + 1; k < n; k++) {
                        if (frame[j] == pages[k]) {
                            future[j] = k;
                            break;
                        }
                    }
                }

                farthest = 0;
                for (j = 1; j < frames; j++) {
                    if (future[j] == -1 || (future[farthest] != -1 && future[j] > future[farthest]))
                        farthest = j;
                }

                frame[farthest] = pages[i];
            }
            count++;
            printf("PF No. %d: ", count);
            printFrame(frame, frames);
        }
    }
    printf("Optimal Page Faults: %d\n", count);
}

int main() {
    int pages[MAX], n, frames, choice, i;

    printf("Enter the number of Frames: ");
    scanf("%d", &frames);
    printf("Enter the length of reference string: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("\n");
    fifo(pages, n, frames);
    lru(pages, n, frames);
    optimal(pages, n, frames);

    return 0;
}
