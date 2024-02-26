#pragma once
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
 *  \file Optimizer.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Mon 26 February 2024 - 16:59:57
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include <Eigen/Dense>
#include "global.hxx"

using namespace Eigen;

namespace NeuralNetwork
{
  class Dense;

  class Optimizer
  {
    public:
    virtual void update(NeuralNetwork::Dense* layer, const MatrixXd& output_grad) = 0;
  };

  class SGD : public Optimizer
  {
    private:
    double learning_rate;

    public:
    SGD(double _learning_rate = DEFAULT_LEARNIN_RATE);
    ~SGD();
     
    void update(NeuralNetwork::Dense* layer, const MatrixXd& output_grad ) override;    
  };

  class Adam : public Optimizer
  {
    private:
    double learning_rate;
    double beta1;
    double beta2;
    double epsilon;
    MatrixXd m_weight;
    MatrixXd v_weight;
    MatrixXd m_bias;
    MatrixXd v_bias;
    MatrixXd epsilon_bias;
    MatrixXd epsilon_weight;
    uint64_t t;

    public:
    Adam(double _learning_rate = DEFAULT_LEARNIN_RATE, double _beta1 = DEFAULT_BETA1, double _beta2 = DEFAULT_BETA2, double _epsilon = DEFAULT_EPSILON);
    ~Adam();
     
    void update(NeuralNetwork::Dense* layer, const MatrixXd& output_grad ) override;    
  };
}