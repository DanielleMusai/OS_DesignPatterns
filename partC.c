#include <stdlib.h>
#include "partC.h"
//Part C

void *activeObjectThread(void *arg)
{
    activeObject *self = (activeObject *)arg;
    void *task;
    while ((task = dequeue(self->queue)) != NULL)
    {
        self->func(task);
    }
    return NULL;
}

activeObject *createActiveObject(void *(*func)(void *))
{
    activeObject *obj = malloc(sizeof(activeObject));
    if (obj == NULL)
    {
        fprintf(stderr, "allocate Memory failed.\n");
        exit(EXIT_FAILURE);
    }
    obj->queue = createQueue();
    obj->func = func;
    pthread_create(&(obj->pthr), NULL, start, obj);
    return obj;
}

void stop(activeObject *obj)
{
    enqueue(obj->queue, NULL);
    pthread_join(obj->pthr, NULL);
    freeQueue(obj->queue);
    free(obj);
}

queue *getQueue(activeObject *obj)
{
    return obj->queue;
}