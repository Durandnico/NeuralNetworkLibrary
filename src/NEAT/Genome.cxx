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
 *  \file Genome.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Fri 24 May 2024 - 13:08:23
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Genome.hxx"

using namespace NeuralNetwork::NEAT;

Genome::Genome(const int genome_id, const int num_inputs, const int num_outputs)
  : genome_id(genome_id), num_inputs(num_inputs), num_outputs(num_outputs)
{
  /* create all the inputs*/
  for (int i = 0; i < num_inputs; i++)
  {
    const int id = -i - 1;
    genes.emplace(id, Gene(id));
  }

  /* create all the outputs */
  for (int i = 0; i < num_outputs; i++)
  {
    const int id = i + 1;
    genes.emplace(id,Gene(id));
  }

  /* create all the synapses between inputs & outputs*/
  int id = num_outputs + 1;
  for (int i = 0; i < num_inputs; i++)
  {
    for (int j = 0; j < num_outputs; j++)
    {
      synapses.emplace(id, Synapse{id, -i - 1, j + 1});
      ++id;
      // synapses[id] = Synapse(id++, -i - 1, j + 1);
    }
  }
}

Genome::Genome(const Genome& genome)
  : genome_id(genome.get_genome_id()), num_inputs(genome.get_num_inputs()), num_outputs(genome.get_num_outputs())
{
  for(const auto& gene : genome.get_genes())
  {
    genes.emplace(gene.first, gene.second);
  }

  for(const auto& synapse : genome.get_synapses())
  {
    synapses.emplace(synapse.first, synapse.second);
    // synapses[synapse.first] = Synapse(synapse.second);
  }
}

Genome::Genome(const int genome_id, const int num_inputs, const int num_outputs, const std::vector<Gene>& genes, const std::vector<Synapse>& synapses)
  : genome_id(genome_id), num_inputs(num_inputs), num_outputs(num_outputs)
{/*
  for (const auto& gene : genes)
  {
    this->genes[gene.get_innovation_id()] = gene;
  }

  for (const auto& synapse : synapses)
  {
    this->synapses[synapse.get_innovation_id()] = synapse;
  }*/
}

/* operator */

/* copy */
Genome& Genome::operator=(const Genome& genome)
{
  genome_id = genome.get_genome_id();
  num_inputs = genome.get_num_inputs();
  num_outputs = genome.get_num_outputs();
  genes = genome.get_genes();
  synapses = genome.get_synapses();
  return *this;
}

/* static methods */

void Genome::mutate_add_synapse(Genome& genome)
{
  /* TODO */
}

void Genome::mutate_remove_synapse(Genome& genome)
{
  /* TODO */
}

void Genome::mutate_add_gene(Genome& genome)
{
  /* TODO */
}

void Genome::mutate_remove_gene(Genome& genome)
{
  /* TODO */
}

/* methods */

void Genome::add_gene(const Gene& gene)
{
  // genes[gene.get_innovation_id()] = gene;
}

void Genome::add_synapse(const Synapse& synapse)
{
  // synapses[synapse.get_innovation_id()] = synapse;
}

/* getters & setters */

int Genome::get_genome_id() const
{
  return genome_id;
}

void Genome::set_genome_id(const int genome_id)
{
  this->genome_id = genome_id;
}

int Genome::get_num_inputs() const
{
  return num_inputs;
}

void Genome::set_num_inputs(const int num_inputs)
{
  this->num_inputs = num_inputs;
}

int Genome::get_num_outputs() const
{
  return num_outputs;
}

void Genome::set_num_outputs(const int num_outputs)
{
  this->num_outputs = num_outputs;
}

std::unordered_map<int, Gene>& Genome::get_genes()
{
  return genes;
}

const std::unordered_map<int, Gene>& Genome::get_genes() const
{
  return genes;
}

void Genome::set_genes(const std::unordered_map<int, Gene>& genes)
{
  this->genes = genes;
}

std::unordered_map<int, Synapse>& Genome::get_synapses()
{
  return synapses;
}

const std::unordered_map<int, Synapse>& Genome::get_synapses() const
{
  return synapses;
}

void Genome::set_synapses(const std::unordered_map<int, Synapse>& synapses)
{
  this->synapses = synapses;
}

// End of NeuralNetwork/NEAT/Genome.cxx

        