#pragma once
#include <iostream>
#include <vector>
#include <map>
using namespace std;

// A simple struct to represent a data instance with its features and class label
struct Instance {
    vector<double> features;
    int label;
};

class BayesClassifier
{
private:
    // Map to store the mean and variance of each feature for each class
    map<int, vector<pair<double, double>>> class_feature_stats;

    // Map to store the prior probability of each class
    map<int, double> class_prior_probs;
    
public:
    // Function to train the classifier on a set of instances
    void train(vector<Instance>& instances);

    // Function to classify a new instance based on its features
    int classify(vector<double>& features);
};
