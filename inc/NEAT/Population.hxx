/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   NEAT                                               :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 03/June/2024 00:36:35 by Durandnico #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

#pragma once

/*! 
 *  \file Population.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Mon 03 June 2024 - 00:36:35
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Individual.hxx"
#include "Species.hxx"

#include <vector>
#include <memory>

namespace NeuralNetwork::NEAT
{
  class Population
  {
    private:
      /* data */
      std::vector<std::shared_ptr<Individual>> m_individuals;
      std::shared_ptr<Individual> m_bestIndividual;
      std::vector<Species> m_species;
      int m_generation = 0;
      
      int m_bestScore = 0;

    public:
      Population(int size, int num_inputs, int num_outputs);
      Population(Genome& genome, int size);
      ~Population() = default;

      /* methods */
      void updateAlive();
      bool done() const;
      void setBestIndividual();
      void naturalSelection();


      /* getters & setters */
      const std::vector<std::shared_ptr<Individual>>& get_pop() const;
      int current_gen() const;
      const std::vector<Species>& get_species() const;

    private:
      void speciate();
      void calculateFitness();
      void sortSpecies();
      void killStaleSpecies();
      double getAvgFitnessSum();
      void cullSpecies();

  };
}