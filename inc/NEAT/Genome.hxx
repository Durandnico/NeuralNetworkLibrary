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
#include <vector>

#include "Gene.hxx"
#include "Synapse.hxx"
#include "Innovation.hxx"

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
        std::vector<Gene> genes;
        std::vector<Synapse> synapses;

        // pour trouver l
        const Innovation& getNodeId(std::vector<Innovation>& innovations, Synapse& synToSplit);
        const Innovation& getInnovationNo(std::vector<Innovation>& innovations, int nodeIn, int nodeOut);
      
      public:
        Genome(const int genome_id, const int num_inputs, const int num_outputs);
        Genome(const Genome& genome);
        Genome(const int genome_id, const int num_inputs, const int num_outputs, const std::vector<Gene>& genes, const std::vector<Synapse>& synapses);
        ~Genome() = default;

        /* operator */

        /* copy */
        Genome& operator=(const Genome& genome);

        /* static methods */
        static void mutate_add_synapse(std::vector<Innovation>& innovations, Genome& genome);
        static void mutate_remove_synapse(Genome& genome);
        static void mutate_add_gene(std::vector<Innovation>& innovations, Genome& genome);
        static void mutate_remove_gene(Genome& genome);

        /* methods */
        void add_gene(const Gene& gene);
        void add_gene(const Innovation& inn);
        void add_synapse(const Synapse& synapse);
        void add_synapse(const Innovation& inn, double _weight);
        void mutate(std::vector<Innovation>& innovations);
        void mutateWeightAndBias();

        /* getters & setters */
        int get_genome_id() const;
        void set_genome_id(const int genome_id);

        int get_num_inputs() const;
        void set_num_inputs(const int num_inputs);

        int get_num_outputs() const;
        void set_num_outputs(const int num_outputs);

        std::vector<Gene>& get_genes();
        const std::vector<Gene>& get_genes() const;
        void set_genes(const std::vector<Gene>& genes);

        std::vector<Synapse>& get_synapses();
        const std::vector<Synapse>& get_synapses() const;
        void set_synapses(const std::vector<Synapse>& synapses);

        size_t get_num_hidden_genes() const;
        std::vector<Gene>::iterator find_gene_by_id(int id);
        std::vector<Gene>::const_iterator find_gene_by_id(const int innovation_id) const;
        std::vector<Synapse>::iterator find_synapse_by_id(linkIds_t link_id);
        std::vector<Synapse>::const_iterator find_synapse_by_id(const linkIds_t link_id) const;
    };
  }
}