#pragma once
#include <iostream>
#include <ostream>
#include <random>

#include "XoshiroCpp.h"


static auto RandRange(const int min, const int max)
{
    static XoshiroCpp::Xoshiro256Plus rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

static double RandDouble()
{
    static XoshiroCpp::Xoshiro256Plus rng(std::random_device{}());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(rng);
}

inline int RandomWeight(const std::vector<double>& weights)
{
    const double r = RandDouble();

    double sum = 0;
    for (const double weight : weights) sum += weight;
    const double threshold = r * sum;

    double partialSum = 0;
    for (int i = 0; i < weights.size(); i++)
    {
        partialSum += weights[i];
        if (partialSum >= threshold) return i;
    }
    return 0;
}