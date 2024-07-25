#include "genetic.h"
static inline void n_clean_up(neuron * clean) 
{
	free(clean->weights); 
}
static inline neuron initialize_neuron (size_t number_of_input )
{
	float * weights= calloc(number_of_input,sizeof(float)); 
	float bias = ((float)rand()/ (float)RAND_MAX) -0.5;	
	for(size_t i=0; i< number_of_input; ++i)
		weights[i] = ((float)rand()/(float)RAND_MAX) - 0.5;
	neuron return_val = {
		number_of_input, 
		bias,weights 
		};	
	return return_val;
}  

inline static float sigmoid(float x)
{
	return (1)/(1 + exp(-x));
}
inline static float relu(float x)
{
	if(x < 0.0)
		return 0.0;
	else 
		return x; 
}
inline static float compute_neuron(neuron * self, float * inputs , activation func)
{
	float sum = 0.0;  
	float result = 0.0; 
	for(size_t i=0; i< self->num_inputs; ++i)
	{
		sum += inputs[i] * self->weights[i];	
	} 
	sum += self->bias; 
	switch(func)
	{
		case SIGMOID:
			result = sigmoid(sum);
		case RELU:
			result = relu(sum);
	} 
	return result; 
} 
static inline float mutate()
{
	int mutator = (int)(MUTATION_RATE*100);
	float return_val = 0.0; 
	if(rand() % mutator == mutator)
	{
		return_val = ((float)rand()/RAND_MAX)- 0.5;
	}
	return return_val; 
}
inline static neuron n_crossover(neuron * first, neuron * second){
	assert(first->num_inputs == second->num_inputs);
	float * weights= calloc(first->num_inputs,sizeof(float)); 
	float bias = second->bias; 
	neuron result = {first->num_inputs,
			bias,
			weights}; 
	for(size_t i=0; i<first->num_inputs; ++i)
	{
		if(rand() % 2)
			weights[i] = first->weights[i] + mutate();	
		else
			weights[i] = second->weights[i] + mutate();

	}
	if(rand() % 2)
		bias = first->bias + mutate(); 
	return result;
} 
inline static layer initialize_layer(size_t number_of_input, size_t number_of_neurons)
{
	neuron * neurons = calloc(number_of_neurons , sizeof(neuron));
	for(size_t i=0; i< number_of_neurons; ++i)
		 neurons[i] = initialize_neuron(number_of_input);
	layer result ={number_of_input, number_of_neurons, neurons};
	return result;
}
inline static float * compute_layer(layer* self, float * inputs, activation func, float* result )
{
	for(size_t i=0; i< self->num_neurons; ++i)
		result[i] = compute_neuron(&self->neurons[i], inputs, func);
	return result; 
}
inline static void l_clean_up(layer * self)
{
	for(size_t i=0; i< self->num_neurons; ++i)
		n_clean_up(&self->neurons[i]);
	free(self->neurons);
}
brain initialize_brain(size_t num_layers,
			size_t num_inputs,
			size_t neurons_per[],
			activation func_per[])
{
layer * layers = calloc(num_layers, sizeof(layer));
brain result={
	num_layers,
	num_inputs, 
	neurons_per, 
	func_per,
	layers
	};
result.layers[0] = initialize_layer(result.num_inputs, result.neurons_per[0]);
for(size_t i=1; i< num_layers; ++i )
{
	result.layers[i] = initialize_layer(result.neurons_per[i-1], result.neurons_per[i]);
}
return result;
} 
float* compute_brain(brain * self, float * inputs)
{
	float * mem[self->num_layers];  
	for(size_t i=0; i< self->num_layers; ++i){
	float * temp = calloc(self->neurons_per[i], sizeof(float));
	mem[i] = temp;
	} 
	compute_layer(&self->layers[0], inputs, self->func_per[0], mem[0]); 
	for(size_t i=1; i< self->num_layers; ++i)
		compute_layer(&self->layers[i], mem[i-1], self->func_per[i], mem[i]);
	for(size_t i=0; i< self-> num_layers-1; ++i)
		free(mem[i]);
	return mem[self->num_layers -1 ];
}
