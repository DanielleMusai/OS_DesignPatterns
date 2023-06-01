#ifndef PART_C_H
#define PART_C_H
#include <pthread.h>
#include "partB.h"

typedef struct activeObject {
    pthread_t pthr;
    queue* queue;
    void* (*func)(void*);
} activeObject;

void *activeObjectThread(void* arg);
activeObject* createActiveObject(void* (*func)(void*));
void stop(activeObject* obj);
queue* getQueue(activeObject* obj);


#endif  // PART_C_H
