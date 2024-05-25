/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   NEAT                                               :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 24/May/2024 by Durandnico   	      #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

/*! 
 *  \file GenomeNetwork.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Fri 24 May 2024 - 16:04:11
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "GenomeNetwork.hxx"
#include <unordered_map>
#include <iostream>
#include <Sigmoid.hxx>

using namespace NeuralNetwork::NEAT;

GenomeNetwork::GenomeNetwork(std::vector<int> inputs_ids, std::vector<int> outputs_ids, std::vector<Neurone_t> neurones)
  : inputs_ids(inputs_ids), outputs_ids(outputs_ids), neurones(neurones)
{
}



std::vector<double> GenomeNetwork::activate(const std::vector<double>& inputs)
{
  assert(inputs.size() == inputs_ids.size());
  std::unordered_map<int, double> values;

  /* set the inputs */
  for (size_t i = 0; i < inputs.size(); i++)
    values[inputs_ids[i]] = inputs[i];

  /* set default output values */
  for (const auto& output_id : outputs_ids)
    values[output_id] = 0.0;

  for(const auto& neuron : neurones)
  {
    double sum = 0.0;
    for(const auto& input : neuron.inputs)
    {
      assert(values.find(input.input_id) != values.end());
      sum += input.weight * values[input.input_id];
    }

    sum += neuron.bias;
    sum = sigmoid(sum); // TODO : change this to the activation function of the gene
    values[neuron.id] = sum;
  }

  /* gather outputs value */
  std::vector<double> outputs;
  outputs.reserve(outputs_ids.size());
  for(const auto& output_id : outputs_ids)
  {
    assert(values.find(output_id) != values.end());
    outputs.emplace_back(values[output_id]);
  }

  return outputs;
}





/* static function */

static int find_neurone_layer(const int neurone_id, const std::vector<Synapse>& synapses, std::unordered_map<int,int>& layers )
{
  if (layers.find(neurone_id) != layers.end())
    return layers[neurone_id];

  int max_layer = 0;
  
  for (const auto& synapse : synapses)
  {
    const auto& link = synapse.get_linkIds();
    if (link.id_out == neurone_id)
    {
      int layer = find_neurone_layer(link.id_in, synapses, layers) + 1;
      if (layer > max_layer)
        max_layer = layer;
    }
  }
  
  layers[neurone_id] = max_layer;
  return max_layer;
}


static std::vector<std::vector<int>> feed_forward_layers(int num_inputs, int num_outputs, const std::vector<Synapse>& synapses)
{
  std::vector<std::vector<int>> layers;
  std::unordered_map<int, int> neuronesLayers;
  int nbLayers = 1;

  // create the input layer
  layers.push_back({});
  layers[0].reserve(num_inputs);
  for (int i = 0; i < num_inputs; i++)
  {
    neuronesLayers[-i - 1] = 0;
    layers[0].emplace_back(-i - 1);
  }
  
  // create the output layer
  for (int i = 0; i < num_outputs; i++)
    neuronesLayers[i] = __INT32_MAX__;


  // create the hidden layers
  for (const auto& synapse : synapses)
  {
    const auto& link = synapse.get_linkIds();

    /* if output is niether an input nor an output */
    if (link.id_out < num_outputs)
      continue;

    // find the layer of the output
    int layer = find_neurone_layer(link.id_out, synapses, neuronesLayers);
    
    // update the number of layers if a new layer is found
    nbLayers = std::max(nbLayers, layer);

    // make sure the layer exists
    while(layers.size() <= (size_t) layer)
      layers.push_back({});

    // check if the neurone is already in the layer
    const auto& opt = std::find(layers[layer].begin(), layers[layer].end(), link.id_out);
    if(opt != layers[layer].end())
      continue;

    // add the neurone to the layer
    layers[layer].emplace_back(link.id_out);
  }
  
  /* add the output layer */
  layers.push_back({});
  layers.back().reserve(num_outputs);
  for (int i = 0; i < num_outputs; i++)
    layers.back().emplace_back(i);

  return layers;  
}




GenomeNetwork GenomeNetwork::create_from_genome(const Genome& genome)
{
  std::vector<Neurone_t> neurones;
  std::vector<int> inputs_ids;
  std::vector<int> outputs_ids;
  std::vector<std::vector<int>> layers = feed_forward_layers(genome.get_num_inputs(), genome.get_num_outputs(), genome.get_synapses());

  std::cout << "\n=============\n";
  for(auto& layer : layers)
  {
    for(auto& neurone_id : layer)
    {
      std::cout << neurone_id << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "\n=============\n";


  /* creating inputs_ids */
  inputs_ids.reserve(genome.get_num_inputs());
  const int& inputs = genome.get_num_inputs();
  for (int i = 0; i < inputs; i++)
    inputs_ids.emplace_back(-i - 1);

  /* creating outputs_ids */
  outputs_ids.reserve(genome.get_num_outputs());
  const int& outputs = genome.get_num_outputs();
  for (int i = 0; i < outputs; i++)
    outputs_ids.emplace_back(i);

  /* creating neurones in correct ordre */
  for(const auto& layer : layers)
  {
    for(const auto& neurone_id : layer)
    {
      std::vector<NeuroneInput_t> neuron_inputs;

      for(auto link : genome.get_synapses())
      {
        const auto& linkIds = link.get_linkIds();
        if (linkIds.id_out == neurone_id)
        {
          neuron_inputs.emplace_back(NeuroneInput_t{linkIds.id_in, link.get_weight()});
        }
      }
      
      auto neuron_gene_opt = genome.get_genes().find(neurone_id);
      assert(neuron_gene_opt != genome.get_genes().end());
      neurones.emplace_back(Neurone_t{neurone_id, neuron_gene_opt->second.get_bias(), std::move(neuron_inputs)});
    }
  }

  return GenomeNetwork(std::move(inputs_ids), std::move(outputs_ids), std::move(neurones));
}