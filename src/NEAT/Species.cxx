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
 *  \file Species.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Mon 03 June 2024 - 13:05:45
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Species.hxx"
#include "NEATconfig.hxx"
#include "Mutator.hxx"

#include <algorithm>
#include <iostream>

namespace NeuralNetwork::NEAT
{


  Species::Species()
    : representative(-1,0,0), m_bestFitness(0)
  {
    std::cerr << "Species::Species() - Species created without representative !" << std::endl;
  }

  Species::Species(const std::shared_ptr<Individual>& firstOne)
    : representative(firstOne->get_genome()), m_bestFitness(firstOne->get_fitness())
  {
    m_individuals.push_back(firstOne);
  }

  bool Species::sameSpecies(const Genome& genome) const
  { 
    const size_t excess_disjoint = getExcessDisjoint(representative, genome);
    const double avg_weight_diff = getAvgWeightDiff(representative, genome);

    const double largeGenomeNormalizer = std::max((int) genome.get_genes().size() - 20 , 1);
    
    
    const double compatibility = (NeatGlobalconfig.excess_coefficient * excess_disjoint / largeGenomeNormalizer) + (NeatGlobalconfig.weight_coefficient * avg_weight_diff);

    return compatibility < NeatGlobalconfig.compatibility_threshold;
  }

  void Species::addToSpecies(const std::shared_ptr<Individual>& individual)
  {
    m_individuals.push_back(individual);
  }


  size_t Species::getExcessDisjoint(const Genome& brain1, const Genome& brain2) const
  {
    size_t matching = 0;
    const size_t brain1Size = brain1.get_genes().size();
    const size_t brain2Size = brain2.get_genes().size();

    const auto& genes1 = brain1.get_genes();
    const auto& genes2 = brain2.get_genes();

    for (size_t i = 0; i < brain1Size; i++) {
      for (size_t j = 0; j < brain2Size; j++) {

        if (genes1[i].get_innovation_id() == genes2[j].get_innovation_id()) {
          ++ matching;
          break;
        }
      }
    }
    return (brain1Size + brain2Size - 2*(matching));//return no of excess and disjoint genes
  }

  double Species::getAvgWeightDiff(const Genome& brain1, const Genome& brain2) const
  {
    size_t matching = 0;
    double total_diff = 0;
    const size_t brain1Size = brain1.get_synapses().size();
    const size_t brain2Size = brain2.get_synapses().size();
    
    if(brain1Size == 0 || brain2Size == 0) 
      return 0;

    const auto& genes1 = brain1.get_synapses();
    const auto& genes2 = brain2.get_synapses();

    for (size_t i = 0; i < brain1Size; i++) {
      for (size_t j = 0; j < brain2Size; j++) {

        if (genes1[i].get_innovation_id() == genes2[j].get_innovation_id()) {
          ++ matching;
          total_diff += std::abs(genes1[i].get_weight() - genes2[j].get_weight());
          break;
        }
      }
    }
    return total_diff / matching;
  }

  double Species::getSumFitness() const
  {
    double fitnessSum = 0;
    std::for_each(m_individuals.begin(), m_individuals.end(), [&fitnessSum](const std::weak_ptr<Individual>& ind)
      {
        if(const auto ind_share = ind.lock())
          fitnessSum += ind_share->get_fitness(); 
      });
    return fitnessSum;
  }

  void Species::sortSpecies()
  {
    // on enlève les individus morts
    m_individuals.erase(std::remove_if(m_individuals.begin(), m_individuals.end(), [](const std::weak_ptr<Individual>& i) { return i.expired(); }), m_individuals.end());

    // on trie les individus par fitness
    std::sort(m_individuals.begin(), m_individuals.end(), [](const std::weak_ptr<Individual>& a, const std::weak_ptr<Individual>& b) {
      return a.lock()->get_fitness() > b.lock()->get_fitness();
    });

    // si aucun individu de l'espèce n'est en vie c'est le bordel
    if (m_individuals.empty()) {
      std::cerr << "Species::sortSpecies() - No individual in the species -> FUCK" << std::endl;
      m_bestFitness = INT32_MAX;
    } 

    // update du nouveau meilleur
    if(m_individuals.front().lock()->get_fitness() > m_bestFitness)
    {
      m_staleness = 0;
      m_bestFitness = m_individuals.front().lock()->get_fitness();
    }
    else // si aucune amélioration, on increment le counteur de nulité
    {
      ++m_staleness;
    }
  }


  double Species::setAvgFitness()
  {
    const double sum = getSumFitness(); 
    
    m_averageFitness = sum / m_individuals.size();
    return m_averageFitness;
  }


  std::shared_ptr<Individual> Species::selectIndiv() const
  {
    const double fitnessSum = getSumFitness();    

    // génère un fitness entre 0 et fitnessSum
    const double randFitness = ((double) rand() / RAND_MAX) * fitnessSum;

    // on parcours les individus en sommant leur fitness jusqu'à atteindre randFitness
    double runningSum = 0;
    for (const auto& ind : m_individuals) {
      runningSum += ind.lock()->get_fitness();
      if (runningSum > randFitness) {
        return ind.lock();
      }
    } 

    // si on arrive ici c'est que c'est la merde
    std::cerr << "Species::selectIndiv() - Reach out of fitness sum " << std::endl;
    return m_individuals.front().lock();
  }

  Individual Species::reproduce() const
  {
    // on a une chance d'avoir un individu identique
    if(!Mutator::get_instance()->next_bernoulli(NeatGlobalconfig.crossover_rate))
    {
      return selectIndiv()->copy();
    }


    // on sélectionne deux individus
    const std::shared_ptr<Individual> parent1 = selectIndiv();
    const std::shared_ptr<Individual> parent2 = selectIndiv();

    // pour choisir le parent dominant
    if(parent1->get_fitness() > parent2->get_fitness())
      return {0, Individual::cross_over(*parent1, *parent2)};


    return {0, Individual::cross_over(*parent2, *parent1)};
  }


  void Species::cull()
  {
    // on supprime les individus les moins performants en fonction du taux de survie
    const size_t numToSurvive =  std::ceil(m_individuals.size() * NeatGlobalconfig.survival_rate); // nombre d'individus à conserver
    m_individuals.erase(m_individuals.begin() + numToSurvive, m_individuals.end()); // on supprime les autres
  }

  void Species::fitnessSharing()
  {
    const size_t speciesSize = m_individuals.size();
    // on partage la fitness de chaque individu en fonction du nombre d'individus dans l'espèce
    std::for_each(m_individuals.begin(), m_individuals.end(), [&speciesSize](const std::weak_ptr<Individual>& ind) {
      std::shared_ptr<Individual> ind_shared = ind.lock();
      ind_shared->set_fitness(ind_shared->get_fitness() / speciesSize);
    });
  }

  void Species::reset()
  {
    m_individuals.clear();
  }


  /* getters & setters */
  const Individual& Species::getBestIndividual() const
  {
    return *(m_individuals.front().lock());
  }

  const std::vector<std::weak_ptr<Individual>> Species::getElite() const
  {
    const size_t numberOfElite = std::max(NeatGlobalconfig.elistism_min_species, (int) std::floor(NeatGlobalconfig.elitism_rate * m_individuals.size()));
    const auto lastElit = m_individuals.begin() + numberOfElite;
    
    return std::vector<std::weak_ptr<Individual>>{m_individuals.begin(), lastElit};
  }

  double Species::getBestFitness() const
  {
    return m_bestFitness;
  }

  double Species::getAvgFitness() const
  {
    return m_averageFitness;
  }

  double Species::getStaleness() const
  {
    return m_staleness;
  }

  const std::vector<std::weak_ptr<Individual>>& Species::get_individuals() const 
  {
    return m_individuals;
  }  

} // namespace NeuralNetwork::NEAT