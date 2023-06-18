/*

Based on the literature "Ultra-low Power Embedded Unsupervised
Learning Smart Sensor for Industrial Fault
Classification" - Paper by Geis et al.

*/


#include "algorithm/algorithm.h"
#include<math.h>

float centroid[N_DATA_POINTS][N_FEATURES];
float variance[N_DATA_POINTS][N_FEATURES];
float epsilon = 0.00001;
float alpha = 0.1;
float distance;
int centroid_count;

float *cent = &centroid[0][0];
float *var = &variance[0][0];


// Training function
ERROR_T kmeans_train(float *data, float threshold)
{
    for (int i = 0; i < N_FEATURES; i++)
    {
        centroid[0][i] = data[i];
        variance[0][i] = threshold;
    }

    int n;
    centroid_count = 0; // centroid count is the value + 1

    // loop to go line by line in data
    for (int i = 1; i < N_DATA_POINTS; i++)
    {
        n = 0;
        // loop for each centroid
        for (int j = 0; j < centroid_count+1; j++)
        {
            distance = 0;
            // loop for each feature
            for (int k = 0; k < 32; k++)
            {
                distance = distance + (((data[(32*i)+k] - cent[(32*j)+k]) / (var[(32*j)+k] + epsilon)) * ((data[(32*i)+k] - cent[(32*j)+k]) / (var[(32*j)+k] + epsilon)));
            }
            distance = sqrtf(distance) / 32;

            if (distance < threshold)
            {
                n=1;
                for (int k = 0; k < 32; k++)
                {
                    cent[(32*j)+k] = ((1-alpha)* cent[(32*j)+k]) + (alpha * data[(32*i)+k]);
                    var[(32*j)+k] = fabs(((1-alpha)* var[(32*j)+k]) + (alpha * (fabs(data[(32*i)+k] - cent[(32*j)+k]))));
                }
                break;

            }
        }

        if (n == 0)
        {
            centroid_count ++;

            for (int j = 0; j < 32; j++)
            {
                centroid[centroid_count][j] = data[(32*i)+j];
                variance[centroid_count][j] = threshold;
            }
        }
    }


return 0;
}



// Prediction function
ERROR_T kmeans_predict(float *data, float threshold, int *pred)
{
    int8_t n;
    for (int i = 0; i < N_DATA_POINTS; i++)
    {
        n = 0;
        // loop for each centroid
        for (int j = 0; j < centroid_count+1; j++)
        {
            distance = 0;
            // loop for each feature
            for (int k = 0; k < 32; k++)
            {
                distance = distance + (((data[(32*i)+k] - cent[(32*j)+k]) / (var[(32*j)+k] + epsilon)) * ((data[(32*i)+k] - cent[(32*j)+k]) / (var[(32*j)+k] + epsilon)));
            }
            distance = sqrtf(distance) / 32;

            if (distance < threshold)
            {
                n=1;
                pred[i] = 1;
                break;
            }
        }
        if (n == 0)
        {
            pred[i] = -1;
        }
    }
return 0;
}
