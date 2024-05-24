/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   NEAT                                               :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 23/May/2024 22:18:29 by Durandnico   #+#    #+#    #+#            */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

#pragma once

/*! 
 *  \file Individual.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Thu 23 May 2024 - 22:18:29
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies

#include "Genome.hxx"

namespace NeuralNetwork 
{
  namespace NEAT
  {
    class Individual
    {
      private:
        /* data */
        int individual_id;
        Genome genome;
        double fitness;

      public:
        Individual(const int individual_id, const Genome& genome);
        Individual(const Individual& individual) = default;
        ~Individual() = default;

        /* static methods */
        static Genome cross_over(const Individual& dominant, const Individual& recessive);

        /* getters & setters */
        double get_fitness() const;
        void set_fitness(const double fitness);

        const Genome& get_genome() const;
        void set_genome(const Genome& genome);
    };
  }
}
