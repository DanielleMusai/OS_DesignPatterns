#ifndef PART_B_H
#define PART_B_H
#include <pthread.h>
#include <stdio.h>

typedef struct node {
    void* data;
    struct node* next;
} node;

typedef struct queue {
    node* head;
    node* tail;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} queue;

queue* createQueue();
void enqueue(queue* que, void* item);
void* dequeue(queue* que);
void freeQueue(queue* queue);
node *createNode(void *item);

#endif  // PART_B_H
