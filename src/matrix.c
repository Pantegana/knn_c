#include "matrix.h"

uint8_t** uint8_matrix(int rows, int cols){
    int size = sizeof(uint8_t *) * rows + sizeof(uint8_t) * cols * rows;
    uint8_t** matrix = (uint8_t**)malloc(size);
    uint8_t* ptr = (uint8_t *)(matrix + rows); 
    int count = 0;

    for(int i = 0; i < rows; i++) 
        matrix[i] = (ptr + cols * i);

    return matrix;
}