#include <math.h>
#include <stdbool.h>
#include "partA.h"


bool isPrime(unsigned int num)
{
    if (num < 2 || (num > 2 && num % 2 == 0))
        return false;

    for (unsigned int i = 3; i <= sqrt(num); i += 2)
    {
        if (num % i == 0)
            return false;
    }

    return true;
}