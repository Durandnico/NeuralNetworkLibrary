/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   Neural Network                                     :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 27/February/2024 by Durandnico   	  #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

/*! 
 *  \file NeuralNetworkBuilder.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Tue 27 February 2024 - 00:55:50
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "NeuralNetworkBuilder.hxx"
#include "Activation.hxx"
#include "Dense.hxx"
#include "Optimizer.hxx"
#include "global.hxx"
#include "NeuralNetwork.hxx"

#include "Relu.hxx"
#include "Sigmoid.hxx"
#include "LeakyRelu.hxx"
#include "Tanh.hxx"

#include <iostream>
#include <vector>


namespace NeuralNetwork 
{
  NeuralNetworkBuilder::NeuralNetworkBuilder()
    : optimizer{0},
      has_input_layer{false},
      has_output_layer{false}
  {
  }

  NeuralNetworkBuilder::~NeuralNetworkBuilder()
  {
  }

  NeuralNetwork NeuralNetworkBuilder::build()
  {
    if(!has_output_layer)
    {
      throw std::runtime_error("No output layer");
    }

    if(!has_input_layer)
    {
      throw std::runtime_error("No input layer");
    }

    // for(size_t i = 0; i < layers_size.size(); i++)
    // {
    //   if(layers_size[i].second == nullptr)
    //   {
    //     layers_size[i].second = new Relu{};
    //   }
    // }


    std::vector<Dense*> layers;
    const size_t n_layers = layers_size.size();
    for(size_t i = 1; i < n_layers; i++)
    {
      if(i == 0)
      {
        layers.emplace_back(new Dense(
          layers_size[i-1].first,
          layers_size[i].first,
          new SGD{hyperparametre.learning_rate}
          )
        );
      }
      else
      {
        layers.emplace_back(new Dense(
          layers_size[i-1].first,
          layers_size[i].first,
          new Adam{hyperparametre.learning_rate, hyperparametre.beta1, hyperparametre.beta2, hyperparametre.epsilon}
          )
        );
      }
      if(layers_size[i].second != nullptr)
      {
        layers.emplace_back(layers_size[i].second);
      }
    }

    this->has_input_layer = false;
    this->has_output_layer = false;
    return NeuralNetwork{layers};
  }

  NeuralNetworkBuilder& NeuralNetworkBuilder::set_hyperparametre_adam(double learning_rate, double beta1, double beta2, double epsilon)
  {
    this->optimizer = 1;
    this->hyperparametre.learning_rate = learning_rate;
    this->hyperparametre.beta1 = beta1;
    this->hyperparametre.beta2 = beta2;
    this->hyperparametre.epsilon = epsilon;
    return *this;
  }

  NeuralNetworkBuilder& NeuralNetworkBuilder::set_hyperparametre_sgd(double learning_rate)
  {
    this->optimizer = 0;
    this->hyperparametre.learning_rate = learning_rate;
    return *this;
  }

  NeuralNetworkBuilder& NeuralNetworkBuilder::add_input_layer(int input_size)
  {
    if(has_input_layer)
    {
      throw std::runtime_error("Input layer already added");
    }

    has_input_layer = true;
    layers_size.push_back(std::make_pair(input_size, nullptr));
    return *this;
  }
    
  NeuralNetworkBuilder& NeuralNetworkBuilder::add_hidden_layer(int size)
  {
    if(!has_input_layer)
    {
      throw std::runtime_error("No input layer");
    }

    if(has_output_layer)
    {
      throw std::runtime_error("Output layer already added");
    }

    layers_size.push_back(std::make_pair(size, nullptr));
    return *this;
  }

  NeuralNetworkBuilder& NeuralNetworkBuilder::add_output_layer(int size)
  {
    if(!has_input_layer)
    {
      throw std::runtime_error("Cannot add output layer when no input layer added");
    }

    if(has_output_layer)
    {
      throw std::runtime_error("Output layer already added");
    }

    has_output_layer = true;
    layers_size.push_back(std::make_pair(size, nullptr));
    return *this;
  }


  NeuralNetworkBuilder& NeuralNetworkBuilder::add_relu()
  {
    if(layers_size.empty())
    {
      throw std::runtime_error("No layer to add activation function");
    }

    layers_size.back().second = new Relu{};
    return *this;
  }

  NeuralNetworkBuilder& NeuralNetworkBuilder::add_leakyRelu(const double alpha)
  {
    if(layers_size.empty())
    {
      throw std::runtime_error("No layer to add activation function");
    }

    layers_size.back().second = new LeakyRelu{alpha};
    return *this;
  }

  NeuralNetworkBuilder& NeuralNetworkBuilder::add_softmax()
  {
    if(!has_output_layer)
    {
      throw std::runtime_error("No output layer, cannot add softmax");
    }

    // layers_size.back().second = new Softmax{};
    return *this;
  }

  NeuralNetworkBuilder& NeuralNetworkBuilder::add_sigmoid()
  {
    if(layers_size.empty())
    {
      throw std::runtime_error("No layer to add activation function");
    }

    layers_size.back().second = new Sigmoid{};
    return *this;
  }

  NeuralNetworkBuilder& NeuralNetworkBuilder::add_tanh()
  {
    if(layers_size.empty())
    {
      throw std::runtime_error("No layer to add activation function");
    }

    layers_size.back().second = new Tanh{};
    return *this;
  }

// namespace NeuralNetwork
}