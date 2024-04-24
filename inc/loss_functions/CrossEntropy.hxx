/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   Neural Network                                     :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 24/April/2024 by Durandnico         #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

#pragma once

/*! 
 *  \file CrossEntropy.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Wed 24 April 2024 - 15:13:56
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Loss.hxx"
#include <Eigen/Dense>

using namespace Eigen;

namespace NeuralNetwork
{

#if 0
  double cross_entropy(const VectorXd& y_true, const VectorXd& y_pred)
  {
    return - (y_true.array() * y_pred.array().log() + (1 - y_true.array()) * (1 - y_pred.array()).log()).sum() / y_true.size();
  }

  Eigen::VectorXd cross_entropy_prime(const VectorXd& y_true, const VectorXd& y_pred)
  {
    return - (y_true.array() / y_pred.array() - (1 - y_true.array()) / (1 - y_pred.array())) / y_true.size();
  }
#endif

  inline VectorXd cross_entropy(const MatrixXd& y_true, const MatrixXd& y_pred)
  {
    return - (y_true.array() * y_pred.array().log() + (1 - y_true.array()) * (1 - y_pred.array()).log()).rowwise().sum() / y_true.cols();
  }

  inline MatrixXd cross_entropy_prime(const MatrixXd& y_true, const MatrixXd& y_pred)
  {
    return - (y_true.array() / y_pred.array() - (1 - y_true.array()) / (1 - y_pred.array())) / y_true.cols();
  }

  class CrossEntropy
    : public Loss
  {
    public:
      CrossEntropy()
        : Loss{cross_entropy, cross_entropy_prime}
      {
      }

  };
}