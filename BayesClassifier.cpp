#include "BayesClassifier.h"

void BayesClassifier::train(vector<Instance>& instances)
{
    int num_instances = instances.size();
    int num_features = instances[0].features.size();

    // Compute the mean and variance of each feature for each class
    for (int i = 0; i < num_instances; i++) {
        int label = instances[i].label;
        if (class_feature_stats.find(label) == class_feature_stats.end()) {
            class_feature_stats[label].resize(num_features);
        }

        for (int j = 0; j < num_features; j++) {
            double feature = instances[i].features[j];
            if (i == 0) {
                class_feature_stats[label][j].first = feature;
                class_feature_stats[label][j].second = 0;
            } else {
                double old_mean = class_feature_stats[label][j].first;
                double old_var = class_feature_stats[label][j].second;
                double new_mean = old_mean + (feature - old_mean) / (i + 1);
                double new_var = old_var + (feature - old_mean) * (feature - new_mean);
                class_feature_stats[label][j].first = new_mean;
                class_feature_stats[label][j].second = new_var;
            }
        }
    }

    // Compute the prior probability of each class
    for (int i = 0; i < num_instances; i++) {
        int label = instances[i].label;
        class_prior_probs[label]++;
    }
    for (auto& pair : class_prior_probs) {
        pair.second /= num_instances;
    }
}

int BayesClassifier::classify(vector<double>& features)
{
    int best_label = -1;
    double best_log_prob = -INFINITY;

    // Compute the log probability of the instance belonging to each class
    for (auto& currentPair : class_feature_stats) {
        int label = currentPair.first;
        vector<pair<double, double>>& feature_stats = currentPair.second;

        double log_prob = log(class_prior_probs[label]);
        for (int i = 0; i < features.size(); i++) {
            double feature = features[i];
            double mean = feature_stats[i].first;
            double var = feature_stats[i].second / (feature_stats[i].second + 1);
            log_prob += log(1 / sqrt(2 * 3.14 * var)) - pow(feature - mean, 2) / (2 * var);
        }

        if (log_prob > best_log_prob) {
            best_label = label;
            best_log_prob = log_prob;
        }
    }

    return best_label;
}
