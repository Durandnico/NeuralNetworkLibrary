/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   NEAT                                               :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 24/May/2024 20:03:33 by Durandnico   #+#    #+#    #+#            */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

#pragma once

/*! 
 *  \file Mutator.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Fri 24 May 2024 - 20:03:33
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include <random>
#include <time.h>
#include "NEATconfig.hxx"
#include "Genome.hxx"
#include "Gene.hxx"
#include "Synapse.hxx"

namespace NeuralNetwork::NEAT
{
  class Mutator
  {
    private:
      static Mutator* instance;
      
      /* data */ 
      mutationConfig_t config;
      std::random_device rd;
      std::mt19937 gen;
      
      int genome_id = 0;

      double clamp(const double value) const;
      Mutator(mutationConfig_t);
      Mutator();

    public:
      ~Mutator() = default;


      Mutator(const Mutator& obj) = delete; 
      Mutator& operator=(const Mutator& obj) = delete;
      /*  =======================  method ========================= */
      static Mutator* get_instance();
      void set_config(const mutationConfig_t& config);
      
      double new_value();
      double mutate_delta(const double value);
  
      static inline bool next_bernoulli(const double p)
      {
        double r = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        return r < p;
      }
      
      template <typename T>
      static inline T choose(const double p, const T& a, const T& b)
      {
        /* generate number between 0 and 1*/
        return Mutator::next_bernoulli(p) ? a : b;
      }

      inline int next_genome_id()
      {
        return genome_id++;
      }
  };
}