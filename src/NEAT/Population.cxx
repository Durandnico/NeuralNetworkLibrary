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
  Genome firstone{0, num_inputs, num_outputs};
  // Genome& last_brain = firstone;

  for (int i = 0; i < size; i++)
  {
    Genome brain{firstone}; // copy afin de garder la topologie 
    brain.set_genome_id(i);

    const int numMutation = i * population_mutation_ratio; 

    for (int j = 0; j < numMutation; ++j)
      brain.mutate(m_innovations);

    brain.mutateWeightAndBias();
    // last_brain = brain; 
    m_individuals.push_back(std::make_shared<Individual>(Individual{i, std::move(brain)}));
  }
} 

Population::Population(const Genome& initialBrain, size_t size)
{
  m_individuals.reserve(size);

  for (size_t i = 0; i < size; i++)
  {
    Genome brain{initialBrain}; // copy afin de garder la topologie 
    brain.set_genome_id(i);

    const int numMutation = i * population_mutation_ratio; 

    for (int j = 0; j < numMutation; ++j)
      brain.mutate(m_innovations);

    brain.mutateWeightAndBias();
    m_individuals.push_back(std::make_shared<Individual>(Individual{i, std::move(brain)}));
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
  speciate();//seperate the population into species 
  calculateFitness();//calculate the fitness of each player
  sortSpecies();//sort the species to be ranked in fitness order, best first
  
  cullSpecies();//kill off the bottom half of each species
  setBestIndividual();//save the best player of this gen
  killStaleSpecies();//remove species which haven't improved in the last 15(ish) generations
  // killBadSpecies();//kill species which are so bad that they cant reproduce <-- from code bullet template but not used yet

  std::cout << "generation: " << m_generation << ", species: " << m_species.size() << "<<<<<<<<<<<<<<<<<<<<\n";

  const double avgSum = getAvgFitnessSum();
  const size_t popSize = m_individuals.size();
  std::vector<std::shared_ptr<Individual>> childs; // la futur génération
  childs.reserve(m_individuals.size());
  size_t species_individuals_count;

  std::cout << "species:\n";
  for(const auto& s : m_species)
  {
    std::cout << "\tbest unajusted fitness : " << s.getBestFitness() << "\n";
    
    species_individuals_count = 0;
    for(const std::weak_ptr<Individual>& weak_ind : s.get_individuals())
    {
      const auto shared_ind = weak_ind.lock();
      std::cout << "\t\tplayer: " <<  species_individuals_count++ << " fitness: " <<  shared_ind->get_fitness() << " score: "  << shared_ind->getScore() << "\n";
    }
    std::cout << "\n";
    
    // on récupère l'élite de chaque espèce
    int numOfElite = 0;
    for(const auto& weak_elite : s.getElite())
    {
      childs.push_back(weak_elite.lock());
      ++numOfElite;
    }

    int NoOfChildren = std::floor(s.getAvgFitness() / avgSum * popSize) - numOfElite;//the number of children this species is allowed, note : we remove the number of elite already added
    for (int i = 0; i< NoOfChildren; i++) {//get the calculated amount of children from this species
      childs.push_back(std::make_shared<Individual>(s.reproduce()));
    }
  }

  while (childs.size() < popSize) {//if not enough babies (due to flooring the number of children to get a whole int) 
    childs.push_back(std::make_shared<Individual>(m_species.front().reproduce()));
  }

  m_individuals.clear();
  m_individuals = std::move(childs);  
  ++m_generation;
  
  for (auto shared_ind : m_individuals) {//generate networks for each of the children
    shared_ind->generateNetwork();
  } 
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

  std::remove_if(m_species.begin(), m_species.end(),
  [](const Species& s){
    return s.getStaleness() >= age_of_death_of_trisomie21;
  });
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