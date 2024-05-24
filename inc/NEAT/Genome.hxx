/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   NEAT                                               :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 23/May/2024 22:07:59 by Durandnico   #+#    #+#    #+#            */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

#pragma once

/*! 
 *  \file Genome.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Thu 23 May 2024 - 22:07:59
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include <unordered_map>
#include <vector>

#include "Gene.hxx"
#include "Synapse.hxx"

namespace NeuralNetwork 
{
  namespace NEAT
  {
    class Genome
    {
      private:
        /* data */
        int genome_id;
        int num_inputs;
        int num_outputs;
        std::unordered_map<int, Gene> genes;
        std::unordered_map<int, Synapse> synapses;

        
      public:
        Genome(const int genome_id, const int num_inputs, const int num_outputs);
        Genome(const Genome& genome);
        Genome(const int genome_id, const int num_inputs, const int num_outputs, const std::vector<Gene>& genes, const std::vector<Synapse>& synapses);
        ~Genome() = default;

        /* operator */

        /* copy */
        Genome& operator=(const Genome& genome);

        /* static methods */
        static void mutate_add_synapse(Genome& genome);
        static void mutate_remove_synapse(Genome& genome);
        static void mutate_add_gene(Genome& genome);
        static void mutate_remove_gene(Genome& genome);


        /* methods */
        void add_gene(const Gene& gene);
        void add_synapse(const Synapse& synapse);

        /* getters & setters */
        int get_genome_id() const;
        void set_genome_id(const int genome_id);

        int get_num_inputs() const;
        void set_num_inputs(const int num_inputs);

        int get_num_outputs() const;
        void set_num_outputs(const int num_outputs);

        std::unordered_map<int, Gene>& get_genes();
        const std::unordered_map<int, Gene>& get_genes() const;
        void set_genes(const std::unordered_map<int, Gene>& genes);

        std::unordered_map<int, Synapse>& get_synapses();
        const std::unordered_map<int, Synapse>& get_synapses() const;
        void set_synapses(const std::unordered_map<int, Synapse>& synapses);
    };
  }
}