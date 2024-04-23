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
#include "Optimizer.hxx"
#include "global.hxx"


using namespace Eigen;

namespace NeuralNetwork
{

class Optimizer;

class Dense
{
protected:
  /* data */
  MatrixXd weights;
  MatrixXd biases;
  MatrixXd inputs;
  Optimizer* optimizer;

  int n_inputs;
  int n_outputs;  

public:
  Dense();
  Dense(const int _N_INPUTS, const int _N_OUTPUTS, Optimizer*);
  ~Dense();

  virtual MatrixXd forward(const MatrixXd& inputs);
  virtual MatrixXd backward(const MatrixXd& output_grad);

  inline MatrixXd& get_inputs() { return inputs; } 
  inline MatrixXd& get_weights() { return weights; }
  inline MatrixXd& get_biases() { return biases; }

  inline void set_weights(const MatrixXd& _weights) { weights = _weights; }
  inline void set_biases(const MatrixXd& _biases) { biases = _biases; }
};

}