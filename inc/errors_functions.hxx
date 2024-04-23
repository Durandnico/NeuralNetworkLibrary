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
 *  \file errors_functions.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Fri 23 February 2024 - 22:49:53
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include <Eigen/Dense>

using namespace Eigen;

namespace NeuralNetwork
{

  double inline mean_squared_error(const MatrixXd& y_true, const MatrixXd& y_pred)
  {
    return (y_true - y_pred).squaredNorm() / y_true.size();
  }

  MatrixXd inline mean_squared_error_prime(const MatrixXd& y_true, const MatrixXd& y_pred)
  {
    return 2 * (y_pred - y_true) / y_true.size();
  }

  double inline cross_entropy(const MatrixXd& y_true, const MatrixXd& y_pred)
  {
    return - (y_true.array() * y_pred.array().log() + (1 - y_true.array()) * (1 - y_pred.array()).log()).sum() / y_true.size();
  }

  Eigen::VectorXd inline cross_entropy_prime(const MatrixXd& y_true, const MatrixXd& y_pred)
  {
    return - (y_true.array() / y_pred.array() - (1 - y_true.array()) / (1 - y_pred.array())) / y_true.size();
  }

}