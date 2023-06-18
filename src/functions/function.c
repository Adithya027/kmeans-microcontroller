#include "functions/function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const char* filePath;

FILE *fpr;

float mean[N_FEATURES];
float sd[N_FEATURES];

//  Selecting the required file
ERROR_T init_import_data(float *data_array_call, purpose_t purpose)
{
    if (purpose == 0)
    {
        filePath = "../Dataset/features_source_train_speed_2_export_new.csv";
        fpr = fopen(filePath, "r");
        printf("Reading Training data\n");
    }
    else if (purpose == 1)
    {
        filePath = "../Dataset/features_source_test_speed_2_normal_export_new.csv";
        fpr = fopen(filePath, "r");
        printf("Reading Normal Testing data\n");
    }
    else if (purpose == 2)
    {
        filePath = "../Dataset/features_source_test_speed_2_a_dmg_high_export_new.csv";
        fpr = fopen(filePath, "r");
        printf("Reading Anomalous Testing data\n");
    }
    else
    {
        return 1;
    }

return 0;
}

//  Reading the required file
ERROR_T read_data(float *data_points)
{

    if (ferror(fpr))
    {
            printf("Error opening file");
            return 1;
    }

    int num_rows = 0;
    int i = 0;

    char line[1000];

     while (fscanf(fpr, "%[^,\n]", line) != EOF)
    {
        if (num_rows%33 != 0)
        {
            *(data_points+i) = atof(line);
            i++;
        }
        //printf("item %i\n", atoi(line));
        fgetc(fpr);
        num_rows++;
        if (num_rows == DATA_ARRAY)
        {
            break;
        }
    }

return 0;
}

// Closing the opened file after reading is complete
ERROR_T close_file()
{
    fclose(fpr);
return 0;
}

// Fitting standardization function for normalizing and transforming normal training data
ERROR_T standardization_fit_transform(float *data)
{

    float sum[N_FEATURES] = {0};

    for (int i = 0; i < N_FEATURES; i++)
    {
        mean[i] = 0;
        sd[i] = 0;
    }


    for(uint32_t i = 0; i < N_FEATURES; i++)
    {
        for(uint32_t j = 0; j < N_DATA_POINTS; j++)
        {
            sum[i] = sum[i] + data[i+(N_FEATURES*j)];

        }
        mean[i] = sum[i] / N_DATA_POINTS;
    }

    for(uint32_t i = 0; i < N_FEATURES; i++)
    {
        for(uint32_t j = 0; j < N_DATA_POINTS; j++)
        {
            sd[i] = sd[i] + ((data[i+(N_FEATURES*j)] - mean[i]) * (data[i+(N_FEATURES*j)] - mean[i]));

        }
        sd[i] = sqrt(sd[i] / N_DATA_POINTS);
    }

    for (int i = 0; i < N_DATA_POINTS; i++)
    {
        for(uint32_t j = 0; j < N_FEATURES; j++)
        {
          data[(N_FEATURES*i)+j] = (data[(N_FEATURES*i)+j] - mean[j]) / sd[j];
        }

    }
return 0;

}

// Normalize data based on available standards
ERROR_T standardization_transform(float *data)
{
    for (int i = 0; i < N_DATA_POINTS; i++)
    {
        for(uint32_t j = 0; j < N_FEATURES; j++)
        {
          data[(N_FEATURES*i)+j] = (data[(N_FEATURES*i)+j] - mean[j]) / sd[j];
        }

    }
return 0;
}







/*
 while (fscanf(fpr, "%s", line) != EOF)
    {
        //line[strcspn(line, "\n")] = '\0'; // Remove the newline character

        int col = 0;
        int ignore_first = 1; // Flag to ignore the first element

        // Read values using sscanf
        char* ptr = line;
        while (*ptr != '\0' && col < N_FEATURES) {
            if (ignore_first) {
                ignore_first = 0;
            } else {
                int value;
                if (sscanf(ptr, "%d,", &value) == 1) {
                    data[num_rows][col] = value;
                    col++;
                }
            }
            ptr = strchr(ptr, ',');
            if (ptr != NULL) {
                ptr++; // Move pointer to the next comma
            }
        }


        num_rows++;

        if (num_rows >= N_DATA_POINTS) {
            printf("Exceeded maximum number of rows.\n");
            fclose(fpr);
            return 1;
        }
    }

    fclose(fpr);

    // Print the data
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < N_FEATURES - 1; j++) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }
*/
