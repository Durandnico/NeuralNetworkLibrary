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
#include <random>
#include <ostream>


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


Synapse Synapse::cross_over_synapse(const Synapse& synapse1, const Synapse& synapse2)
{
  /* TODO*/
  return Synapse{synapse1.get_innovation_id(), synapse1.get_linkIds(), synapse1.get_weight(), synapse1.get_enabled()};
}

void Synapse::mutateWeight()
{
  /* TODO */
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
