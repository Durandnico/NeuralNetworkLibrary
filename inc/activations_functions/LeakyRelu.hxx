#pragma once
/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   Neural Network                                       :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 24/February/2024 by Durandnico   	  #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

/*! 
 *  \file LeakyRelu.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Sat 24 February 2024 - 03:16:03
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Activation.hxx"

namespace NeuralNetwork
{
  double leaky_relu(const double x, const double alpha)
  {
    return std::max(alpha * x, x);
  }

  double leaky_relu_prime(const double x, const double alpha)
  {
    return x > 0 ? 1 : alpha;
  }

  class LeakyRelu
    : public Activation
  {
    private:
      double alpha;

    public:

      LeakyRelu(double alpha)
        : Activation{[alpha](double x) { return leaky_relu(x, alpha); }, [alpha](double x) { return leaky_relu_prime(x, alpha); }},
          alpha{alpha}
      { 
      }

      ~LeakyRelu()
      {
      }
  };
}
