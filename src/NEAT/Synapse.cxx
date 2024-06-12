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
 *  \file Synapse.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Fri 24 May 2024 - 13:06:02
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Synapse.hxx"
#include "Mutator.hxx"
#include "Innovation.hxx"
#include <random>
#include <ostream>
#include <cassert>


using namespace NeuralNetwork::NEAT;



Synapse::Synapse(int innovation_id, linkIds_t linkIds, double weight, bool enabled)
  : innovationNo(innovation_id), linkIds(linkIds), weight(weight), enabled(enabled)
{
}

Synapse::Synapse(int innovation_id, linkIds_t linkIds)
  : innovationNo(innovation_id), linkIds(linkIds), enabled(true)
{
  /* thanks copilot for that*/
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1.0, 1.0);
  this->weight = dis(gen);
}

Synapse::Synapse(int innovation_id, int id_in, int id_out)
  : innovationNo(innovation_id), linkIds({id_in, id_out}), enabled(true)
{
  /* thanks copilot for that*/
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1.0, 1.0);
  this->weight = dis(gen);
}


Synapse::Synapse(const Synapse& synapse)
  : innovationNo(synapse.get_innovation_id()), linkIds(synapse.get_linkIds()), weight(synapse.get_weight()), enabled(synapse.get_enabled())
{
}

Synapse::Synapse(const Innovation& inn, double _weight)
  : innovationNo(inn.innovation_num1), linkIds({inn.node_in_id, inn.node_out_id}), weight(_weight), enabled(true)
{
}


/* operator */

/* copy */
Synapse& Synapse::operator=(const Synapse& synapse)
{
  innovationNo = synapse.get_innovation_id();
  linkIds = synapse.get_linkIds();
  weight = synapse.get_weight();
  enabled = synapse.get_enabled();
  return *this;
}


/* mutation */

Synapse Synapse::cross_over_synapse(const Synapse& synapse1, const Synapse& synapse2)
{
  assert(synapse1.get_innovation_id() == synapse2.get_innovation_id());
  const double new_weight = Mutator::choose(0.5, synapse1.get_weight(), synapse2.get_weight());
  const bool new_enabled = Mutator::choose(0.5, synapse1.get_enabled(), synapse2.get_enabled());

  return Synapse{synapse1.get_innovation_id(), synapse1.get_linkIds(), new_weight, new_enabled};
}

void Synapse::mutateWeight()
{
  weight = Mutator::get_instance()->mutate_delta(weight);
}




/* methods */
bool Synapse::linked_to(const int gene_id_in, const int gene_id_out) const
{
  return linkIds.id_in == gene_id_in && linkIds.id_out == gene_id_out;
}

bool Synapse::linked_to(const int gene_id) const
{
  return linkIds.id_in == gene_id || linkIds.id_out == gene_id;
}




/* getters & setters */

int Synapse::get_innovation_id() const
{
  return innovationNo;
}

void Synapse::set_innovation(const int innovation)
{
  innovationNo = innovation;
}

double Synapse::get_weight() const
{
  return weight;
}

void Synapse::set_weight(const double weight)
{
  this->weight = weight;
}

bool Synapse::get_enabled() const
{
  return enabled;
}

void Synapse::set_enabled(const bool enabled)
{
  this->enabled = enabled;
}

linkIds_t Synapse::get_linkIds() const
{
  return linkIds;
}

void Synapse::set_linkIds(const linkIds_t linkIds)
{
  this->linkIds = linkIds;
}
