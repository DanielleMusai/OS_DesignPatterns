#include <stdlib.h>
#include "partC.h"
//Part C

void *activeObjectThread(void *obj)
{
    activeObject *AO = (activeObject *)obj;
    void *task;
    while ((task = dequeue(AO->queue)) != NULL)
    {
        AO->func(task);
    }
    return NULL;
}

activeObject *createActiveObject(void *(*func)(void*))
{
    activeObject *obj = malloc(sizeof(activeObject));
    if (obj == NULL)
    {
        return NULL;

    }
    obj->queue = createQueue();
    obj->func = func;
    pthread_create(&(obj->thread), NULL, activeObjectThread, obj);
    return obj;
}

void stop(activeObject *obj)
{
    enqueue(obj->queue, NULL);
    pthread_join(obj->thread, NULL);
    freeQueue(obj->queue);
    free(obj);
}

queue *getQueue(activeObject *obj)
{
    return obj->queue;
}