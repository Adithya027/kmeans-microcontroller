#include <stdint.h>

#include "functions/function.h"
#include "algorithm/algorithm.h"

float data_array[DATA_ARRAY];
float data_array_result[DATA_ARRAY];
float *data_array_result_p = data_array_result;

float *data_array_p = data_array;
int error;


float threshold = 0.4;
int result[N_DATA_POINTS];
int *pred = result;
int samples = 0;
int tp, tn, fp, fn = 0;

int main()
{
   error = init_import_data(data_array_p, train);
   error = read_data(data_array_p);
   error = close_file();
   error = standardization_fit_transform(data_array_p);
   error = kmeans_train(data_array_p, threshold);
   printf("TRAINING COMPLETE!\n\n");

   error = init_import_data(data_array_p, test_a);
   error = read_data(data_array_p);
   error = close_file();
   error = standardization_transform(data_array_p);
   error = kmeans_predict(data_array_p, threshold, pred);
    for(int i = 0; i < N_DATA_POINTS; i++)
    {
        if (*(pred+i) == -1)
        {
            tp++;
        }
        else
        {
            tn++;
        }
    }


    error = init_import_data(data_array_p, test_n);
    error = read_data(data_array_p);
    error = close_file();
    error = standardization_transform(data_array_p);
    error = kmeans_predict(data_array_p, threshold, pred);
    for(int i = 0; i < N_DATA_POINTS; i++)
    {
        if (*(pred+i) == -1)
        {
            fp++;
        }
        else
        {
            fn++;
        }
    }

printf("\n\nf1 Score:\n");
float precision = tp / (float)(tp + fp);
float recall = tp / (float)(tp + fn);
float f1Score = 2 * ((precision * recall) / (precision + recall));
printf("%f\n", f1Score);


   /*for(int i = 0; i < N_DATA_POINTS; i++)
    {
        printf("%i  ", *(pred+i));
    }*/

}


