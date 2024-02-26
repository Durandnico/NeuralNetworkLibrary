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
 *  \file Activation.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Fri 23 February 2024 - 16:33:02
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "global.hxx"
#include "Dense.hxx"
#include <Eigen/Dense>

using namespace Eigen;

namespace NeuralNetwork
{
  
  class Activation
    : public Dense
  {
    private:
      /* data */
      std::function<double(const double)> activation;
      std::function<double(const double)> activation_prime;

    public:
      Activation( std::function<double(const double)> , std::function<double(const double)>);
      ~Activation();

      VectorXd forward(const MatrixXd& inputs) override;
      VectorXd backward(const MatrixXd& output_grad, const double learning_rate) override;
  };
}