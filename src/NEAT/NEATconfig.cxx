/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   NEAT                                               :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 11/June/2024 by Durandnico   	  #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

/*! 
 *  \file NEATconfig.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Tue 11 June 2024 - 20:21:23
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "NEATconfig.hxx"


unsigned long int NeuralNetwork::NEAT::nextNodeId = 0;
unsigned long int NeuralNetwork::NEAT::nextInnoId = 0;

int NeuralNetwork::NEAT::population_size = 150; // la taille de la population
int NeuralNetwork::NEAT::num_generations = 100; // le nombre de générations à exécuter

// double NeuralNetwork::NEAT::mutation_rate = 0.2; // la probabilité de mutation (non utilisé)
double NeuralNetwork::NEAT::population_mutation_ratio = 0.2; // c'est compliqué à expliquer, mais en gros plus c'est grand, plus il y a de mutation 
double NeuralNetwork::NEAT::crossover_rate = 0.75; // la probabilité de croisement
double NeuralNetwork::NEAT::mutate_power = 1.2; // la puissance de mutation

double NeuralNetwork::NEAT::bias_mutate_rate = 0.4; // la probabilité de mutation d'un biai
double NeuralNetwork::NEAT::bias_replace_rate = 0.1; // la probabilité de remplacement d'un biai

double NeuralNetwork::NEAT::weight_mutate_rate = 0.4;  // la probabilité de mutation d'un unique poid
double NeuralNetwork::NEAT::weight_replace_rate = 0.1; // la probabilité de remplacement des poids
    
double NeuralNetwork::NEAT::node_add_rate = 0.01; // la probabilité d'ajout de noeuds
// double NeuralNetwork::NEAT::node_delete_rate = 0.1; // la probabilité de suppression de noeuds (non implémenté)

double NeuralNetwork::NEAT::conn_add_prob = 0.05; // la probabilité d'ajout de connexions
// double NeuralNetwork::NEAT::conn_delete_prob = 0.01; // la probabilité de suppression de connexions (non implémenté)
double NeuralNetwork::NEAT::enable_mutate_rate = 0.25; // la probabilité d'activation d'une connexion pendant un crossover

double NeuralNetwork::NEAT::elitism_rate = 0.1; // la proportion de la population qui est conservée pour la génération suivante
int NeuralNetwork::NEAT::elistism_min_species = 1; // le nombre minimum d'espèces à conserver
int NeuralNetwork::NEAT::age_of_death_of_trisomie21 = 15; // c'est le stalness en gros

double NeuralNetwork::NEAT::survival_rate = 0.5; // la proportion de la population qui survit à chaque génération
  
double NeuralNetwork::NEAT::compatibility_threshold = 3.0; // si la distance de compatibilité est inférieure à ce seuil, les génomes sont de la même espèce
double NeuralNetwork::NEAT::excess_coefficient = 1.0; // coefficient pour les gènes en excès
double NeuralNetwork::NEAT::disjoint_coefficient = 1.0; // coefficient pour les gènes disjoints
double NeuralNetwork::NEAT::weight_coefficient = 0.4; // coefficient pour les poids
double NeuralNetwork::NEAT::compatibility_threshold_modifier = 0.1; // le taux de modification du seuil de compatibilité
