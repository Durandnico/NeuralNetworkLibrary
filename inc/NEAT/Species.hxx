/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   NEAT                                               :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 03/June/2024 00:57:53 by Durandnico #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

#pragma once

/*! 
 *  \file Speciese.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Mon 03 June 2024 - 00:57:53
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Individual.hxx"
#include "Genome.hxx"

#include <vector>
#include <memory>

namespace NeuralNetwork::NEAT
{
  class Species
  {
    private:
      /* data */
      std::vector<std::weak_ptr<Individual>> m_individuals;
      Genome representative;
      
      double m_bestFitness = 0;
      double m_averageFitness = 0;
      double m_staleness = 0;
      // int m_species_id;

      /* methods */
      size_t getExcessDisjoint(const Genome& brain1, const Genome& brain2) const;
      double getAvgWeightDiff(const Genome& brain1, const Genome& brain2) const;
      double getSumFitness() const;

    public:
      Species();
      Species(const std::shared_ptr<Individual>& firstOne);
      ~Species() = default;

      /* methods */
      bool sameSpecies(const Genome& genome) const;
      void addToSpecies(const std::shared_ptr<Individual>& individual);
      void sortSpecies();
      double setAvgFitness();
      std::shared_ptr<Individual> selectIndiv() const;
      void cull();
      void fitnessSharing();
      Individual reproduce() const;
      void reset();


      /* getters & setters */
      const Individual& getBestIndividual() const;
      const std::vector<std::weak_ptr<Individual>> getElite() const;
      double getBestFitness() const;
      double getAvgFitness() const;
      double getStaleness() const;
      // int get_species_id() const;
      const std::vector<std::weak_ptr<Individual>>& get_individuals() const;
      const Genome& get_representative() const;
  };
}