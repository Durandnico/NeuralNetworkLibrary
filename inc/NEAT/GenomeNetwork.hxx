/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   NEAT                                               :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 24/May/2024 15:39:36 by Durandnico   #+#    #+#    #+#            */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

#pragma once

/*! 
 *  \file GenomeNetwork.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Fri 24 May 2024 - 15:39:36
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Genome.hxx"

#include <vector>
#include <unordered_map>

namespace NeuralNetwork::NEAT
{

  typedef struct    NeuroneInput_s
  {
    int input_id;
    double weight;
  }                 NeuroneInput_t;

  typedef struct    Neurone_s
  {
    int id;
    double bias;
    std::vector<NeuroneInput_t> inputs;
  }                 Neurone_t;

  class GenomeNetwork
  {
    public:

      GenomeNetwork(std::vector<int> inputs_ids, std::vector<int> outputs_ids, std::vector<Neurone_t> neurones);

      ~GenomeNetwork() = default;

      std::vector<double> activate(const std::vector<double>& inputs);

      // void print() const;

      static GenomeNetwork create_from_genome(const Genome& genome);

    private:
      std::vector<int> inputs_ids;
      std::vector<int> outputs_ids;
      std::vector<Neurone_t> neurones;
  };
}