#pragma once
/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   Project name                                       :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 24/February/2024 by Durandnico   	  #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

/*! 
 *  \file Relu.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Sat 24 February 2024 - 03:24:41
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Activation.hxx"

namespace NeuralNetwork
{

  inline double relu(const double x)
  {
    return std::max(0.0, x);
  }


  inline double relu_prime(const double x)
  {
    return x > 0 ? 1 : 0;
  }


  class Relu
    : public Activation
  {
    public:

      Relu()
        : Activation{relu, relu_prime}
      { 
      }

      ~Relu()
      {
      }
  };

}
