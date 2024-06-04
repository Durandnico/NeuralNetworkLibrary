/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   NEAT                                               :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 03/June/2024 by Durandnico   	      #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

/*! 
 *  \file Population.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Mon 03 June 2024 - 21:42:16
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Population.hxx"
#include "Individual.hxx"
#include "Species.hxx"
#include "Mutator.hxx"
#include "NEATconfig.hxx"

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

namespace NeuralNetwork::NEAT
{

Population::Population(int size, int num_inputs, int num_outputs)
{
  m_individuals.reserve(size);
  
  for (int i = 0; i < size; i++)
  {
    Genome brain{i, num_inputs, num_outputs};
    const int numMutation = i/10; 

    for (int j = 0; j < numMutation; ++j)
      brain.mutate();
  
    m_individuals.push_back(std::make_shared<Individual>(std::move(Individual{i, std::move(brain)})));;
  }
} 


void Population::updateAlive()
{
  for(auto& ind_ptr : m_individuals)
  {
    if(!ind_ptr->isDead())
    {
      ind_ptr->look(); // get inputs
      ind_ptr->think();  // get ouput
      ind_ptr->update(); // update position

      // add here to show the individual
    }
  }
}


bool Population::done() const
{
  for(auto& ind_ptr : m_individuals)
  {
    if(!ind_ptr->isDead())
      return false;
  }
  return true;
}


void Population::setBestIndividual()
{
  m_bestIndividual = *std::max_element(m_individuals.begin(), m_individuals.end(), 
    [](const std::shared_ptr<Individual>& a, const std::shared_ptr<Individual>& b) -> bool
    {
      return a->getScore() < b->getScore();
    });
}


void Population::naturalSelection()
{
  //TODO
}


void Population::speciate()
{
  for(Species s: m_species)
  {
    s.reset();
  }

  for(std::shared_ptr<Individual> ind_ptr : m_individuals)
  {
    bool speciesFound = false;
    for(Species s: m_species)
    {
      if(s.sameSpecies(ind_ptr->get_genome())) // si une espèce correspond au génome
      {
        s.addToSpecies(ind_ptr);
        speciesFound = true;
        break;
      }
    }

    if(!speciesFound) // si aucune espèce ne correspond, on crée une nouvelle espèce
    {
      m_species.emplace_back(ind_ptr);;
    } 
  }
}


void Population::calculateFitness()
{
  for(std::shared_ptr<Individual> ind_ptr : m_individuals)
  {
    ind_ptr->calculateFitness();
  }
}


void Population::sortSpecies()
{
  for(Species& s: m_species)
  {
    s.sortSpecies();
  }

  // on trie les espèces par la fitness de leurs meilleurs individu
  std::sort(m_species.begin(), m_species.end(), [](const Species& a, const Species& b) {
    return a.getBestFitness() > b.getBestFitness();
  });
}

void Population::killStaleSpecies()
{

  m_species.erase(std::remove_if(m_species.begin(), m_species.end(),
  [](const Species& s){
    return s.getStaleness() >= NeatGlobalconfig.age_of_death_of_trisomie21;
  }));
}

double Population::getAvgFitnessSum()
{
  double avgFitness = 0.;
  for(const Species& s : m_species)
  {
    avgFitness += s.getAvgFitness();
  }

  return avgFitness;
}

void Population::cullSpecies()
{
  for(Species& s: m_species)
  {
    s.cull();
    s.fitnessSharing();
    s.setAvgFitness();
  }
}


/* getters & setters */

const std::vector<std::shared_ptr<Individual>>& Population::get_pop() const
{
  return m_individuals;
}

int Population::current_gen() const
{
  return m_generation;
}

const std::vector<Species>& Population::get_species() const
{
  return m_species;
}



} // namespace NeuralNetwork::NEAT