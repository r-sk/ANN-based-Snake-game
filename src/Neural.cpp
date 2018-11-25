#include <fstream>
#include "Neural.h"

Neural::Neural(int in, int out, int lyr, int hn, float lrate)
{
    no_of_inputs = in;
    no_of_outputs = out;
    no_of_layers = lyr;
    no_of_hid_nodes = hn;
    learning_rate = lrate;

    no_of_weights = 0;

    layer = new Layer[lyr];

    //INPUT LAYER FORMATION

    layer[0].no_of_nodes = no_of_inputs;
    layer[0].node = new Node[no_of_inputs];

    for(int i = 0; i < no_of_inputs; i++)
    {
        (layer[0].node[i]).node_inputs = 1;
        no_of_weights++;

        (layer[0].node[i]).weight = new float[1];
        (layer[0].node[i]).input = new float[1];
        (layer[0].node[i]).error = new float[1];

        (layer[0].node[i]).error[0] = 0.0;                          // set 0.0 error initially

    }

    std::cout << "No of weights up to Input layer: " <<no_of_weights<<std::endl;

    //HIDDEN LAYERS FORMATION

    for(int i = 1; i <  lyr - 1; i++)
    {
//           std::cout << "inside hidden layer formation" << std::endl;

        layer[i].no_of_nodes = hn;
        layer[i].node = new Node[hn];

        int layer_inputs = layer[i - 1].no_of_nodes;

//           std::cout << "hidden layer loop i" << std::endl;

        for(int j = 0; j < hn; j++)
        {
            (layer[i].node[j]).node_inputs = layer_inputs;

//               std::cout << "hidden layer loop j" << std::endl;

            (layer[i].node[j]).weight = new float[layer_inputs];
            (layer[i].node[j]).input = new float[layer_inputs];
            (layer[i].node[j]).error = new float[layer_inputs];

            for(int e = 0; e < layer_inputs ; e++)
            {
                (layer[i].node[j]).error[e] = 0.0;
                no_of_weights++;
            }
        }
    }

    std::cout << "No of weights up to Hidden layer: " <<no_of_weights<<std::endl;

    //OUTPUT LAYER FORMATION

    int op_layer_inputs = layer[lyr - 2].no_of_nodes;
    layer[lyr - 1].no_of_nodes = out;
    layer[lyr - 1].node = new Node[out];

    for(int i = 0; i < out; i++)
    {
//           std::cout << "inside output layer formation" << std::endl;
        (layer[lyr - 1].node[i]).node_inputs = op_layer_inputs;

        (layer[lyr - 1].node[i]).weight = new float[op_layer_inputs];
        (layer[lyr - 1].node[i]).input = new float[op_layer_inputs];
        (layer[lyr - 1].node[i]).error = new float[op_layer_inputs];

        for(int e = 0; e < op_layer_inputs; e++)
        {
            (layer[lyr - 1].node[i]).error[e] = 0.0;
            no_of_weights++;
        }

    }

    std::cout << "Total No of weights: " <<no_of_weights<<std::endl;

    v_weight = new float[no_of_weights];


}

void Neural::put_weights(float *wt) //Puts the weights into the network
{
    int n = 0;
    for(int i = 0; i < no_of_layers; i++)
    {
        for(int j = 0; j < layer[i].no_of_nodes; j++)
        {
            for(int k = 0; k < (layer[i].node[j]).node_inputs; k++)
            {
                (layer[i].node[j]).weight[k] = wt[n];
                n++;
            }
        }
    }
}

void Neural::init()             //Generates random weights
{
    for(int i = 0; i < no_of_weights; i++)
    {
        v_weight[i] = (float)rand() / (float)RAND_MAX;
    }

    put_weights(v_weight);
}

void Neural::display_formation()    //Display Neural Architecture
{
    std::cout<<"\n\n";
    std::cout.width(20);
    std::cout.fill(' ');
    std::cout<<"Input";

    std::cout.width(20);
    std::cout.fill(' ');
    std::cout<<"Weight";

    std::cout.width(20);
    std::cout.fill(' ');
    std::cout<< "Error";

    std::cout.width(20);
    std::cout.fill(' ');
    std::cout<< "Output" << std::endl;

    std::cout << "---------------------------------------------------------------------------------------------"<< std::endl;

    for(int i=0; i<no_of_layers; i++)
    {
        for(int j=0; j<layer[i].no_of_nodes; j++)
        {
            std::cout<<"Layer: "<<i<<" Node: "<<j<<std::endl<<std::endl;

            for(int k=0; k<layer[i].node[j].node_inputs; k++)
            {
                //std::cout << "\t\t" <<(layer[i].node[j]).input[k] << "\t\t" << (layer[i].node[j]).weight[k] << "\t\t" << (layer[i].node[j]).error[k] << "\t\t" << (layer[i].node[j]).output << std::endl;
                std::cout.width(20);
                std::cout.fill(' ');
                std::cout<<(layer[i].node[j]).input[k];

                std::cout.width(20);
                std::cout.fill(' ');
                std::cout<<(layer[i].node[j]).weight[k];

                std::cout.width(20);
                std::cout.fill(' ');
                std::cout<< (layer[i].node[j]).error[k];

                std::cout.width(20);
                std::cout.fill(' ');
                std::cout<< (layer[i].node[j]).output << std::endl;
            }

            std::cout << "---------------------------------------------------------------------------------------------"<< std::endl;

        }

    }



}

void Neural::display_weights()
{
    std::cout<<"Weights are: "<<std::endl;

    for(int i = 0; i < no_of_weights; i++)
    {
        std::cout<<i<< " :\t" << v_weight[i] << std::endl;
    }


}

float* Neural::feed(float* input)   //Inputs the neural network to obtain output
{

    int n = 0;
    float *output;
    for(int i = 0; i < no_of_layers; i++)
    {
        output = new float[layer[i].no_of_nodes];    //(no_of_nodes+1) kina yesma ??

        for(int j = 0; j < layer[i].no_of_nodes; j++)
        {
            float sum = 0.0;

            if(i == 0)      //CASE OF INPUT LAYER
            {
                (layer[i].node[j]).input[0] = input[j];
                sum = (layer[i].node[j]).weight[0] * input[j];
            }

            else            //CASE OF OTHER LAYERS
            {
                for(int k = 0; k < (layer[i].node[j]).node_inputs; k++)
                {
                    (layer[i].node[j]).input[k] = input[k];
                    sum += (layer[i].node[j]).weight[k] * input[k];
                }
            }

            output[j] = 1/(1+exp(-sum)) ;           //Using sigmoid function as Activation function

            (layer[i].node[j]).output = output[j];
        }


        input = output;
    }

    std::cout<<output[1]<<std::endl;

    return output;
}

float Neural::get_weighted_error(int l, int in)
{
    float sum = 0.0;
    for(int j = 0; j < layer[l].no_of_nodes; j++)
    {
        float error  = (layer[l].node[j]).error[in];
        float weight = (layer[l].node[j]).weight[in];
        sum += error * weight;
    }
    return sum;
}

void Neural::learn(float dout)
{
    int tmp = no_of_layers - 1;

    for(int j = 0; j < layer[tmp].no_of_nodes; j++)
    {
        for(int k = 0; k < (layer[tmp].node[j]).node_inputs; k++)
        {
            (layer[tmp].node[j]).error[k] = dout;

//               std::cout << (layer[tmp].node[j]).weight[k] <<"\t"<< learning_rate <<"\t"<< (layer[tmp].node[j]).input[k] <<"\t"<< (layer[tmp].node[j]).error[k]<<"\t"<<std::endl;

//               std::cout<<"Initial Weight:\t"<<(layer[tmp].node[j]).weight[k]<<std::endl;
            (layer[tmp].node[j]).weight[k] += learning_rate * (layer[tmp].node[j]).input[k] * (layer[tmp].node[j]).error[k];
//               std::cout<<"Final Weight:\t"<<(layer[tmp].node[j]).weight[k]<<std::endl;
        }
    }

    //std::cout<<"Weight changer's part 1 completed."<<std::endl;

    for(int i = no_of_layers - 2; i >= 0; i--)
    {

        //std::cout<<"Inside weight changer's part 2 i"<<std::endl;

        for(int j = 0; j < layer[i].no_of_nodes ; j++)
        {
            float sum = get_weighted_error(i + 1, j);
            for(int k = 0; k < (layer[i].node[j]).node_inputs; k++)
            {
                (layer[i].node[j]).error[k] = sum;

                //std::cout<<"Initial Weight:\t"<<(layer[i].node[j]).weight[k]<<"\t";
                (layer[i].node[j]).weight[k] += learning_rate * (layer[i].node[j]).input[k] * (layer[i].node[j]).error[k];
                //std::cout<<"Final Weight:\t"<<(layer[i].node[j]).weight[k]<<"\t";
                //std::cout<<learning_rate <<"\t"<< (layer[i].node[j]).input[k] <<"\t"<< (layer[i].node[j]).error[k]<<"\t"<<std::endl;
                //while(1);
            }
        }
    }

}
