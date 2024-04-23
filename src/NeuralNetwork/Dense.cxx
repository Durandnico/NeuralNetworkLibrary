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



MatrixXd NeuralNetwork::Dense::forward(const MatrixXd& inputs)
{
  ASSERT(inputs.rows() == weights.cols());

  this->inputs = inputs;
  MatrixXd tmp = weights * inputs;

  /* add the biaises to all cols*/
  for (int i = 0; i < tmp.cols(); i++)
  {
    tmp.col(i) +=  biases;
  }

  return tmp;
}


MatrixXd NeuralNetwork::Dense::backward(const MatrixXd& output_grad)
{
  std::cout << "\n\n DENSE BACKPROP\n\n"; 
  ASSERT(output_grad.rows() == n_outputs);
  MatrixXd output_grad_{n_inputs ,output_grad_.rows()};

  optimizer->update(this, output_grad);

  return this->weights.transpose() * output_grad;
}

