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
 *  \file MAE.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Wed 24 April 2024 - 21:44:54
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

  inline double mae(const MatrixXd& labels, const MatrixXd& predicted) {
    // Assurez-vous que les dimensions des matrices correspondent
    ASSERT(predicted.rows() == labels.rows() && predicted.cols() == labels.cols());

    double loss = 0.0;
    int numSamples = predicted.rows();

    // Calcul de la perte de MAE
    for (int i = 0; i < numSamples; ++i) {
        for (int j = 0; j < predicted.cols(); ++j) {
            loss += std::abs(predicted(i, j) - labels(i, j));
        }
    }

    return loss / numSamples;
  }

  inline MatrixXd mae_prime(const MatrixXd& predicted, const MatrixXd& labels) {
    // Assurez-vous que les dimensions des matrices correspondent
    ASSERT(predicted.rows() == labels.rows() && predicted.cols() == labels.cols());

    int numSamples = predicted.rows();
    MatrixXd loss_prime = MatrixXd::Zero(predicted.rows(), predicted.cols());

    // Calcul de la dérivée de la perte de MAE
    for (int i = 0; i < numSamples; ++i) {
        for (int j = 0; j < predicted.cols(); ++j) {
            loss_prime(i, j) = (predicted(i, j) > labels(i, j)) ? 1 : -1;  // <= WARNING : Il n'y a pas de dérivée en 0 !!!!
        }
    }

    return loss_prime / numSamples;
  }

  class MAE
    : public Loss
  {
    public:
      MAE()
        : Loss(mae, mae_prime)
      {};

  };

}