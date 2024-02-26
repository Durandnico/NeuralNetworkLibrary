#pragma once

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
 *  \file Dense.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Fri 23 February 2024 - 15:57:47
 *
 *  \brief 
 *    file containing the definition of the Dense class 
 *
 */

// Inclusion des entetes de librairies
#include <Eigen/Dense>
using namespace Eigen;

namespace NeuralNetwork
{

class Dense
{
protected:
  /* data */
  MatrixXd weights;
  MatrixXd biases;
  MatrixXd inputs;

  int n_inputs;
  int n_outputs;  

public:

  Dense();
  Dense(const int _N_INPUTS, const int _N_OUTPUTS);
  ~Dense();

  virtual VectorXd forward(const MatrixXd& inputs);
  virtual VectorXd backward(const MatrixXd& output_grad, const double learning_rate);
};

}