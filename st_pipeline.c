#include <math.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include "st_pipeline.h"


activeObject *AO1, *AO2, *AO3, *AO4;

void *func1(void *argument)
{
    unsigned int *number_ptr = (unsigned int *)argument;
    unsigned int number = *number_ptr;

    printf("%u\n", number);

    if (isPrime(number))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }

    unsigned int *number_copy = malloc(sizeof(unsigned int));
    if (number_copy == NULL)
    {
        fprintf(stderr, "Allocate Memory failed.\n");
        exit(EXIT_FAILURE);
    }
    *number_copy = number;
    enqueue(getQueue(AO2), number_copy);

    return NULL;
}

void *func2(void *argument)
{
    unsigned int *number = (unsigned int *)argument;

    *number += 11;

    printf("%u\n", *number);

    if (isPrime(*number))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }

    enqueue(getQueue(AO3), number);

    return NULL;
}

void *func3(void *argument)
{
    unsigned int *number = (unsigned int *)argument;

    *number -= 13;

    printf("%u\n", *number);

    if (isPrime(*number))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }

    enqueue(getQueue(AO4), number);

    return NULL;
}

void *func4(void *argument)
{
    unsigned int *number = (unsigned int *)argument;

    *number += 2;

    printf("%u\n", *number);

    free(number);

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Too many Arguments! \n");
        return 0;
    }

    if (argc > 3 || argc < 2)
    {
        printf("Usage: %s <tasksNum> <seed>\n", argv[0]);
        return 1;
    }

    int iterations = atoi(argv[1]);

    int seed;
    if (argc == 3)
    {
        seed = atoi(argv[2]);
    }
    else
    {
        seed = time(0);
    }

    srand(seed);

    AO1 = createActiveObject(func1);
    AO2 = createActiveObject(func2);
    AO3 = createActiveObject(func3);
    AO4 = createActiveObject(func4);

    for (int i = 0; i < iterations; i++)
    {
        unsigned int *num = malloc(sizeof(unsigned int));
        *num = rand() % 900000 + 100000;
        enqueue(getQueue(AO1), num);
        printf("\n");

        if (i < iterations - 1)
        {
            sleep(1);
        }
    }

    stop(AO1);
    stop(AO2);
    stop(AO3);
    stop(AO4);

    return 0;
}