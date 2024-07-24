#ifndef GENETIC_H
#define GENETIC_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
typedef struct neuron{
size_t num_inputs;
float bias;
float* weights;
} neuron;
typedef enum{
	SIGMOID, 
	RELU 
} activation;
inline static float sigmoid(float x); 
inline static float relu(float x); 
/*static inline */void n_clean_up(neuron * clean); 
/*static inline */ neuron initialize_neuron (size_t number_of_input );
float compute_neuron( neuron * self,float* inputs, activation func);
typedef struct{
size_t num_inputs,
       num_neurons;
neuron * neurons[];  
} layer;
layer initialize_layer(size_t number_of_input, size_t number_of_neurons); 

typedef struct {

} brain; 
#endif 
