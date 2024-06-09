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
        int innovationNo = 0;

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
        int auto_add_gene();
        void add_gene(const Gene& gene);
        int auto_add_synapse(const int id_in, const int id_out, const double weight);
        void add_synapse(const Synapse& synapse);
        void mutate();
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

        int get_innovationNo() const;
        void set_innovationNo(const int);
    };
  }
}