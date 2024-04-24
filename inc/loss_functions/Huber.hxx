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
 *  \file Huber.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Wed 24 April 2024 - 15:28:49
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

  inline VectorXd huber(const MatrixXd& y_true, const MatrixXd& y_pred, const double epsi = 1.0)
  {
    const int cols = y_pred.cols();
    VectorXd diff = (y_true - y_pred).rowwise().sum() / cols;
    
    for(double& err: diff)
    {
      if(abs(err) < epsi)
        err = 0.5 * err * err;

      else
        err = epsi * (abs(err) - 0.5 * epsi);

    }
    return diff;
  }

  inline MatrixXd huber_prime(const MatrixXd& y_true, const MatrixXd& y_pred, const double delta = 1.0)
  {
    MatrixXd diff = y_true - y_pred;
    MatrixXd loss = (diff.array().abs() < delta).select(diff, delta * diff.array().sign());
    return loss / y_true.cols();
  }

  class Huber
    : public Loss
  {
    private:
      /* data */
      double m_delta;
      
    public:
      Huber(double _delta = 1.0)
        : Loss(nullptr, nullptr),
          m_delta{_delta}
      {};

      VectorXd operator()(const MatrixXd& y_true, const MatrixXd& y_pred) override
      {
        return huber(y_true, y_pred, m_delta);
      }

      MatrixXd prime(const MatrixXd& y_true, const MatrixXd& y_pred) override
      {
        return huber_prime(y_true, y_pred, m_delta);
      }
  };

}