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
#include "Innovation.hxx"
#include <iostream>
#include <cassert>


/* static local function */

static std::vector<NeuralNetwork::NEAT::Gene>::iterator choose_random_hidden(NeuralNetwork::NEAT::Genome& genome)
{
  return genome.get_genes().begin() + genome.get_num_inputs() + genome.get_num_outputs() + (((double) rand() / RAND_MAX) * (genome.get_num_hidden_genes() - 1));
}

static std::vector<NeuralNetwork::NEAT::Gene>::iterator choose_random_input(NeuralNetwork::NEAT::Genome& genome)
{
  return genome.get_genes().begin() + (((double) rand() / RAND_MAX) * (genome.get_num_inputs() - 1));
}

static std::vector<NeuralNetwork::NEAT::Gene>::iterator choose_random_ouput(NeuralNetwork::NEAT::Genome& genome)
{
  return genome.get_genes().begin() + genome.get_num_inputs() + (((double) rand() / RAND_MAX) *  (genome.get_num_outputs() - 1));
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

  // if it's the firs
  if(!nextInnoId)
  {
    nextInnoId = id;
    nextNodeId = num_outputs;
  } 
  
}

Genome::Genome(const Genome& genome)
  : genome_id(genome.get_genome_id()), num_inputs(genome.get_num_inputs()), num_outputs(genome.get_num_outputs()), genes(genome.get_genes()), synapses(genome.get_synapses())
{
}

Genome::Genome(const int genome_id, const int num_inputs, const int num_outputs, const std::vector<Gene>& genes, const std::vector<Synapse>& synapses)
  : genome_id(genome_id), num_inputs(num_inputs), num_outputs(num_outputs), genes(genes), synapses(synapses)
{
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
void Genome::mutate_add_synapse(std::vector<Innovation>& innovations, Genome& genome)
{
  const auto& gene_in = choose_random_input_or_hidden(genome);
  const auto& gene_out = choose_random_hidden_or_output(genome);

  if(gene_in == gene_out)
    return mutate_add_synapse(innovations, genome);

  const int& id_in = gene_in->get_innovation_id();
  const int& id_out = gene_out->get_innovation_id();
  // on regarde si le lien existe deja
  const auto opt_link = std::find_if(genome.get_synapses().begin(), genome.get_synapses().end(), [&id_in, &id_out](const Synapse& synapse){return synapse.linked_to(id_in, id_out);});
  // au moins on le réacrive
  if(opt_link != genome.get_synapses().end())
    opt_link->set_enabled(true);
  
  // sinon on le crée
  else
  {
    const Innovation& innSyn = genome.getInnovationNo(innovations, id_in, id_out);
  std::cout <<  "id_in : " << id_in << " id_out : " << id_out << std::endl;
    genome.add_synapse(innSyn, Mutator::get_instance()->new_value());
  }
  
}

void Genome::mutate_remove_synapse(Genome& genome)
{
  genome.get_synapses().erase(genome.get_synapses().begin() + Mutator::get_instance()->choose_int_between(0, genome.get_synapses().size() - 1));
}

void Genome::mutate_add_gene(std::vector<Innovation>& innovations, Genome& genome)
{
  // on ajout des genes en séparant des synapeses
  // ie : pas de synapse pas d'ajout
  if(genome.get_synapses().empty())
    return;

  const int random_index = Mutator::get_instance()->choose_int_between(0, genome.get_synapses().size() - 1);
  Synapse& syn_to_split = genome.get_synapses()[random_index];
  syn_to_split.set_enabled(false);

  const Innovation& innGene = genome.getNodeId(innovations, syn_to_split);
  genome.add_gene(innGene);

  /* je ne sais pas pourquoi je dois faire ca sinon c'est explosé avec une valeur random pour idout ????*/
  const Innovation& innSynIn = genome.getInnovationNo(innovations, syn_to_split.get_linkIds().id_in, innGene.newnode_id);
  const Innovation& innSynOut = genome.getInnovationNo(innovations, innGene.newnode_id, syn_to_split.get_linkIds().id_out);


  genome.add_synapse(innSynIn, 1.0);
  genome.add_synapse(innSynOut, Mutator::get_instance()->new_value());
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
                    [&hidden_it](const Synapse& s) {
                      return s.linked_to(hidden_it->get_innovation_id());
                    }
                  ),
      links.end());
  
  // delete the hidden gene
  genome.get_genes().erase(hidden_it);
}








/* methods */

void Genome::add_gene(const Gene& gene)
{
  const auto& gene_opt = find_gene_by_id(gene.get_innovation_id());
  assert(gene_opt == genes.end());
  genes.emplace_back(gene);
}

void Genome::add_gene(const Innovation& inn)
{
  genes.emplace_back(inn);
}


void Genome::add_synapse(const Synapse& synapse)
{
  synapses.emplace_back(synapse);
}

void Genome::add_synapse(const Innovation& inn, double weight)
{
  synapses.emplace_back(Synapse(inn, weight));
}

void Genome::mutate(std::vector<Innovation>& innovations)
{
  if(Mutator::next_bernoulli(node_add_rate)) // on ajoute un gène
    mutate_add_gene(innovations, *this);

  if(Mutator::next_bernoulli(conn_add_prob)) // on ajoute une synapse
    mutate_add_synapse(innovations, *this);
}

void Genome::mutateWeightAndBias()
{
  auto* mut = Mutator::get_instance();
  for (Synapse& synapse : synapses)
  {
    synapse.set_weight(mut->new_value());
  }

  for (Gene& gene : genes)
  {
    // gene.set_bias(mut->new_value());
  }
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
  return std::find_if(genes.begin(), genes.end(), [&innovation_id](const Gene& gene){return gene.get_innovation_id() == innovation_id;});
}

std::vector<Gene>::const_iterator Genome::find_gene_by_id(const int innovation_id) const
{
  return std::find_if(genes.begin(), genes.end(), [&innovation_id](const Gene& gene){return gene.get_innovation_id() == innovation_id;});
}

std::vector<Synapse>::iterator Genome::find_synapse_by_id(linkIds_t link_id)
{
  return std::find_if(synapses.begin(), synapses.end(), [&link_id](const Synapse& synapse){return synapse.get_linkIds() == link_id;});
}

std::vector<Synapse>::const_iterator Genome::find_synapse_by_id(const linkIds_t link_id) const
{
  return std::find_if(synapses.begin(), synapses.end(), [&link_id](const Synapse& synapse){return synapse.get_linkIds() == link_id;});
}




/* local static method */
#include "Innovation.hxx"
const Innovation& Genome::getNodeId(std::vector<Innovation>& innovations, Synapse& synToSplit)
{
  // on cherche parmis les innovations pour voir si elle existe déja
  std::vector<Innovation>::iterator inn_it;
  bool found;

  inn_it = innovations.begin();
  do
  {
    // on cherche la 1ère innovation qui correspond au critère
    inn_it = std::find_if(inn_it, innovations.end(), [&synToSplit](const Innovation& inn){
      return inn.innovation_type == innovtype::NEWNODE
              && inn.node_in_id == synToSplit.get_linkIds().id_in
              && inn.node_out_id == synToSplit.get_linkIds().id_out;
    });

    if(inn_it == innovations.end())
    {
      innovations.emplace_back(Innovation(synToSplit.get_linkIds().id_in, synToSplit.get_linkIds().id_out, nextInnoId, nextInnoId + 1, nextNodeId++));
      return innovations.back(); //retourne nouveau id pour le gène
    }

    found = true;
    for(const Gene& gene : this->genes)
    {
      if(gene.get_innovation_id() == inn_it->newnode_id)
      {
        found = false;
        inn_it++;
        break;
      }
    }


  } while (!found);

  // on a trouvé une correspondance

  return *inn_it;
}

const Innovation& Genome::getInnovationNo(std::vector<Innovation>& innovations, int nodeIn, int nodeOut)
{
  // on cherche parmis les innovations pour voir si elle existe déja
  std::vector<Innovation>::iterator inn_it;
  bool found;

  inn_it = innovations.begin();
  do
  {
    // on cherche la 1ère innovation qui correspond au critère
    inn_it = std::find_if(inn_it, innovations.end(), [&nodeIn, &nodeOut](const Innovation& inn){
      return inn.innovation_type == innovtype::NEWLINK
              && inn.node_in_id == nodeIn
              && inn.node_out_id == nodeOut;
    });

    if(inn_it == innovations.end())
    {
      innovations.emplace_back(Innovation(nodeIn, nodeOut, nextInnoId++));
      return innovations.back(); //retourne nouveau id pour le gène
    }

    found = true;
    for(const Synapse& syn : this->synapses)
    {
      if(syn.get_innovation_id() == inn_it->innovation_num1)
      {
        found = false;
        inn_it++;
        break;
      }
    }

  } while (!found);

  // on a trouvé une correspondance

  return *inn_it;
}
// End of NeuralNetwork/NEAT/Genome.cxx

        