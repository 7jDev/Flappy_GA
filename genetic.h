#ifndef GENETIC_H
#define GENETIC_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MUTATION_RATE 0.01 
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
inline static float mutate(); 
static inline void n_clean_up(neuron * clean); 
static inline neuron initialize_neuron (size_t number_of_input );
inline static float compute_neuron( neuron * self,float* inputs, activation func);
inline static neuron n_crossover(neuron * first, neuron * second); 
typedef struct{
size_t num_inputs,
       num_neurons;
neuron * neurons;  
} layer;
inline static layer initialize_layer(size_t number_of_input, size_t number_of_neurons); 
inline static float * compute_layer(layer * self, float * inputs, activation func, float * result) ; 
static layer l_crossover(layer * first, layer * second);
inline static void l_clean_up(layer * self);
typedef struct {
	size_t num_layers,
	       num_inputs;
	size_t *neurons_per;
	activation *func_per;
	layer * layers; 
} brain; 
brain initialize_brain(size_t num_layers, 
		size_t num_inputs, 
		size_t neurons_per[],
		activation func_per[]); 
float * compute_brain(brain * self, float * inputs);  
brain crossover(brain * first, brain * second);
void clean_up(brain * self);
#endif 
