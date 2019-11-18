#include "data_load.h"

int load_data(const char* filename, Data* data){
    //open file
    FILE* fp = fopen(filename, "r");
    if(!fp){
        printf("Error opening file %s.\n", filename);
        return -1;
    }
    //read header data
    uint32_t header[4];
    for(int i = 0; i < 4; i++){
        if(fread(&header[i], sizeof(uint32_t), 1, fp)){
            header[i] = be32toh(header[i]);
        }
    }
    
    uint32_t samples = header[1];
    uint32_t dimensions = header[2] * header[3];
    //allocate matrix
    data->samples =  (uint8_t**)uint8_matrix(samples, dimensions);
  
    //read samples data
    for (int i = 0; i < samples; i++){
        for (int j = 0; j < dimensions; j++){
            fread(&(data->samples)[i][j], sizeof(uint8_t), 1, fp);
        }
    } 
    data->num_features = dimensions;
    data->num_samples = samples;

    //close file
    fclose(fp);
    return 0;
}

int read_labels(const char* filename, Data* data){
    //open file
    FILE* fp = fopen(filename, "r");
    if(!fp){
        printf("Error opening file %s.\n", filename);
        return -1;
    }
    //read header data
    uint32_t header[2];
    for(int i = 0; i < 2; i++){
        if(fread(&header[i], sizeof(uint32_t), 1, fp)){
            header[i] = be32toh(header[i]);
        }
    }
    data->labels = (uint8_t*) malloc(sizeof(uint8_t) * header[1]);
    //char array to count the classes, same length of the labels array
    //as there could be as many classes as there are labels
    char* classes = (char*) malloc(sizeof(char) * header[1]);
    //init all values to \0
    memset((void *)classes, '\0', sizeof(char) * header[1]);

    //read labels
    for (int i = 0; i < header[1]; i++){
        fread((data->labels + i), sizeof(uint8_t), 1, fp);
        classes[data->labels[i]] = 'a';
    } 
    //check length of "string" to find the number of classes
    data->num_classes = strlen(classes);
    
    fclose(fp);
    return 0;
}
