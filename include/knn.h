#ifndef KNN_H
#define KNN_H

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <float.h>
#include "data_load.h"

uint8_t* find_k_nearest(int k, uint8_t* point, uint8_t** data, uint8_t* labels, int num_samples, int num_features);

double euclidean(uint8_t* point_a, uint8_t* point_b, int size);

int find_most_frequent(uint8_t* neighbours, int num_classes, int k);

#endif
