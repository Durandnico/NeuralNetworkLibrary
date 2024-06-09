/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   NEAT                                               :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 24/May/2024 by Durandnico   	      #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

/*! 
 *  \file Individual.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Fri 24 May 2024 - 13:34:13
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Individual.hxx"
#include "Mutator.hxx"
#include "NEATconfig.hxx"

using namespace NeuralNetwork::NEAT;


Individual::Individual(const int individual_id, const Genome& genome)
  : individual_id(individual_id), genome(genome), fitness(0.0)
{
}

Individual::Individual(const Individual& individual)
  : individual_id(individual.individual_id), genome(individual.genome), 
    network(individual.network), isNetworkGenerate(individual.isNetworkGenerate),
    fitness(individual.fitness), unajusted_fitness(individual.unajusted_fitness)
{
}

/* operator overload */

// copy
Individual& Individual::operator=(const Individual& obj)
{
  individual_id = obj.individual_id;
  genome = obj.genome;
  fitness = obj.fitness;

  return *this;
}

Genome Individual::cross_over(const Individual& dominant, const Individual& recessive)
{
  Genome offspring{Mutator::get_instance()->next_genome_id(), dominant.get_genome().get_num_inputs(),
                  dominant.get_genome().get_num_outputs()};
  
  // héritage des gènes
  for (const Gene& dominant_gene : dominant.get_genome().get_genes())
  {
    const int gene_id = dominant_gene.get_innovation_id();

    // est-ce qu'une mutation remplace le gène
    if(Mutator::next_bernoulli(NeatGlobalconfig.bias_replace_rate))
    {
      offspring.add_gene({gene_id, Mutator::get_instance()->new_value()});
      continue;
    }
    
    auto recessive_gene = recessive.get_genome().find_gene_by_id(gene_id);
    Gene to_add = dominant_gene; // par défaut on prend celui de parent dominant

    // si le gène est présent chez le parent récessif
    if (recessive_gene != recessive.get_genome().get_genes().end())
      to_add = Gene::cross_over_gene(dominant_gene, *recessive_gene);
    
    //possible mutation
    if(Mutator::next_bernoulli(NeatGlobalconfig.bias_mutate_rate))
      to_add.mutateBias();

    offspring.add_gene(to_add);
  } 


  // héritage des synapses
  for(const Synapse& dominant_synapse : dominant.get_genome().get_synapses())
  {
    const linkIds_t link_id = dominant_synapse.get_linkIds();

    // est-ce qu'une mutation remplace entièrement la synapse
    if(Mutator::next_bernoulli(NeatGlobalconfig.weight_replace_rate))
    {
      offspring.add_synapse({dominant_synapse.get_innovation_id(), link_id, Mutator::get_instance()->new_value(), Mutator::next_bernoulli(0.5)});
      continue;
    }
    
    auto recessive_synapse = recessive.get_genome().find_synapse_by_id(link_id);
    Synapse to_add = dominant_synapse; // par défaut on prend celui de parent dominant

    // si la synapse est présente chez le récessif
    if (recessive_synapse != recessive.get_genome().get_synapses().end())
      to_add = Synapse::cross_over_synapse(dominant_synapse, *recessive_synapse);
  
    // possible mutation
    if(Mutator::next_bernoulli(NeatGlobalconfig.weight_mutate_rate))
      to_add.mutateWeight();

    if(Mutator::next_bernoulli(NeatGlobalconfig.enable_mutate_rate))
      to_add.set_enabled(true);

    offspring.add_synapse(to_add);
  }

  return offspring;
}



double Individual::calculateFitness()
{
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<replace

  return 0.;
}


void Individual::move()
{
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<replace
}

void Individual::update()
{
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<replace
}

void Individual::look()
{
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<replace
}

void Individual::think()
{
  double max = 0;
  int maxIndex = 0;
  //get the output of the neural network
  decision = network.activate(vision);

  const int choices = decision.size();
  for (int i = 0; i < choices; ++i) {
    if (decision[i] > max) {
      max = decision[i];
      maxIndex = i;
    }
  }
    
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<replace
}

void Individual::show()
{
  // TODO
}


















/* methodes */

Individual Individual::copy() const
{
  return Individual{*this};
}





/* getters & setters */

double Individual::get_fitness() const
{
  return fitness;
}

void Individual::set_fitness(const double fitness)
{
  this->fitness = fitness;
}

const Genome& Individual::get_genome() const
{
  return genome;
}

void Individual::set_genome(const Genome& genome)
{
  this->genome = genome;
}

const GenomeNetwork& Individual::get_network() const
{
  return network;
}

bool Individual::isDead() const
{
  return dead;
}


double Individual::getScore() const
{
  return score;
}

double Individual::getUnajustedFitness() const
{
  return unajusted_fitness;
}
