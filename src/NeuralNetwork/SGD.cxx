/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   Neural Network                                     :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 26/February/2024 by Durandnico   	  #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

/*! 
 *  \file SGD.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Mon 26 February 2024 - 17:20:12
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Optimizer.hxx"
#include "Dense.hxx"
#include <Eigen/Dense>
#include <iostream>

namespace NeuralNetwork
{
  SGD::SGD(double _learning_rate)
    : learning_rate{_learning_rate}
  {
  }

  SGD::~SGD()
  {
  }

  void SGD::update(NeuralNetwork::Dense* layer, const MatrixXd& output_grad)
  {
    MatrixXd weights_grad = output_grad * layer->get_inputs().transpose();
   
    layer->set_weights(layer->get_weights() - learning_rate * weights_grad);
    layer->set_biases(layer->get_biases() - learning_rate * output_grad);
  }
}