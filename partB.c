#include <stdlib.h>
#include "partB.h"

//Part B 

queue *createQueue()
{
    queue *q = malloc(sizeof(queue));
    if (q == NULL)
    {
        fprintf(stderr, "allocate Memory failed\n");
        exit(EXIT_FAILURE);
    }
    pthread_mutex_init(&(q->mutex), NULL);
    pthread_cond_init(&(q->cond), NULL);
    q->head = NULL;
    q->tail = NULL;
    return q;
}

void enqueue(queue *que, void *item)
{
    node *new_node = createNode(item);

    pthread_mutex_lock(&(que->mutex));

    if (que->head == NULL)
    {
        que->head = new_node;
        que->tail = new_node;
    }
    else
    {
        que->tail->next = new_node;
        que->tail = new_node;
    }

    pthread_cond_signal(&(que->cond));
    pthread_mutex_unlock(&(que->mutex));
}

void *dequeue(queue *que)
{
    pthread_mutex_lock(&(que->mutex));

    while (que->head == NULL)
    {
        pthread_cond_wait(&(que->cond), &(que->mutex));
    }

    node *head = que->head;
    void *item = head->data;
    que->head = head->next;

    if (que->head == NULL)
    {
        que->tail = NULL;
    }

    pthread_mutex_unlock(&(que->mutex));

    free(head);
    return item;
}
void freeQueue(queue *queue)
{
    pthread_mutex_lock(&(queue->mutex));

    node *current = queue->head;
    while (current != NULL)
    {
        node *to_free = current;
        current = current->next;
        free(to_free);
    }

    queue->head = NULL;
    queue->tail = NULL;
    pthread_mutex_unlock(&(queue->mutex));
    pthread_mutex_destroy(&(queue->mutex));
    pthread_cond_destroy(&(queue->cond));
    free(queue);
}


node *createNode(void *item)
{
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        fprintf(stderr, "allocate Memory failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = item;
    new_node->next = NULL;

    return new_node;
}
