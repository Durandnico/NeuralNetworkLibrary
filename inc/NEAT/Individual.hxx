/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   NEAT                                               :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 23/May/2024 22:18:29 by Durandnico   #+#    #+#    #+#            */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

#pragma once

/*! 
 *  \file Individual.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Thu 23 May 2024 - 22:18:29
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies

#include "Genome.hxx"
#include "GenomeNetwork.hxx"

namespace NeuralNetwork 
{
  namespace NEAT
  {
    class Individual
    {
      private:
        /* data */
        int individual_id;
        Genome genome;
        GenomeNetwork network;
        double fitness;
        double unajusted_fitness;

        std::vector<double> vision; // input
        std::vector<double> decision; // output

        bool dead = false;
        double score = 0.;

      public:
        Individual(const int individual_id, const Genome& genome);
        Individual(const Individual& individual);
        ~Individual() = default;

        /* operator overload */

        // copy
        Individual& operator=(const Individual& obj);

        /* static methods */
        static Genome cross_over(const Individual& dominant, const Individual& recessive);

        /* methodes */
        Individual copy() const;
        inline void generateNetwork()
        {
          network = GenomeNetwork::create_from_genome(genome);
        }
        
        inline double calculateFitness();
        inline void show() = delete;
        inline void move();
        inline void update();
        inline void look();
        inline void think();



        /* getters & setters */
        double get_fitness() const;
        void set_fitness(const double fitness);

        const Genome& get_genome() const;
        void set_genome(const Genome& genome);

        const GenomeNetwork& get_network() const;
        bool isDead() const;
        double getScore() const;
        double getUnajustedFitness() const;
    };
  }
}
