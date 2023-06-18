#ifndef FUNCTION
#define FUNCTION
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define N_DATA_POINTS 270
#define N_FEATURES (1<<5)
#define DATA_PER_LINE (1<<14)
#define DATA_ARRAY N_DATA_POINTS*N_FEATURES

enum purpose {train = 0, test_n = 1, test_a = 2};

typedef enum purpose purpose_t;
typedef int ERROR_T;

ERROR_T init_import_data(float *data_array_call, purpose_t purpose);

ERROR_T read_data(float *data_array_call);

ERROR_T close_file();

ERROR_T standardization_fit_transform(float *data_array_call);

ERROR_T standardization_transform(float *data_array_call);

#endif // FUNCTION
