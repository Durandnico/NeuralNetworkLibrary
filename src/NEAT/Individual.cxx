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

using namespace NeuralNetwork::NEAT;


Individual::Individual(const int individual_id, const Genome& genome)
  : individual_id(individual_id), genome(genome), fitness(0.0)
{
}

Genome Individual::cross_over(const Individual& dominant, const Individual& recessive)
{
  /* TODO */
  const int individual_id = dominant.get_genome().get_genome_id();
  const int inputs = dominant.get_genome().get_num_inputs();
  const int outputs = dominant.get_genome().get_num_outputs();
  
  return Genome(individual_id, inputs, outputs);
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

