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
 *  \file MSE.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Wed 24 April 2024 - 14:53:16
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
  inline double mean_squared_error(const VectorXd& y_true, const VectorXd& y_pred)
  {
    return (y_true - y_pred).squaredNorm() / y_true.size();
  }

  inline VectorXd mean_squared_error_prime(const VectorXd& y_true, const VectorXd& y_pred)
  {
    return 2 * (y_pred - y_true) / y_true.size();
  }
  #endif

  /* version pour les batch */
  inline VectorXd mean_squared_error(const MatrixXd& y_true, const MatrixXd& y_pred)
  {
    return (y_true - y_pred).rowwise().squaredNorm() / y_true.cols();
  }

  inline MatrixXd mean_squared_error_prime(const MatrixXd& y_true, const MatrixXd& y_pred)
  {
    return 2 * (y_pred - y_true) / y_true.cols();
  }

  class MSE
    : public Loss
  {
    
    public:
      MSE()
        : Loss{mean_squared_error, mean_squared_error_prime}
      { 
      }
  };

}
