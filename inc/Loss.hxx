/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   Neural Network                                     :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 24/April/2024 by Durandnico   	    #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

#pragma once

/*! 
 *  \file Loss.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Wed 24 April 2024 - 14:40:59
 *
 *  \brief 
 *
 *
 */


// Inclusion des entetes de librairies
#include "global.hxx"
#include <Eigen/Dense>

using namespace Eigen;

namespace NeuralNetwork
{
  class Loss
  {
    private:
      /* data */
      std::function<double (const MatrixXd&, const MatrixXd&)> loss_batch;
      std::function<MatrixXd(const MatrixXd&, const MatrixXd&)> loss_batch_prime;


    public:
      Loss(std::function<double (const MatrixXd&, const MatrixXd&)> _loss_batch, std::function<MatrixXd(const MatrixXd&, const MatrixXd&)> _loss_batch_prime) 
        : loss_batch{_loss_batch},
          loss_batch_prime{_loss_batch_prime}
      {};

      
    #if 0
      double operator()(const VectorXd& y_true, const VectorXd& y_pred);
      VectorXd prime(const VectorXd& y_true, const VectorXd& y_pred);
    #endif

      inline virtual double operator()(const MatrixXd& y_true, const MatrixXd& y_pred) 
      {
        return loss_batch(y_true, y_pred);
      }

      inline virtual MatrixXd prime(const MatrixXd& y_true, const MatrixXd& y_pred)
      {
        return loss_batch_prime(y_true, y_pred);
      }
  };

}