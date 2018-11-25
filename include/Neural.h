#ifndef NEURAL_H
#define NEURAL_H
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>

typedef struct
{
    int node_inputs;
	float *weight;
	float *input;
	float *error;
	float output;
} Node;

typedef struct
{
	int no_of_nodes;
	Node *node;
} Layer;

class Neural
{
private:
    int no_of_inputs;
    int no_of_outputs;
    int no_of_layers;
    int no_of_hid_nodes;
    float learning_rate;

    int no_of_weights;
    Layer *layer;
    float *v_weight;

public:
    Neural(int in, int out, int lyr, int hn, float lrate);
    void put_weights(float *wt);
    void init();
    void display_formation();
    void display_weights();
    float* feed(float* input);
    float get_weighted_error(int l, int in);
    void learn(float dout);



};


#endif // NEURAL_H
