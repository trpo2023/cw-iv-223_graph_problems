#include "queue_array.h"
#include <stdio.h>
#include <stdlib.h>

struct queue* QueueCreate(int maxsize)
{
    struct queue* q = malloc(sizeof(*q));
    if (q != NULL) {
        q->a = malloc(sizeof(int) * (maxsize + 1));
        if (q->a == NULL) {
            free(q);
            return NULL;
        }
        q->maxsize = maxsize;
        q->size = 0;
        q->head = maxsize + 1;
        q->tail = 0;
    }
    return q;
}

void QueueFree(struct queue* q)
{
    free(q->a);
    free(q);
}

int QueueSize(struct queue* q)
{
    return q->size;
}

int QueueEnqueue(struct queue* q, int value)
{
    if (q->head == q->tail + 1) {
        fprintf(stderr, "Queue overflow\n");
        return -1;
    }

    q->a[q->tail++] = value;
    q->tail = q->tail % (q->maxsize + 1);
    q->size++;
    return 0;
}

int QueueDequeue(struct queue* q)
{
    if (q->head % (q->maxsize + 1) == q->tail) {
        fprintf(stderr, "Queue is empty\n");
        return -1;
    }

    q->head = q->head % (q->maxsize + 1);
    q->size--;
    return q->a[q->head++];
}