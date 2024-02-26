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

constexpr double learning_rate = 0.01;
constexpr int epochs = 5000;
constexpr double alpha = 0.01;

int main()
{

  srand(time(NULL));

   /* creating neural network for XOR */
  NeuralNetwork::Dense* NN[] = {
    new NeuralNetwork::Dense(2, 3, new NeuralNetwork::Adam{}),
    // new NeuralNetwork::Tanh{},
    // new NeuralNetwork::Relu{},
    new NeuralNetwork::LeakyRelu{alpha},
    new NeuralNetwork::Dense(3, 1, new NeuralNetwork::Adam{}),
    new NeuralNetwork::Sigmoid{}
  };


  /* training data */
  Eigen::MatrixXd X(4, 2);
  X << 0, 0,
       0, 1,
       1, 0,
       1, 1;

  Eigen::MatrixXd y(4, 1);
  y << 0, 1, 1, 0;

  /* training */
  std::vector<double> losses;
  losses.reserve(epochs);
  for (int i = 0; i < epochs; i++)
  {
    double loss = 0;

    for(int j = 0; j < 4; j++)
    {
      Eigen::VectorXd inputs = X.row(j);
      Eigen::VectorXd target = y.row(j);

      /* forward */
      for (auto layer : NN)
      {
        inputs = layer->forward(inputs);
      }

      /* loss */
      loss += NeuralNetwork::mean_squared_error(inputs, target);

      /* backward */
      Eigen::VectorXd grad = NeuralNetwork::mean_squared_error_prime(target, inputs);
      // NeuralNetwork::Adam{learning_rate, 0.9, 0.999, 1e-8};
      // NeuralNetwork::SGD optimizer(learning_rate);

      /* loop from last to first*/
      for(int i = 3; i >= 0; i--)
      {
        grad = NN[i]->backward(grad);
      }
    }

    loss /= 4;
    losses.emplace_back(loss);
  }

  // printf("losses: [ ");
  // for (double l : losses)
  // {
  //   printf("%f, ", l);
  // }
  // putchar(']');
  // putchar('\n');

  /* testing */
  for (int i = 0; i < 4; i++)
  {
    Eigen::VectorXd inputs = X.row(i);
    Eigen::VectorXd target = y.row(i);

    for (auto layer : NN)
    {
      inputs = layer->forward(inputs);
    }

    printf("target: %f, prediction: %f\n", target(0), inputs(0));
  }

  for (NeuralNetwork::Dense* layer : NN)
  {
    delete layer;
  }  

  return 0;
}
