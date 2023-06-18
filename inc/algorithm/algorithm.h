#ifndef ALGORITHM
#define ALGORITHM

#include "functions/function.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


typedef int ERROR_T;

ERROR_T kmeans_train(float *data, float threshold);

ERROR_T kmeans_predict(float *data, float threshold, int *pred);


#endif // ALGORITHM
