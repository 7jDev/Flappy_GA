#ifndef GENETIC_H
#define GENETIC_H
typedef struct neuron{
size_t num_neurons,
       num_inputs;
double* bias;
double* weights[];
} neuron;

double initialize_neuron (neuron * self);
double compute_neuron( neuron * self,double * inputs);
typedef struct{

} layer;
typedef struct {

} brain; 
#endif 
