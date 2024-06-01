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
#include "Mutator.hxx"
#include "NEATconfig.hxx"
#include <cassert>


/* static local function */

static std::vector<NeuralNetwork::NEAT::Gene>::iterator choose_random_hidden(NeuralNetwork::NEAT::Genome& genome)
{
  std::uniform_int_distribution<int> dist(genome.get_num_outputs(), genome.get_genes().size());
  std::default_random_engine rng;

  return genome.get_genes().begin() + dist(rng);
}

static std::vector<NeuralNetwork::NEAT::Gene>::iterator choose_random_input(NeuralNetwork::NEAT::Genome& genome)
{
  std::uniform_int_distribution<int> dist(0, genome.get_num_inputs());
  std::default_random_engine rng;

  return genome.get_genes().begin() + dist(rng);
}

static std::vector<NeuralNetwork::NEAT::Gene>::iterator choose_random_ouput(NeuralNetwork::NEAT::Genome& genome)
{
  std::uniform_int_distribution<int> dist(0, genome.get_num_outputs());
  std::default_random_engine rng;

  return genome.get_genes().begin() + dist(rng) + genome.get_num_inputs();
}


static std::vector<NeuralNetwork::NEAT::Gene>::iterator choose_random_input_or_hidden(NeuralNetwork::NEAT::Genome& genome)
{
  const double ratio_hidden = (double) genome.get_num_hidden_genes() / (genome.get_num_inputs() + genome.get_num_hidden_genes());
  if(NeuralNetwork::NEAT::Mutator::next_bernoulli(ratio_hidden))
    return choose_random_hidden(genome);

  return choose_random_input(genome);
}

static std::vector<NeuralNetwork::NEAT::Gene>::iterator choose_random_hidden_or_output(NeuralNetwork::NEAT::Genome& genome)
{
  const double ratio_hidden = (double) genome.get_num_hidden_genes() / (genome.get_num_outputs() + genome.get_num_hidden_genes());
  if(NeuralNetwork::NEAT::Mutator::next_bernoulli(ratio_hidden))
    return choose_random_hidden(genome);

  return choose_random_ouput(genome);
}












/* class methods */
using namespace NeuralNetwork::NEAT;

Genome::Genome(const int genome_id, const int num_inputs, const int num_outputs)
  : genome_id(genome_id), num_inputs(num_inputs), num_outputs(num_outputs)
{
  /* create all the inputs*/
  for (int i = 0; i < num_inputs; i++)
  {
    const int id = -i - 1;
    genes.emplace_back(id);
  }

  /* create all the outputs */
  for (int i = 0; i < num_outputs; i++)
  {
    genes.emplace_back(i);
  }

  /* create all the synapses between inputs & outputs*/
  int id = num_outputs;
  for (int i = 0; i < num_inputs; i++)
  {
    for (int j = 0; j < num_outputs; j++)
    {
      synapses.emplace_back(id++, -i - 1, j);
    }
  }

  innovationNo = id;
}

Genome::Genome(const Genome& genome)
  : genome_id(genome.get_genome_id()), num_inputs(genome.get_num_inputs()), num_outputs(genome.get_num_outputs()), genes(genome.get_genes()), synapses(genome.get_synapses()), innovationNo(genome.get_innovationNo())
{
}

Genome::Genome(const int genome_id, const int num_inputs, const int num_outputs, const std::vector<Gene>& genes, const std::vector<Synapse>& synapses)
  : genome_id(genome_id), num_inputs(num_inputs), num_outputs(num_outputs), genes(genes), synapses(synapses)
{
  innovationNo = genes.size() + synapses.size();
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
  innovationNo = genome.get_innovationNo();
  return *this;
}









/* static methods */

void Genome::mutate_add_synapse(Genome& genome)
{
  const auto& gene_in = choose_random_input_or_hidden(genome);
  const auto& gene_out = choose_random_hidden_or_output(genome);

  const int& id_in = gene_in->get_innovation_id();
  const int& id_out = gene_out->get_innovation_id();
  // on regarde si le lien existe deja
  const auto opt_link = std::find_if(genome.get_synapses().begin(), genome.get_synapses().end(), [id_in, id_out](const Synapse& synapse){return synapse.linked_to(id_in, id_out);});
  // au moins on le réacrive
  if(opt_link != genome.get_synapses().end())
    opt_link->set_enabled(true);
  
  // sinon on le crée
  else
    genome.auto_add_synapse(id_in, id_out, Mutator::get_instance()->new_value());
}

void Genome::mutate_remove_synapse(Genome& genome)
{
  std::uniform_int_distribution<int> dist(0, genome.get_synapses().size() - 1);
  std::default_random_engine rng;

  genome.get_synapses().erase(genome.get_synapses().begin() + dist(rng));
}

void Genome::mutate_add_gene(Genome& genome)
{
  // on ajout des genes en séparant des synapeses
  // ie : pas de synapse pas d'ajout
  if(genome.get_synapses().empty())
    return;


  std::uniform_int_distribution<int> dist(0, genome.get_synapses().size() - 1);
  std::default_random_engine rng;

  Synapse& syn_to_split = genome.get_synapses()[dist(rng)];
  syn_to_split.set_enabled(false);

  int inno_id = genome.auto_add_gene();

  genome.auto_add_synapse(syn_to_split.get_linkIds().id_in, inno_id, 1);
  genome.auto_add_synapse(inno_id, syn_to_split.get_linkIds().id_out, syn_to_split.get_weight());
}

void Genome::mutate_remove_gene(Genome& genome)
{
  
  if(genome.get_num_hidden_genes() == 0)
    return;

  const auto& hidden_it = choose_random_hidden(genome);

  //delete all the associated synapses
  auto& links = genome.get_synapses();
  links.erase(
    std::remove_if(links.begin(), links.end(),
                    [hidden_it](const Synapse& s) {
                      return s.linked_to(hidden_it->get_innovation_id());
                    }
                  ),
      links.end());
  
  // delete the hidden gene
  genome.get_genes().erase(hidden_it);
}








/* methods */

int Genome::auto_add_gene()
{
  genes.emplace_back(innovationNo++);
  return innovationNo - 1;
}

void Genome::add_gene(const Gene& gene)
{
  const auto& gene_opt = find_gene_by_id(gene.get_innovation_id());
  assert(gene_opt == genes.end());
  genes.emplace_back(gene);
}

int Genome::auto_add_synapse(const int id_in, const int id_out, const double weight)
{
  synapses.emplace_back(innovationNo++, linkIds_t{id_in, id_out}, weight, true);
  return innovationNo - 1;
}

void Genome::add_synapse(const Synapse& synapse)
{
  synapses.emplace_back(synapse);
}

void Genome::mutate()
{
  if(Mutator::next_bernoulli(NeatGlobalconfig.node_add_rate)) // on ajoute un gène
    mutate_add_gene(*this);

  if(Mutator::next_bernoulli(NeatGlobalconfig.conn_add_prob)) // on ajoute une synapse
    mutate_add_synapse(*this);
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

std::vector<Gene>& Genome::get_genes()
{
  return genes;
}

const std::vector<Gene>& Genome::get_genes() const
{
  return genes;
}

void Genome::set_genes(const std::vector<Gene>& genes)
{
  this->genes = genes;
}

std::vector<Synapse>& Genome::get_synapses()
{
  return synapses;
}

const std::vector<Synapse>& Genome::get_synapses() const
{
  return synapses;
}

void Genome::set_synapses(const std::vector<Synapse>& synapses)
{
  this->synapses = synapses;
}

size_t Genome::get_num_hidden_genes() const
{
  return genes.size() - num_inputs - num_outputs;
}

std::vector<Gene>::iterator Genome::find_gene_by_id(const int innovation_id)
{
  return std::find_if(genes.begin(), genes.end(), [innovation_id](const Gene& gene){return gene.get_innovation_id() == innovation_id;});
}

std::vector<Gene>::const_iterator Genome::find_gene_by_id(const int innovation_id) const
{
  return std::find_if(genes.begin(), genes.end(), [innovation_id](const Gene& gene){return gene.get_innovation_id() == innovation_id;});
}

std::vector<Synapse>::iterator Genome::find_synapse_by_id(linkIds_t link_id)
{
  return std::find_if(synapses.begin(), synapses.end(), [link_id](const Synapse& synapse){return synapse.get_linkIds() == link_id;});
}

std::vector<Synapse>::const_iterator Genome::find_synapse_by_id(const linkIds_t link_id) const
{
  return std::find_if(synapses.begin(), synapses.end(), [link_id](const Synapse& synapse){return synapse.get_linkIds() == link_id;});
}


int Genome::get_innovationNo() const
{
  return innovationNo;
}

void Genome::set_innovationNo(const int innNo)
{
  innovationNo = innNo;
}
// End of NeuralNetwork/NEAT/Genome.cxx

        