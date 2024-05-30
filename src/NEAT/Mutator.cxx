/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   NEAT                                               :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 25/May/2024 by Durandnico   	      #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

/*! 
 *  \file Mutator.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Sat 25 May 2024 - 16:58:34
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Mutator.hxx"
#include <random>
#include <time.h>

using namespace NeuralNetwork::NEAT;


Mutator::Mutator(mutationConfig_t config)
  : config(config), rd(), gen(rd())
{
  gen.seed(time(NULL));
}
      
Mutator::Mutator()
  : Mutator(mutationConfig_t{})
{
}

double Mutator::clamp(const double value) const
{
  return std::max(config.min, std::min(config.max, value));
}


Mutator* Mutator::get_instance()
{
  return instance;
}

void Mutator::set_config(const mutationConfig_t& config)
{
  this->config = config;
}

bool Mutator::mutation_occurs() const
{
  return this->next_bernoulli(config.mutation_rate);
}

bool Mutator::mutation_topology_occurs() const
{
  return this->next_bernoulli(config.replace_rate);
}

double Mutator::new_value()
{
  std::normal_distribution<double> new_value_generator{config.init_mean, config.init_std_dev};
  // return 0;
  return clamp(new_value_generator(gen));
}

double Mutator::mutate_delta(const double value)
{
  std::normal_distribution<double> mutate_delta_generator{0.0, config.mutate_power};
  // return 0;
  return clamp(value + mutate_delta_generator(gen));
}

