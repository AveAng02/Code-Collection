
#include <iostream>
#include <vector>
#include <ctime>



/////////////////////////////////////////////////////////////////////////////////////////////////

// node
class Neuron
{
public:

    Neuron()
    {
        bias = 0.0;
        weight.push_back(0.0);

        // generating a random tag to uniquely recognize a neuron
	    neuronID = 10000000 + std::rand() / (RAND_MAX / 99999999);
    }

    Neuron(std::vector<float> weight_, float bias_)
    {
        weight = weight_;
        bias = bias_;

        // generating a random tag to uniquely recognize a neuron
	    neuronID = 10000000 + std::rand() / (RAND_MAX / 99999999);
    }

    float compute_output(std::vector<float> input);
    void set_node(std::vector<float> weight_, float bias_);
    std::vector<float> get_weight();
    void set_weight(std::vector<float> val);
    float get_bias();
    void set_bias(float bias_);
    void print();

private:
    std::vector<float> weight;
    float bias;
    int neuronID;
};

float Neuron::compute_output(std::vector<float> input)
{
    float output = 0.0;

    for(int i = 0; i < weight.size(); i++)
    {
        output += (weight[i] * input[i]);
    }

    output += bias;

    return output;
}

void Neuron::set_node(std::vector<float> weight_, float bias_)
{
    weight = weight_;
    bias = bias_;
}

void Neuron::print()
{
    std::cout << "Neuron Tag : " << neuronID << std::endl;
    std::cout << "Weights : ";

    for(int i = 0; i < weight.size(); i++)
    {
        std::cout << weight[i] << ", ";
    }

    std::cout << "\nBias : " << bias << std::endl;
}

std::vector<float> Neuron::get_weight()
{
    return weight;
}

void Neuron::set_weight(std::vector<float> val)
{
    weight = val;
}

float Neuron::get_bias()
{
    return bias;
}

void Neuron::set_bias(float bias_)
{
    bias = bias_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

// Layer
class Layer
{
public:
    Layer()
    {
        Neuron newNode;
        node_list.push_back(newNode);

        // generating a random tag to uniquely recognize a neuron
	    layerID = 10000000 + std::rand() / (RAND_MAX / 99999999);
    }

    Layer(int n)
    {
        for(int i = 0; i < n; i++)
        {
            Neuron newNode;
            node_list.push_back(newNode);
        }

        // generating a random tag to uniquely recognize a neuron
	    layerID = 10000000 + std::rand() / (RAND_MAX / 99999999);
    }

    void set_neuron(std::vector<float> weight_, float bias_, int neuron_number);
    std::vector<float> get_layer_output(std::vector<float> input);
    std::vector<float> get_input_layer_output(std::vector<float> input);



private:
    std::vector<Neuron> node_list;
    float width;
    int layerID;
};

void Layer::set_neuron(std::vector<float> weight_, float bias_, int neuron_number)
{
    node_list[neuron_number].set_node(weight_, bias_);
}

std::vector<float> Layer::get_layer_output(std::vector<float> input)
{
    std::vector<float> output;

    for(int i = 0; i < node_list.size(); i++)
    {
        output.push_back(node_list[i].compute_output(input));
    }

    return output;
}

std::vector<float> Layer::get_input_layer_output(std::vector<float> input)
{
    std::vector<float> output;

    for(int i = 0; i < node_list.size(); i++)
    {
        output.push_back(node_list[i].compute_output(std::vector<float>({input[i]})));
    }

    return output;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

// Network
class Network
{
public:
    Network()
    {
        depth = 3;
        Layer newLayer;
        hidden.push_back(newLayer);
    }

    Network(int n)
    {
        // check if n >= 2
        depth = n;

        for(int i = 0; i < n - 2; i++)
        {
            Layer newLayer;
            hidden.push_back(newLayer);
        }
    }
    /*
    * Eventually I want to dynamically increase the depth of the network as required.
    * Also dynamically change the width of a layer as required.
    */

    void set_input_layer(std::vector<float>);

    // forward propagation
    std::vector<float> forward_propagation(std::vector<float>);


    // back propagatin
    void back_propagation();


private:
    Layer input;
    Layer output;
    std::vector<Layer> hidden;
    int depth; // vizualize what happens when this becomes float
    int networkID;
};

void Network::set_input_layer(std::vector<float> feed_forward)
{
    input.get_input_layer_output(feed_forward);
}

std::vector<float> Network::forward_propagation(std::vector<float> feed_forward)
{   
    feed_forward = input.get_layer_output(feed_forward);

    for(int i = 0; i < hidden.size(); i++)
    {
        feed_forward = hidden[i].get_layer_output(feed_forward);
    }

    return output.get_layer_output(feed_forward);
}




/////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Layer input(2);
    Layer middle(3);
    Layer output(1);

    // get input
    std::cout << "\nInput Layer :\n";
    input.set_neuron(std::vector<float>({1}), 0, 0);
    input.set_neuron(std::vector<float>({1}), 0, 1);

    std::vector<float> out = input.get_input_layer_output(std::vector<float>({5, 7}));
    
    for(int i = 0; i < out.size(); i++)
    {
        std::cout << out[i] << " ";
    }
    std::cout << "\n";
    
    // compute middle layer
    std::cout << "\nMiddle Layer :\n";
    middle.set_neuron(std::vector<float>({1, 0}), 0, 0);
    middle.set_neuron(std::vector<float>({1, 1}), 0, 1);
    middle.set_neuron(std::vector<float>({0, 1}), 0, 2);

    out = middle.get_layer_output(out);

    for(int i = 0; i < out.size(); i++)
    {
        std::cout << out[i] << " ";
    }
    std::cout << "\n";

    // compute output layer
    std::cout << "\nOutput Layer :\n";
    output.set_neuron(std::vector<float>({0, 1, 0}), 0, 0);

    out = output.get_layer_output(out);

    for(int i = 0; i < out.size(); i++)
    {
        std::cout << out[i] << " ";
    }
    std::cout << "\n";

    return 0;
}






