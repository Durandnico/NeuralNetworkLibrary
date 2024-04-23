/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   Neural Network                                     :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 27/February/2024 by Durandnico   	  #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

/*! 
 *  \file NeuralNetwork.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Tue 27 February 2024 - 01:30:22
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "NeuralNetwork.hxx"
#include "Activation.hxx"
#include "Dense.hxx"
#include "Optimizer.hxx"
#include "global.hxx"
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;

namespace NeuralNetwork
{
  NeuralNetwork::NeuralNetwork(std::vector<Dense*> layers)
    : layers{layers}
  {
  }

  NeuralNetwork::~NeuralNetwork()
  {
    for(auto layer : layers)
    {
      delete layer;
    }
  }

  std::vector<Dense*> NeuralNetwork::get_layers()
  {
    return layers;
  }


  MatrixXd NeuralNetwork::forward(const MatrixXd& inputs)
  {
    MatrixXd outputs = inputs;

    for(auto layer : layers)  {
      outputs = layer->forward(outputs);
    }

    return outputs;
  }


  void NeuralNetwork::backward(MatrixXd& output_grad)
  {
    // ASSERT(output_grad.cols() == layers.back()->get_n_outputs());

    for(auto layer = layers.rbegin(); layer != layers.rend(); layer++)
    {
      std::cout << "input gradient --->: " << output_grad << std::endl;
      output_grad = (*layer)->backward(output_grad);
    }
  }

  void NeuralNetwork::fit(const MatrixXd& inputs, const MatrixXd& targets, const int n_epochs, const int batch_size)
  {
    const int n_samples = inputs.rows();
    const int n_batches = n_samples / batch_size;

    std::cout << "n_samples: " << n_samples << std::endl;
    std::cout << "n_batches: " << n_batches << std::endl;
    for(int epoch = 0; epoch < n_epochs; epoch++)
    {
      for(int batch = 0; batch < n_batches; batch++)
      {
        const int start = batch * batch_size;
        
        const MatrixXd inputs_batch = inputs.middleRows(start, batch_size);
        const MatrixXd targets_batch = targets.middleRows(start, batch_size);

        std::cout << "inputs_batch: " << inputs_batch << std::endl;
        std::cout << "targets_batch: " << targets_batch << std::endl;

        const MatrixXd outputs = forward(inputs_batch.transpose()).transpose();
        std::cout << "outputs predict: " << outputs << std::endl;
      
        MatrixXd output_grad = loss_prime_fct(outputs, targets_batch).transpose();
        std::cout << "output_grad: " << output_grad << std::endl;
        backward(output_grad);
      }
    }
  }

  double NeuralNetwork::validate(const MatrixXd& inputs, const MatrixXd& targets)
  {
    const MatrixXd outputs = forward(inputs);
    return loss(outputs, targets);
  }
/*
  double NeuralNetwork::accuracy(const MatrixXd& inputs, const MatrixXd& targets)
  {
    const MatrixXd outputs = forward(inputs);
    const MatrixXd predictions = outputs.unaryExpr([](double x) { return x > 0.5 ? 1 : 0; });
    const MatrixXd correct = (predictions.array() == targets.array()).cast<double>();
    return correct.sum() / correct.size();
  }

  double NeuralNetwork::recall(const MatrixXd& inputs, const MatrixXd& targets)
  {
    const MatrixXd outputs = forward(inputs);
    const MatrixXd predictions = outputs.unaryExpr([](double x) { return x > 0.5 ? 1 : 0; });
    const MatrixXd true_positives = (predictions.array() == 1 && targets.array() == 1).cast<double>();
    const MatrixXd false_negatives = (predictions.array() == 0 && targets.array() == 1).cast<double>();
    return true_positives.sum() / (true_positives.sum() + false_negatives.sum());
  }


  MatrixXd NeuralNetwork::confusion_matrix(const MatrixXd& inputs, const MatrixXd& targets)
  {
    const MatrixXd outputs = forward(inputs);
    const MatrixXd predictions = outputs.unaryExpr([](double x) { return x > 0.5 ? 1 : 0; });
    const MatrixXd true_positives = (predictions.array() == 1 && targets.array() == 1).cast<double>();
    const MatrixXd false_positives = (predictions.array() == 1 && targets.array() == 0).cast<double>();
    const MatrixXd true_negatives = (predictions.array() == 0 && targets.array() == 0).cast<double>();
    const MatrixXd false_negatives = (predictions.array() == 0 && targets.array() == 1).cast<double>();

    MatrixXd confusion_matrix(2, 2);
    confusion_matrix << true_positives.sum(), false_positives.sum(),
                        false_negatives.sum(), true_negatives.sum();

    return confusion_matrix;
  }
*/
  double NeuralNetwork::loss(const MatrixXd& inputs, const MatrixXd& targets)
  {
    return loss_fct(inputs, targets);
  }

  MatrixXd NeuralNetwork::predict(const MatrixXd& inputs)
  {
    // ASSERT(inputs.cols() == layers[0]->get_n_inputs());
    return forward(inputs);
  }
  
} // namespace NeuralNetwork