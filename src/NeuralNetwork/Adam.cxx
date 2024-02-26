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
 *  \file Adam.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Mon 26 February 2024 - 17:23:42
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Optimizer.hxx"
#include <Eigen/Dense>
#include <iostream>
#include "Dense.hxx"


using namespace Eigen;

namespace NeuralNetwork {
  Adam::Adam(double _learning_rate, double _beta1, double _beta2, double _epsilon)
    : learning_rate{_learning_rate},
      beta1{_beta1},
      beta2{_beta2},
      epsilon{_epsilon},
      t{0}
  {
  }

  Adam::~Adam()
  {
  }

  void Adam::update(NeuralNetwork::Dense* layer, const MatrixXd& _output_grad)
  {
    t++;
    if(t == 1)
    {
      m_weight = MatrixXd::Zero(layer->get_weights().rows(), layer->get_weights().cols());
      v_weight = MatrixXd::Zero(layer->get_weights().rows(), layer->get_weights().cols());
      m_bias = VectorXd::Zero(layer->get_biases().rows());
      v_bias = VectorXd::Zero(layer->get_biases().rows());

      epsilon_bias = VectorXd::Constant(layer->get_biases().rows(), epsilon);
      epsilon_weight = MatrixXd::Constant(layer->get_weights().rows(), layer->get_weights().cols(), epsilon);
    }
    
    MatrixXd weights_grad = _output_grad * layer->get_inputs().transpose();
    MatrixXd biases_grad = _output_grad;

    m_weight = beta1 * m_weight + (1 - beta1) * weights_grad;
    v_weight = beta2 * v_weight + (1 - beta2) * weights_grad.cwiseProduct(weights_grad);

    m_bias = beta1 * m_bias + (1 - beta1) * biases_grad;
    v_bias = beta2 * v_bias + (1 - beta2) * biases_grad.cwiseProduct(biases_grad);

    MatrixXd m_weight_hat = m_weight / (1 - pow(beta1, t));
    MatrixXd v_weight_hat = v_weight / (1 - pow(beta2, t));

    MatrixXd m_bias_hat = m_bias / (1 - pow(beta1, t));
    MatrixXd v_bias_hat = v_bias / (1 - pow(beta2, t));

    layer->set_weights(layer->get_weights() - learning_rate *  m_weight_hat.cwiseQuotient(v_weight_hat.cwiseSqrt() + epsilon_weight));
    layer->set_biases(layer->get_biases() - learning_rate * m_bias_hat.cwiseQuotient((v_bias_hat.cwiseSqrt() + epsilon_bias)));
  }
}