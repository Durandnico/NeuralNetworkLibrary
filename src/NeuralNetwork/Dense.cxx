/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   Neural Network                                     :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 23/February/2024 by Durandnico      #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

/*! 
 *  \file Dense.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Fri 23 February 2024 - 16:11:48
 *
 *  \brief 
 *    file containing the implementation of the Dense class
 *
 */

// Inclusion des entetes de librairies
#include "Dense.hxx"
#include "Optimizer.hxx"
#include "global.hxx"
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;

NeuralNetwork::Dense::Dense(const int n_inputs, const int n_outputs, Optimizer* optimizer)
  : weights{MatrixXd::Random(n_outputs, n_inputs)},
    biases{VectorXd::Random(n_outputs)},
    optimizer{optimizer},
    n_inputs{n_inputs},
    n_outputs{n_outputs}
{
  
}

NeuralNetwork::Dense::Dense()
{
}



NeuralNetwork::Dense::~Dense()
{
  delete optimizer;
}



VectorXd NeuralNetwork::Dense::forward(const MatrixXd& inputs)
{
  ASSERT(inputs.size() == n_inputs);

  this->inputs = inputs;
  return weights * inputs + biases;
}


VectorXd NeuralNetwork::Dense::backward(const MatrixXd& output_grad)
{
  ASSERT(output_grad.size() == n_outputs);

  optimizer->update(this, output_grad);
  return weights.transpose() * output_grad;
}

