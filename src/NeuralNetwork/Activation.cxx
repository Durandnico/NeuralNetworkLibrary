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
 *  \file Activation.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Fri 23 February 2024 - 21:53:28
 *
 *  \brief 
 *    file containing the implementation of the Activation class
 *
 *
 */

// Inclusion des entetes de librairies
#include "Activation.hxx"
#include "global.hxx"
#include "Dense.hxx"
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;

NeuralNetwork::Activation::Activation( std::function<double(const double)> activation, std::function<double(const double)> activation_prime)
  : activation{activation},
    activation_prime{activation_prime}
{

}



NeuralNetwork::Activation::~Activation()
{
  
}


VectorXd NeuralNetwork::Activation::forward(const MatrixXd& inputs) 
{
  this->inputs = inputs;
  return inputs.unaryExpr(activation);
}

VectorXd NeuralNetwork::Activation::backward(const MatrixXd& output_grad, const double learning_rate)
{
  (void)learning_rate;
  return output_grad.cwiseProduct(inputs.unaryExpr(activation_prime));
}
