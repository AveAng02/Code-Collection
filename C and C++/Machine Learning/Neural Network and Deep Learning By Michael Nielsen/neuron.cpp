
#include <iostream>
#include <vector>


namespace CodeBrain
{
	struct Neuron
	{
		std::vector<float> weights;
		std::vector<float> inputs;
		float bias;
		float output;
	};
	
	struct Perceptron : Neuron
	{
		Perceptron(std::vector<float> weights_, std::vector<float> inputs_, float bias_)
		{
			this->weights = weights_;
			this->inputs = inputs_;
			this->bias = bias_;
		}
	};
	
	struct sigmoidNeuron : Neuron
	{
		
	};
	
	float activation(Neuron& neu)
	{
		// output = weights * inputs + bias
		float sum = 0.0;
		
		for(int i = 0; i < neu.weights.size(); i++)
		{
			sum += neu.weights[i] * neu.inputs[i];
		}
		
		sum += neu.bias;
		
		neu.output = sum;
		
		return sum;
	}
	
}


int main()
{
	CodeBrain::Perceptron cell(std::vector<float>{-2, 3, 1, 0, 4, 2}, std::vector<float>{0, 1, 1, 0, 1, 0}, -3);
	
	std::cout << "Result = " << activation(cell) << std::endl;
	
	return 0;
}




