#include <stdio.h>
#include "Queue.h"

/* a driver program to test Queue */

int main(void) {

    struct Queue queue = { 0 };
    QueueNew(&queue, sizeof(double));
    
    double lz = 0.0;
    
    for (int i = 0; i < 5; ++i) {
        QueueEnqueue(&queue, &lz);
        printf("Enqueued: %lf\n", lz);
        ++lz;
    }

    QueueDequeue(&queue, NULL);
    QueueDequeue(&queue, NULL);

    while (QueueGetCount(&queue) > 0) {
        QueueDequeue(&queue, &lz);
        printf("Dequeued: %lf\n", lz);
    }

    QueueDispose(&queue);
    getchar();
    return 0;
}
