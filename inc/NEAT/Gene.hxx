/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   NEAT                                               :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 23/May/2024 21:51:56 by Durandnico   #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

#pragma once

/*! 
 *  \file Gene.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Thu 23 May 2024 - 21:51:56
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Activation.hxx"
#include "Innovation.hxx"
#include <ostream>

namespace NeuralNetwork 
{
  namespace NEAT
  {
    class Gene
    {
      private:
        /* data */
        int innovation_id;
        double bias;
        // Activation* activation;
        // bool enabled;

      public:
        // Gene(int innovation, double bias, Activation* activation);
        Gene(int innovation, double bias);
        Gene(int innovation);
        Gene(const Gene& gene);
        Gene(const Innovation& inn);
        ~Gene() = default;


        /* operator */

        /* copy */
        Gene& operator=(const Gene& gene);

        /* std::cout */
        friend std::ostream& operator<<(std::ostream& os, const Gene& gene)
          {
            os << "Gene: " << gene.get_innovation_id() << " Bias: " << gene.get_bias();
            return os;
          }

        /* mutation */
        static Gene cross_over_gene(const Gene& gene1, const Gene& gene2); 
        void mutateBias();
        
        /* getters & setters */
        int get_innovation_id() const;
        void set_innovation(const int innovation);

        // bool get_enabled() const;
        // void set_enabled(const bool enabled);

        double get_bias() const;
        void set_bias(const double bias);

        Activation* get_activation() const;
        void set_activation(Activation* activation);

        /* TODO : write to ostream */
    };
  }
}