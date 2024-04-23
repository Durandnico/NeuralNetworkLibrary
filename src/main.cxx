#include <Eigen/Dense>
#include <iostream>
#include <cmath>
#include <vector>

#include "global.hxx"
#include "Dense.hxx"
#include "errors_functions.hxx"
#include "Sigmoid.hxx"
#include "Tanh.hxx"
#include "Relu.hxx"
#include "LeakyRelu.hxx"
#include "Optimizer.hxx"

#include "NeuralNetwork.hxx"
#include "NeuralNetworkBuilder.hxx"

constexpr double learning_rate = 0.01;
constexpr int epochs = 5000;
constexpr double alpha = 0.01;

int main()
{

  srand(time(NULL));

  NeuralNetwork::NeuralNetwork NN = NeuralNetwork::NeuralNetworkBuilder()
    .set_hyperparametre_sgd()
    .add_input_layer(2)
    .add_hidden_layer(3).add_leakyRelu(alpha)
    .add_output_layer(1).add_sigmoid()
    .build();


  /* training data */
  Eigen::MatrixXd X(4, 2);
  X << 0, 0,
       0, 1,
       1, 0,
       1, 1;

  Eigen::MatrixXd y(4, 1);
  y << 0, 1, 1, 0;

  /* training */
  NN.fit(X,y, 10000, 4);


  /* testing */
  for (int i = 0; i < 4; i++)
  {
    Eigen::VectorXd inputs = X.row(i);
    Eigen::VectorXd target = y.row(i);

    for (auto layer : NN.get_layers())
    {
      inputs = layer->forward(inputs);
    }

    printf("target: %f, prediction: %f\n", target(0), inputs(0));
  }
  return 0;
}
