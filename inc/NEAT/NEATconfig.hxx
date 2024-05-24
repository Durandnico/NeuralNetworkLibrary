/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   NEAT                                               :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 24/May/2024 12:45:01 by Durandnico   #+#    #+#    #+#            */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

#pragma once

/*! 
 *  \file NEATconfig.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Fri 24 May 2024 - 12:45:01
 *
 *  \brief 
 *
 *
 */

// typedef struct    NEATconfig_s
// {
//   int population_size;
//   int num_generations;
//   double mutation_rate;
//   double crossover_rate;
//   double elitism_rate;
//   double survival_rate;
//   double compatibility_threshold;
//   double excess_coefficient;
//   double disjoint_coefficient;
//   double weight_coefficient;
//   double compatibility_threshold_modifier;
// }                   NEATconfig_t;



namespace NeuralNetwork::NEAT
{

  typedef struct      mutationConfig_s
  {
    double init_mean = 0.0;
    double init_std_dev = 1.0;
    double min = -20.0;
    double max = 20.0;
    double mutation_rate = 0.2;
    double mutate_power = 1.2;
    double replace_rate = 0.05;
  }                   mutationConfig_t;

}
