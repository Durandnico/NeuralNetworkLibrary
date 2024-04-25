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

  inline double huber(const MatrixXd& labels, const MatrixXd& predicted, double delta) {
    // Assurez-vous que les dimensions des matrices correspondent
    ASSERT(predicted.rows() == labels.rows() && predicted.cols() == labels.cols());

    double loss = 0.0;
    int numSamples = predicted.rows();

    // Calcul de la perte de Huber
    for (int i = 0; i < numSamples; ++i) {
        for (int j = 0; j < predicted.cols(); ++j) {
            double error = predicted(i, j) - labels(i, j);
            if (std::abs(error) <= delta) {
                loss += 0.5 * error * error;
            } else {
                loss += delta * (std::abs(error) - 0.5 * delta);
            }
        }
    }

    return loss / numSamples;
  }


  inline MatrixXd huber_prime(const MatrixXd& predicted, const MatrixXd& labels, double delta) {
    // Assurez-vous que les dimensions des matrices correspondent
    assert(predicted.rows() == labels.rows() && predicted.cols() == labels.cols());

    int numSamples = predicted.rows();
    int numDimensions = predicted.cols();

    MatrixXd gradient = MatrixXd::Zero(numSamples, numDimensions);

    // Calcul de la dérivée de la perte de Huber
    for (int i = 0; i < numSamples; ++i) {
        for (int j = 0; j < numDimensions; ++j) {
            double error = predicted(i, j) - labels(i, j);
            if (std::abs(error) <= delta) {
                gradient(i, j) = error;
            } else {
                gradient(i, j) = (error > 0 ? 1 : -1);
            }
        }
    }

    return gradient;
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

      double operator()(const MatrixXd& y_true, const MatrixXd& y_pred) override
      {
        return huber(y_true, y_pred, m_delta);
      }

      MatrixXd prime(const MatrixXd& y_true, const MatrixXd& y_pred) override
      {
        return huber_prime(y_true, y_pred, m_delta);
      }
  };

}