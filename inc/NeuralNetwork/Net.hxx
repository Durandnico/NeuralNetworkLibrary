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
 *  \file Net.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Mon 26 February 2024 - 23:42:14
 *
 *  \brief 
 *      builder of neural network
 *
 */

// Inclusion des entetes de librairies
#include "Dense.hxx"
#include "MSE.hxx"

#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <memory>

using namespace Eigen;

namespace NeuralNetwork
{
  
  class Net
  {
    private:
      /* data */
      std::vector<Dense*> layers;
      std::unique_ptr<Loss> loss_fct = std::make_unique<MSE>();
      std::vector<double> loss_history;

      MatrixXd forward(const MatrixXd& inputs);
      VectorXd forward(const VectorXd& inputs);
      void backward(MatrixXd& output_grad);
      void backward(VectorXd& output_grad);

    public:

      Net(std::vector<Dense*> layers);
      ~Net();

      std::vector<Dense*> get_layers();
      void set_loss(std::unique_ptr<Loss> loss_fct);

      double accuracy(const MatrixXd& inputs_test, const MatrixXd& targets_test);
      double recall(const MatrixXd& inputs_test, const MatrixXd& targets_test);
      double loss(const MatrixXd& inputs_test, const MatrixXd& targets_test);

      void fit(const MatrixXd& inputs_train, const MatrixXd& targets_train, const int epochs, const int batch_size);
      double validate(const MatrixXd& inputs_validate, const MatrixXd& targets_validate);
      
      MatrixXd confusion_matrix(const MatrixXd& inputs, const MatrixXd& targets);

      MatrixXd predict(const MatrixXd& inputs);
      VectorXd predict(const VectorXd& inputs);

      void plot_loss(void);

    };
}