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
 *  \file Gene.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Fri 24 May 2024 - 13:02:05
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Gene.hxx"
#include "Mutator.hxx"
#include <ostream>
#include <random>


using namespace NeuralNetwork::NEAT;
/*
Gene::Gene(int innovation, double bias, Activation* activation)
  : innovation_id(innovation), bias(bias), activation(activation)
{
}
*/

Gene::Gene(int innovation, double bias)
  : innovation_id(innovation), bias(bias)
{
}

Gene::Gene(int innovation)
  : innovation_id(innovation), bias(0.0)
{
}

Gene::Gene(const Gene& gene)
  : innovation_id(gene.get_innovation_id()), bias(gene.get_bias())
{
}


/* operator */

/* copy */
Gene& Gene::operator=(const Gene& gene)
{
  innovation_id = gene.get_innovation_id();
  bias = gene.get_bias();
  return *this;
}




/* mutation */
Gene Gene::cross_over_gene(const Gene& gene1, const Gene& gene2)
{
  assert(gene1.get_innovation_id() == gene2.get_innovation_id());

  double bias = Mutator::choose(0.5, gene1.get_bias(), gene2.get_bias());
  return Gene{gene1.get_innovation_id(), bias};
}

void Gene::mutateBias()
{
  bias = Mutator::get_instance()->mutate_delta(bias);
}




/* getters & setters */
int Gene::get_innovation_id() const
{
  return innovation_id;
}

void Gene::set_innovation(const int innovation)
{
  innovation_id = innovation;
}

double Gene::get_bias() const
{
  return bias;
}

void Gene::set_bias(const double bias)
{
  this->bias = bias;
}

/*
NeuralNetwork::Activation* Gene::get_activation() const
{
  return activation;
}

void Gene::set_activation(Activation* activation)
{
  this->activation = activation;
}*/

// End of NeuralNetwork/NEAT/Gene.cxx