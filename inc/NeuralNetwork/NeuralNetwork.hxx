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

    protected:
      /* data */
      void add_layer(Dense* layer);
      void add_activation(Activation* activation);


    public:
      NeuralNetwork(std::vector<Dense*> layers);
      ~NeuralNetwork();

      std::vector<Dense*> get_layers();
    };
}