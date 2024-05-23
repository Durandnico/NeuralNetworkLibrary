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
 *  \file Net.cxx
 *  \author DURAND Nicolas Erich Pierre <durandnico@cy-tech.fr>
 *  \version 0.1
 *  \date Tue 27 February 2024 - 01:30:22
 *
 *  \brief 
 *
 *
 */

// Inclusion des entetes de librairies
#include "Net.hxx"
#include "Loss.hxx"

#include <Eigen/Dense>
#include <iostream>
#include <memory>

using namespace Eigen;

namespace NeuralNetwork
{
  Net::Net(std::vector<NeuralNetwork::Dense*> layers)
    : layers{layers}
  {
  }

  Net::~Net()
  {
    for(auto layer : layers)
    {
      delete layer;
    }
  }



  /* ======================================================================== */
  /* Private function */
  /* ======================================================================== */

  MatrixXd Net::forward(const MatrixXd& inputs)
  {
    MatrixXd output = inputs;
    for( Dense* layer : this->layers)
      output = layer->forward(output);

    return output;
  }

  VectorXd Net::forward(const VectorXd& inputs)
  {
    VectorXd output = inputs;
    for( Dense* layer : this->layers)
      output = layer->forward(output);

    return output;
  }

  
  void Net::backward(MatrixXd& output_grad)
  {    
    const int n_layers = layers.size();
   
    for(int i = n_layers - 1; i >= 0; --i)
      output_grad = layers[i]->backward(output_grad);

    return;
  }

  void Net::backward(VectorXd& output_grad)
  {    
    const int n_layers = layers.size();
   
    for(int i = n_layers - 1; i >= 0; --i)
      output_grad = layers[i]->backward(output_grad);

    return;
  }



  /* ======================================================================== */
  /* Public function */
  /* ======================================================================== */


  double Net::loss(const MatrixXd& inputs, const MatrixXd& targets)
  {
    return loss_fct->operator()(inputs, targets);
  }

  MatrixXd Net::predict(const MatrixXd& inputs)
  {
    ASSERT(inputs.cols() == layers[0]->get_n_inputs());
    return forward(inputs);
  }

  VectorXd Net::predict(const VectorXd& inputs)
  {
    ASSERT(inputs.rows() == layers[0]->get_n_inputs());
    return forward(inputs);
  }


  double Net::validate(const MatrixXd& inputs, const MatrixXd& targets)
  {
    const MatrixXd outputs = forward(inputs);
    return loss(outputs, targets);
  }

  void Net::fit(const MatrixXd& inputs_train, const MatrixXd& targets_train, const int epochs, const int batch_size)
  {
    ASSERT(inputs_train.cols() == this->layers.front()->get_inputs().rows()) // 
    const int data_size = inputs_train.rows();
    int data_id;
    double loss;

    this->loss_history.clear();
    this->loss_history.reserve(epochs);

    for(int epoch = 0; epoch < epochs; ++epoch)
    {
      data_id = loss = 0; // on commence sur la 1ère variable de test

      while (data_id < data_size)
      {
        const int local_batch_size = std::min(batch_size, data_size - data_id);

        // Extract batch
        MatrixXd inputs_batch = inputs_train.block(data_id, 0, local_batch_size, inputs_train.cols());
        MatrixXd targets_batch = targets_train.block(data_id, 0, local_batch_size, targets_train.cols());
        std::cout << inputs_batch << "\n";
        std::cout << targets_batch << "\n" ;

        // Forward pass
        MatrixXd outputs = forward(inputs_batch);

        // Compute loss
        loss += loss_fct->operator()(targets_batch, outputs);

        // Backward pass
        MatrixXd output_grad = loss_fct->prime(targets_batch, outputs);
        backward(output_grad);

        // increment data_id
        data_id += local_batch_size;
      }    
      loss_history.emplace_back(loss);
      std::cout << "\n\n";
    }
  }


  double Net::accuracy(const MatrixXd& inputs, const MatrixXd& targets)
  {
    const MatrixXd outputs = this->predict(inputs);
    
    MatrixXd predictions(outputs.rows(), outputs.cols());
    for (int i = 0; i < outputs.rows(); ++i)
      for (int j = 0; j < outputs.cols(); ++j)
        predictions(i, j) = outputs(i, j) > 0.5 ? 1 : 0;

    const MatrixXd true_positives = (predictions.array() == 1 && targets.array() == 1).cast<double>();
    const MatrixXd false_negatives = (predictions.array() == 0 && targets.array() == 1).cast<double>();
    return true_positives.sum() / (true_positives.sum() + false_negatives.sum());

    return 0.;
  }

  double Net::recall(const MatrixXd& inputs, const MatrixXd& targets)
  {
    const MatrixXd outputs = this->predict(inputs);
    
    MatrixXd predictions(outputs.rows(), outputs.cols());
    for (int i = 0; i < outputs.rows(); ++i)
      for (int j = 0; j < outputs.cols(); ++j)
        predictions(i, j) = outputs(i, j) > 0.5 ? 1 : 0;

    const MatrixXd true_positives = (predictions.array() == 1 && targets.array() == 1).cast<double>();
    const MatrixXd false_positives = (predictions.array() == 1 && targets.array() == 0).cast<double>();
    return true_positives.sum() / (true_positives.sum() + false_positives.sum());

    return 0.;
  }


  MatrixXd Net::confusion_matrix(const MatrixXd& inputs, const MatrixXd& targets)
  {
    const MatrixXd outputs = this->predict(inputs);
    
    MatrixXd predictions(outputs.rows(), outputs.cols());
    for (int i = 0; i < outputs.rows(); ++i)
      for (int j = 0; j < outputs.cols(); ++j)
        predictions(i, j) = outputs(i, j) > 0.5 ? 1 : 0;

    const MatrixXd true_positives = (predictions.array() == 1 && targets.array() == 1).cast<double>();
    const MatrixXd false_positives = (predictions.array() == 1 && targets.array() == 0).cast<double>();
    const MatrixXd true_negatives = (predictions.array() == 0 && targets.array() == 0).cast<double>();
    const MatrixXd false_negatives = (predictions.array() == 0 && targets.array() == 1).cast<double>();

    MatrixXd confusion_matrix(2, 2);
    confusion_matrix(0, 0) = true_positives.sum();
    confusion_matrix(0, 1) = false_positives.sum();
    confusion_matrix(1, 0) = false_negatives.sum();
    confusion_matrix(1, 1) = true_negatives.sum();

    return confusion_matrix;
  }

  /* ======================================================================== */
  /* getters */
  /* ======================================================================== */

  std::vector<Dense*> Net::get_layers()
  {
    return layers;
  }


  void Net::plot_loss(void)
  {
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

    /* set label on y axe */
    fprintf(gnuplotPipe, "set ylabel 'loss'\n");

    fprintf(gnuplotPipe, "set xlabel 'epochs'\n");

    fprintf(gnuplotPipe, "plot '-' with lines\n");

    const int loss_size = this->loss_history.size();
    for (int i = 0; i < loss_size; ++i) {
      fprintf(gnuplotPipe, "%d %f\n", i, this->loss_history[i]);
    }
   
    fprintf(gnuplotPipe, "e\n");
  }

  
} // namespace NeuralNetwork