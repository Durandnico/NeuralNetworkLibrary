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
 *  \file NeuralNetwork.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Tue 27 February 2024 - 01:30:22
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "NeuralNetwork.hxx"
#include "Activation.hxx"
#include "Dense.hxx"
#include "Optimizer.hxx"
#include "global.hxx"
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;

namespace NeuralNetwork
{
  NeuralNetwork::NeuralNetwork(std::vector<Dense*> layers)
    : layers{layers}
  {
  }

  NeuralNetwork::~NeuralNetwork()
  {
    for(auto layer : layers)
    {
      delete layer;
    }
  }

  std::vector<Dense*> NeuralNetwork::get_layers()
  {
    return layers;
  }
}