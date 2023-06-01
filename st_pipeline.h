#ifndef ST_PIPELINE_H
#define ST_PIPELINE_H
#include <pthread.h>
#include "partB.h"
#include "partC.h"
#include "partA.h"

void* func1(void* argument);
void* func2(void* argument);
void* func3(void* argument);
void* func4(void* argument);

#endif  // ST_PIPELINE_H
