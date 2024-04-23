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
 *  \file NeuralNetwork.hxx
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
#include "Activation.hxx"
#include "Optimizer.hxx"
#include "errors_functions.hxx"
#include <Eigen/Dense>
#include <vector>
#include <iostream>

using namespace Eigen;

namespace NeuralNetwork
{
  class NeuralNetwork
  {
    private:
      /* data */
      std::vector<Dense*> layers;
      std::function<double(const MatrixXd&, const MatrixXd&)> loss_fct = mean_squared_error;
      std::function<MatrixXd(const MatrixXd&, const MatrixXd&)> loss_prime_fct = mean_squared_error_prime;

      MatrixXd forward(const MatrixXd& inputs);
      void backward(MatrixXd& output_grad);

    public:
      NeuralNetwork(std::vector<Dense*> layers);
      ~NeuralNetwork();

      std::vector<Dense*> get_layers();
      void set_loss(std::function<double(const MatrixXd&, const MatrixXd&)> loss_fct, std::function<MatrixXd(const MatrixXd&, const MatrixXd&)> loss_prime_fct);

      double accuracy(const MatrixXd& inputs_test, const MatrixXd& targets_test);
      double recall(const MatrixXd& inputs_test, const MatrixXd& targets_test);
      double loss(const MatrixXd& inputs_test, const MatrixXd& targets_test);

      void fit(const MatrixXd& inputs_train, const MatrixXd& targets_train, const int epochs, const int batch_size);
      double validate(const MatrixXd& inputs_validate, const MatrixXd& targets_validate);
      
      MatrixXd confusion_matrix(const MatrixXd& inputs, const MatrixXd& targets);

      MatrixXd predict(const MatrixXd& inputs);
    };
}