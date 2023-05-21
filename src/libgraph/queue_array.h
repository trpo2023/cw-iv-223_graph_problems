#pragma once
#include <stdio.h>

struct queue {
    int* a;
    int head;
    int tail;
    int size;
    int maxsize;
};

struct queue* QueueCreate(int maxsize);
void QueueFree(struct queue* q);
int QueueSize(struct queue* q);
int QueueEnqueue(struct queue* q, int value);
int QueueDequeue(struct queue* q);