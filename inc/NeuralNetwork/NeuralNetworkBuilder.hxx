#pragma once
/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   Neural Network                                     :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 27/February/2024 by Durandnico   	  #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

/*! 
 *  \file NeuralNetworkBuilder.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Tue 27 February 2024 - 00:44:40
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "NeuralNetwork.hxx"
#include "Dense.hxx"
#include "Activation.hxx"
#include "Optimizer.hxx"
#include "global.hxx"

#include <Eigen/Dense>
#include <iostream>
#include <vector>

using namespace Eigen;

namespace NeuralNetwork
{
  class NeuralNetworkBuilder
  {
    private:
      /* struct */
      typedef struct    HyperparametreAdam_s
      {
        /* data */
        double learning_rate = DEFAULT_LEARNING_RATE;
        double beta1 = DEFAULT_BETA1;
        double beta2 = DEFAULT_BETA2;
        double epsilon = DEFAULT_EPSILON;
      }                 HyperparametreAdam_t;
      
      /* data */
      std::vector<std::pair<int, Activation*>> layers_size; // size of the layers and the activation function (if any)
      uint8_t optimizer = 0; // 0 for sgd, 1 for adam
      HyperparametreAdam_t hyperparametre; // use to store all the hyperparametre for any optimizer
      bool has_input_layer = false;
      bool has_output_layer = false;

    public:
      NeuralNetworkBuilder();
      ~NeuralNetworkBuilder();

      NeuralNetwork build();

      NeuralNetworkBuilder& set_hyperparametre_adam(double learning_rate = DEFAULT_LEARNING_RATE, double beta1 = DEFAULT_BETA1, double beta2 = DEFAULT_BETA2, double epsilon = DEFAULT_EPSILON);
      NeuralNetworkBuilder& set_hyperparametre_sgd(double learning_rate = DEFAULT_LEARNING_RATE);

      NeuralNetworkBuilder& add_input_layer(int input_size);
      NeuralNetworkBuilder& add_hidden_layer(int size);
      NeuralNetworkBuilder& add_output_layer(int size);

      NeuralNetworkBuilder& add_relu();
      NeuralNetworkBuilder& add_leakyRelu(const double alpha = 0.01);
      NeuralNetworkBuilder& add_softmax();
      NeuralNetworkBuilder& add_sigmoid();
      NeuralNetworkBuilder& add_tanh();
  };
}
