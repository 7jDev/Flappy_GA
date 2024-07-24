#include "genetic.h"
/*static inline */void n_clean_up(neuron * clean) 
{
	free(clean->weights); 
}
/*static inline */ neuron initialize_neuron (size_t number_of_input )
{
	float * weights= malloc(sizeof(float) * number_of_input); 
	float bias = ((float)rand()/ (float)RAND_MAX) - 0.5;	
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
float compute_neuron(neuron * self, float * inputs , activation func)
{
	float sum = 0.0;  
	float result = 0.0; 
	for(size_t i=0; i< self->num_inputs; ++i)
	{
		sum += inputs[i] * self->weights[i];	
	} 
	sum += self->bias; 
	printf("%f\n", sum);
	switch(func)
	{
		case SIGMOID:
			result = sigmoid(sum);
		case RELU:
			result = relu(sum);
	} 
	return result; 
} 
layer initialize_layer(size_t number_of_input, size_t number_of_neurons)
{
	
}
