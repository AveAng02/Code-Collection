
#include <iostream>
#include <vector>


// node
class Node
{
public:

    Node()
    {
        bias = 0.0;
        weight.push_back(0.0);
    }

    Node(std::vector<float> weight_, float bias_)
    {
        weight = weight_;
        bias = bias_;
    }

    float compute_output(std::vector<float> input);
    void set_node(std::vector<float> weight_, float bias_);

private:
    float output;
    std::vector<float> weight;
    float bias;
};


float Node::compute_output(std::vector<float> input)
{
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




// Layer
class Layer
{
public:
    Layer()
    {
        Node newNode;
        node_list.push_back(newNode);
    }

    Layer(int n)
    {
        Node newNode;

        for(int i = 0; i < n; i++)
        {
            node_list.push_back(newNode);
        }
    }

    void set_neuron(std::vector<float> weight_, float bias_, int neuron_number);
    std::vector<float> get_layer_output(std::vector<float> input);

private:
    std::vector<Node> node_list;
};


void Layer::set_neuron(std::vector<float> weight_, float bias_, int neuron_number)
{
    node_list[neuron_number].set_node(weight_, bias_);
}

std::vector<float> Layer::get_layer_output(std::vector<float> input)
{
    std::vector<float> output;

    for(int i = 0; i < input.size(); i++)
    {
        output.push_back(node_list[i].compute_output(input));
    }

    return output;
}



int main()
{
    Layer input(2);
    Layer middle(3);
    Layer output(1);

    // get input
    input.set_neuron(std::vector<float>(1), 0, 0);
    input.set_neuron(std::vector<float>(1), 0, 1);

    std::vector<float> out = input.get_layer_output(std::vector<float>(5, 6));

    for(int i = 0; i < out.size(); i++)
    {
        std::cout << out[i] << std::endl;
    }

    // compute middle layer
    middle.set_neuron(std::vector<float>(0, 1), 0, 0);
    middle.set_neuron(std::vector<float>(1, 1), 0, 1);
    middle.set_neuron(std::vector<float>(0, 1), 0, 2);

    out = middle.get_layer_output(out);

    for(int i = 0; i < out.size(); i++)
    {
        std::cout << out[i] << std::endl;
    }

    // compute output layer
    output.set_neuron(std::vector<float>(0, 1, 0), 0, 0);

    out = output.get_layer_output(out);

    for(int i = 0; i < out.size(); i++)
    {
        std::cout << out[i] << std::endl;
    }

    return 0;
}






