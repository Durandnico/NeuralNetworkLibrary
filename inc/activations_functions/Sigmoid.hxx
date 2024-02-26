#pragma once
/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   Neural Network                                     :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 24/February/2024 by Durandnico   	  #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

/*! 
 *  \file Sigmoid.hpp
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Sat 24 February 2024 - 03:10:26
 *
 *  \brief 
 *
 *
 */
#include <math.h>
#include "Activation.hxx"

namespace NeuralNetwork
{
  double sigmoid(const double x)
  {
    return 1 / (1 + std::exp(-x));
  }


  double sigmoid_prime(const double x)
  {
    return sigmoid(x) * (1 - sigmoid(x));
  }


  class Sigmoid
    : public Activation
  {
    public:

      Sigmoid()
        : Activation{sigmoid, sigmoid_prime}
      { 
      }

      ~Sigmoid()
      {
      }
  };
}