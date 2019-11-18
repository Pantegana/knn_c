#ifndef DATA_LOAD_H
#define DATA_LOAD_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <endian.h>
#include <stdlib.h>
#include "matrix.h"

typedef struct Data{
    uint8_t** samples;
    uint8_t* labels;
    int num_features;
    int num_samples;
    int num_classes;
} Data;

int load_data(const char* filename, Data* data);

int read_labels(const char* filename, Data* data);

#endif
