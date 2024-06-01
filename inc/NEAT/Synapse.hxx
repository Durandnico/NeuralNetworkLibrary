/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   NEAT                                               :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 23/May/2024 19:28:03 by Durandnico   #+#    #+#    #+#            */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

#pragma once

/*! 
 *  \file Synapse.hxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Thu 23 May 2024 - 19:28:03
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include <ostream>

namespace NeuralNetwork 
{
  namespace NEAT
  {
    typedef struct  linkIds_s
    {
      int id_in;
      int id_out;

      inline bool operator==(const linkIds_s& linkIds) const
      {
        return (id_in == linkIds.id_in && id_out == linkIds.id_out);
      }

    }               linkIds_t;
    
    class Synapse
    {
      private:
        /* data */
        int innovationNo;
        linkIds_t linkIds;
        double weight;
        bool enabled;

      public:
        Synapse(int innovationNo, linkIds_t linkIds, double weight, bool enabled);
        Synapse(int innovationNo, linkIds_t linkIds);
        Synapse(int innovationNo, int id_in, int id_out);
        Synapse(const Synapse& synapse);
        ~Synapse() = default;

        /*  =======================  operator ========================= */

        /* copy */
        Synapse& operator=(const Synapse& synapse);


        /* std::cout */
        friend std::ostream& operator<<(std::ostream& os, const Synapse& synapse)
        {
          os << "Synapse: " << synapse.get_innovation_id() << "(" << synapse.get_linkIds().id_in << " -> " << synapse.get_linkIds().id_out << ") | weight: " << synapse.get_weight() << " | enabled: " << synapse.get_enabled();
          return os;
        }

        /* ======================== static methods =================== */

        static Synapse cross_over_synapse(const Synapse& synapse1, const Synapse& synapse2);
        void mutateWeight();

        /* methods */
        bool linked_to(const int gene_id) const;
        bool linked_to(const int gene_id_in, const int gene_id_out) const;

        /* getters & setters */
        int get_innovation_id() const;
        void set_innovation(const int innovation);

        double get_weight() const;
        void set_weight(const double weight);

        bool get_enabled() const;
        void set_enabled(const bool enabled);

        linkIds_t get_linkIds() const;
        void set_linkIds(const linkIds_t linkIds);  
    };
  }
}
