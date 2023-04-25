
#include <iostream>
#include <vector>
#include <ctime>




// node
class Node
{
public:

    Node()
    {
        bias = 0.0;
        weight.push_back(0.0);

        // generating a random tag to uniquely recognize a neuron
	    tag = 10000000 + std::rand() / (RAND_MAX / 99999999);
    }

    Node(std::vector<float> weight_, float bias_)
    {
        weight = weight_;
        bias = bias_;

        // generating a random tag to uniquely recognize a neuron
	    tag = 10000000 + std::rand() / (RAND_MAX / 99999999);
    }

    float compute_output(std::vector<float> input);
    void set_node(std::vector<float> weight_, float bias_);
    float get_neuron_val();
    void set_neuron_val(float val);
    void print();

private:
    std::vector<float> weight;
    float bias;
    int tag;
};

float Node::compute_output(std::vector<float> input)
{
    float output = 0.0;

    for(int i = 0; i < weight.size(); i++)
    {
        output += (weight[i] * input[i]);
    }

    output += bias;

    return output;
}

void Node::set_node(std::vector<float> weight_, float bias_)
{
    weight = weight_;
    bias = bias_;
}

void Node::print()
{
    std::cout << "Neuron Tag : " << tag << std::endl;
    std::cout << "Weights : ";

    for(int i = 0; i < weight.size(); i++)
    {
        std::cout << weight[i] << ", ";
    }

    std::cout << "\nBias : " << bias << std::endl;
}





// Layer
class Layer
{
public:
    Layer()
    {
        Node newNode;
        node_list.push_back(newNode);

        // generating a random tag to uniquely recognize a neuron
	    tag = 10000000 + std::rand() / (RAND_MAX / 99999999);
    }

    Layer(int n)
    {
        for(int i = 0; i < n; i++)
        {
            Node newNode;
            node_list.push_back(newNode);
        }

        // generating a random tag to uniquely recognize a neuron
	    tag = 10000000 + std::rand() / (RAND_MAX / 99999999);
    }

    void set_neuron(std::vector<float> weight_, float bias_, int neuron_number);
    std::vector<float> get_layer_output(std::vector<float> input);
    std::vector<float> get_input_layer_output(std::vector<float> input);

private:
    std::vector<Node> node_list;
    int tag;
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


// Network
class Network
{
public:


private:

};








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






