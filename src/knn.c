#include "knn.h"

//find the most frequent class of the bunch
int find_most_frequent(uint8_t* neighbours, int num_classes, int k){
    int classes[num_classes];
    int max = 0;
    int class;
    memset((void *)classes, 0, sizeof(int) * num_classes);
    for(int i =0; i < k; i++){
        classes[neighbours[i]] +=1;
    }

    for(int i = 0; i < num_classes; i++){
        if(classes[i] > max){
            max = classes[i];
            class = i;
        }
    }

    if(max > 0){
        return class;
    }
    printf("Error searching for most frequent class'");
    return -1;
}

uint8_t* find_k_nearest(int k, uint8_t* point, uint8_t** data, uint8_t* labels, int num_samples, int num_features){
    uint8_t* neighbours = (uint8_t*) malloc(sizeof(uint8_t) * k);
    double min = DBL_MAX;
    int idx = 0;
    double old_min;

    //iterate through the dataset to find the first neighbour
    for(int i = 0; i < num_samples; i++){
        double distance = euclidean(point, data[i], num_features);
        if(distance < min){
            min = distance;
            idx = i;
        }
    }
    neighbours[0] = labels[idx];
    old_min = min;
    min = DBL_MAX;

    //find all other neighbours up to k
    for( int i = 1; i < k; i++){
        for(int j = 0; j < num_samples; j++){
            double distance = euclidean(point, data[j], num_features);
            if(distance < min && distance > old_min){
                min = distance;
                idx = j;
            }
        }
        neighbours[i] = labels[idx];
        old_min = min;
        min = DBL_MAX;
    }
    
    return neighbours;
}

//calculate euclidean distance
double euclidean(uint8_t* point_a, uint8_t* point_b, int size){
    double val = 0;
    for(int i =0; i < size; i++){
        val += pow((point_a[i] - point_b[i]), 2);
    }
    
    return val;
}