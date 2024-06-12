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

namespace NeuralNetwork::NEAT
{
  extern unsigned long int nextNodeId;
  extern unsigned long int nextInnoId;

  extern int population_size; // la taille de la population
  extern int num_generations; // le nombre de générations à exécuter

  // double mutation_rate; // la probabilité de mutation (non utilisé)
  extern double population_mutation_ratio; // c'est compliqué à expliquer, mais en gros plus c'est grand, plus il y a de mutation 
  extern double crossover_rate; // la probabilité de croisement
   
  extern double mutate_power; // la puissance de mutation

  extern double bias_mutate_rate; // la probabilité de mutation d'un biai
  extern double bias_replace_rate; // la probabilité de remplacement d'un biai

  extern double weight_mutate_rate;  // la probabilité de mutation d'un unique poid
  extern double weight_replace_rate; // la probabilité de remplacement des poids
    
  extern double node_add_rate; // la probabilité d'ajout de noeuds
  // extern double node_delete_rate; // la probabilité de suppression de noeuds (non implémenté)

  extern double conn_add_prob; // la probabilité d'ajout de connexions
  //extern double conn_delete_prob; // la probabilité de suppression de connexions (non implémenté)
  extern double enable_mutate_rate; // la probabilité d'activation d'une connexion pendant un crossover

  extern double elitism_rate; // la proportion de la population qui est conservée pour la génération suivante
  extern int elistism_min_species; // le nombre minimum d'espèces à conserver
  extern int age_of_death_of_trisomie21; // c'est le stalness en gros

  extern double survival_rate; // la proportion de la population qui survit à chaque génération
  
  extern double compatibility_threshold; // si la distance de compatibilité est inférieure à ce seuil, les génomes sont de la même espèce
  extern double excess_coefficient; // coefficient pour les gènes en excès
  extern double disjoint_coefficient; // coefficient pour les gènes disjoints
  extern double weight_coefficient; // coefficient pour les poids
  extern double compatibility_threshold_modifier; // le taux de modification du seuil de compatibilité


  typedef struct      mutationConfig_s
  {
    double init_mean = 0.0;
    double init_std_dev = 1.0;
    double min = -20.0;
    double max = 20.0;
    double mutate_power = 1.2;
  }                   mutationConfig_t;

}
