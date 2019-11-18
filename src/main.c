#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <endian.h>
#include <stdlib.h>
#include "data_load.h"
#include "knn.h"
#include "matrix.h"

#define TRAIN_DATA_FILE "./data/train-images-idx3-ubyte"
#define TRAIN_LABELS_FILE "./data/train-labels-idx1-ubyte"
#define TEST_DATA_FILE "./data/t10k-images-idx3-ubyte"
#define TEST_LABELS_FILE "./data/t10k-labels-idx1-ubyte"

//function prototypes
void print_example(uint8_t* sample, uint8_t label);
double validate(Data* data, int k);
int best_k(Data* data);
int test(Data* data, int k);

int main(int argc, char** argv){
    Data train;
    Data test;
    Data validation;

    if(load_data(TRAIN_DATA_FILE, &train) == -1){
        printf("Error loading training data");
        return EXIT_FAILURE;
    }
    if(read_labels(TRAIN_LABELS_FILE, &train) == -1){
        printf("Error loading training data");
        return EXIT_FAILURE;
    }
    if(load_data(TEST_DATA_FILE, &test) == -1){
        printf("Error loading training data");
        return EXIT_FAILURE;
    }
    if(read_labels(TEST_LABELS_FILE, &test) == -1){
        printf("Error loading training data");
        return EXIT_FAILURE;
    }

    print_example(train.samples[0], train.labels[0]);
    print_example(test.samples[0], test.labels[0]);

    //try out the validate function
    int k = 5;
    validate(&train, k);

    //TODO impletent best_k and train to complete the project

    free(train.samples);
    free(train.labels);
    free(test.samples);
    free(test.labels);
    return EXIT_SUCCESS;
}

//the the results
int test(Data* data, int k){

}

//find the best k for the training data
int best_k(Data* data){

}

double validate(Data* data, int k){

    //TODO split the train/validation datasets somewhere else
    int train_slice = floor(data->num_samples * 0.8);
    int validation_slice = data->num_samples - train_slice;
    int errors = 0;
    uint8_t** train_data = (uint8_t**) malloc(sizeof(uint8_t**) * train_slice);
    uint8_t** validation_data = (uint8_t**) malloc(sizeof(uint8_t**) * validation_slice);
    uint8_t* train_labels = (uint8_t*) malloc(sizeof(uint8_t**) * train_slice);
    uint8_t* validation_labels = (uint8_t*) malloc(sizeof(uint8_t**) * validation_slice);

    //split the dataset in train and validation
    for(int i = 0; i < train_slice; i++)
        train_data[i] = data->samples[i];
    for(int i = train_slice; i < data->num_samples; i++)
        validation_data[i - train_slice] = data->samples[i];
    //split the labels accordingly
    for(int i = 0; i < train_slice; i++)
        train_labels[i] = data->labels[i];
    for(int i = train_slice; i < data->num_samples; i++)
        validation_labels[i - train_slice] = data->labels[i];

    for(int i = 0; i < validation_slice; i ++){
        uint8_t* neighbours = find_k_nearest(
            k,
            validation_data[i], 
            train_data,
            train_labels,
            train_slice,
            data->num_features);
        int most_f = find_most_frequent(neighbours, data->num_classes, k);
        if(most_f != validation_labels[i]){
            errors += 1;
        }
        printf("Current performance is %.2f%%.\n", ((double) ((i+1) - errors) * 100) / (double)(i+1) );
    }
    return ((double) (validation_slice - errors) * 100) / (double)validation_slice;
}

//print a sample in console
void print_example(uint8_t* sample, uint8_t label){
    for (int i = 0; i < 28*28; i++){
        printf("%d ", sample[i] > 0);
        if((i + 1) % 28 == 0){
            printf("\n");
        }
    }
    printf("%d\n", label);
    printf("\n");
}