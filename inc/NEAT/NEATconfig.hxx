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


typedef struct NEATconfig_s
{
  int population_size = 150; // la taille de la population
  int num_generations = 100; // le nombre de générations à exécuter

  // double mutation_rate = 0.2; // la probabilité de mutation (non utilisé)
  double population_mutation_ratio = 0.2; // c'est compliqué à expliquer, mais en gros plus c'est grand, plus il y a de mutation 
  double crossover_rate = 0.75; // la probabilité de croisement
  double mutate_power = 1.2; // la puissance de mutation

  double bias_mutate_rate = 0.4; // la probabilité de mutation d'un biai
  double bias_replace_rate = 0.1; // la probabilité de remplacement d'un biai

  double weight_mutate_rate = 0.4;  // la probabilité de mutation d'un unique poid
  double weight_replace_rate = 0.1; // la probabilité de remplacement des poids
    
  double node_add_rate = 0.01; // la probabilité d'ajout de noeuds
  // double node_delete_rate = 0.1; // la probabilité de suppression de noeuds (non implémenté)

  double conn_add_prob = 0.05; // la probabilité d'ajout de connexions
  // double conn_delete_prob = 0.01; // la probabilité de suppression de connexions (non implémenté)
  double enable_mutate_rate = 0.25; // la probabilité d'activation d'une connexion pendant un crossover

  double elitism_rate = 0.1; // la proportion de la population qui est conservée pour la génération suivante
  int elistism_min_species = 1; // le nombre minimum d'espèces à conserver
  int age_of_death_of_trisomie21 = 15; // c'est le stalness en gros

  double survival_rate = 0.5; // la proportion de la population qui survit à chaque génération
  
  double compatibility_threshold = 3.0; // si la distance de compatibilité est inférieure à ce seuil, les génomes sont de la même espèce
  double excess_coefficient = 1.0; // coefficient pour les gènes en excès
  double disjoint_coefficient = 1.0; // coefficient pour les gènes disjoints
  double weight_coefficient = 0.4; // coefficient pour les poids
  double compatibility_threshold_modifier = 0.1; // le taux de modification du seuil de compatibilité
}               NEATconfig_t;


namespace NeuralNetwork::NEAT
{
  extern unsigned long int nextNodeId;
  extern unsigned long int nextInnoId;

  static NEATconfig_t NeatGlobalconfig;

  typedef struct      mutationConfig_s
  {
    double init_mean = 0.0;
    double init_std_dev = 1.0;
    double min = -20.0;
    double max = 20.0;
    double mutate_power = 1.2;
  }                   mutationConfig_t;

}
