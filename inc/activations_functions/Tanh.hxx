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
 *  \file Tanh.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Sat 24 February 2024 - 03:16:56
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Activation.hxx"

namespace NeuralNetwork
{
  
   double tanh(const double x)
  {
    return std::tanh(x);
  }


  double tanh_prime(const double x)
  {
    return 1 - std::pow(tanh(x), 2);
  }
  
  class Tanh
    : public Activation
  {
    public:

      Tanh()
        : Activation{tanh, tanh_prime}
      { 
      }

      ~Tanh()
      {
      }
  };
}