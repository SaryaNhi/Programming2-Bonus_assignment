#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include "MatrixB.h"
#include "LinearRegression.h"
using namespace std;


const int ORIGINAL_FEATURES = 6;   // Original number of features
const int TOTAL_FEATURES = ORIGINAL_FEATURES + 1;  // Including bias term
const int NUM_SAMPLES = 209;        // Total data samples


// Fisher-Yates shuffle for dataset indices
void shuffle(int* indices, int n) {
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(indices[i], indices[j]);
    }
}


int main() {
    double features[NUM_SAMPLES][ORIGINAL_FEATURES];  // Raw input features
    double targets[NUM_SAMPLES];                      // Target values


    // Load dataset
    ifstream file("machine.data");
    if (!file) {
        cerr << "Error: Cannot open machine.data\n";
        return 1;
    }


    // Parse CSV data
    string line;
    int row = 0;
    while (getline(file, line) && row < NUM_SAMPLES) {
        stringstream ss(line);
        string token;


        // Skip vendor and model columns
        getline(ss, token, ',');
        getline(ss, token, ',');


        // Read features
        for (int i = 0; i < ORIGINAL_FEATURES; ++i) {
            getline(ss, token, ',');
            features[row][i] = stod(token);
        }


        // Read target (PRP)
        getline(ss, token, ',');
        targets[row] = stod(token);
        ++row;
    }
    file.close();


    // Create shuffled indices
    int indices[NUM_SAMPLES];
    for (int i = 0; i < NUM_SAMPLES; ++i) indices[i] = i;
    srand(0);
    shuffle(indices, NUM_SAMPLES);


    // Train-test split (80-20)
    int train_size = NUM_SAMPLES * 80 / 100;
    int test_size = NUM_SAMPLES - train_size;


    // Arrays to store mean and standard deviation for each feature
    double feature_means[ORIGINAL_FEATURES] = {0};
    double feature_stds[ORIGINAL_FEATURES] = {0};

    // Step 1: Compute mean and standard deviation for each feature (using training set only)
   
    // Calculate means
    for (int j = 0; j < ORIGINAL_FEATURES; ++j) {
        double sum = 0.0;
        for (int i = 0; i < train_size; ++i) {
            int idx = indices[i];
            sum += features[idx][j];
        }
        feature_means[j] = sum / train_size;
    }
   
    // Calculate standard deviations
    for (int j = 0; j < ORIGINAL_FEATURES; ++j) {
        double sum_sq = 0.0;
        for (int i = 0; i < train_size; ++i) {
            int idx = indices[i];
            double diff = features[idx][j] - feature_means[j];
            sum_sq += diff * diff;
        }
        feature_stds[j] = sqrt(sum_sq / train_size);
       
        // Handle constant features (avoid division by zero)
        if (feature_stds[j] < 1e-7) {
            feature_stds[j] = 1.0;
        }
    }


    // Initialize matrices with bias term
    Matrix X_train(train_size, TOTAL_FEATURES);
    Matrix y_train(train_size, 1);
    Matrix X_test(test_size, TOTAL_FEATURES);
    Matrix y_test(test_size, 1);

    // Step 2: Prepare training data with feature scaling and bias term
   
    for (int i = 0; i < train_size; ++i) {
        int idx = indices[i];
       
        // Add bias term (constant 1 in first column)
        X_train.set(i, 0, 1.0);
       
        // Add scaled features
        for (int j = 0; j < ORIGINAL_FEATURES; ++j) {
            // Standardize feature: (value - mean) / std_dev
            double scaled_value = (features[idx][j] - feature_means[j]) / feature_stds[j];
            X_train.set(i, j + 1, scaled_value);  // j+1 to account for bias column
        }
       
        // Set target value
        y_train.set(i, 0, targets[idx]);
    }

    // Step 3: Prepare test data using same scaling parameters as training set
   
    for (int i = 0; i < test_size; ++i) {
        int idx = indices[train_size + i];
       
        // Add bias term (constant 1 in first column)
        X_test.set(i, 0, 1.0);
       
        // Add scaled features using training set's mean and std
        for (int j = 0; j < ORIGINAL_FEATURES; ++j) {
            double scaled_value = (features[idx][j] - feature_means[j]) / feature_stds[j];
            X_test.set(i, j + 1, scaled_value);  // j+1 to account for bias column
        }
       
        // Set target value
        y_test.set(i, 0, targets[idx]);
    }


    // Train and evaluate model
    LinearRegression model;
    model.train(X_train, y_train);


    Matrix predictions = model.predict(X_test);
    double error = model.rmse(predictions, y_test);


    cout << "Root Mean Squared Error (RMSE): " << error << "\n\n";
    model.printWeights();


    return 0;
}
