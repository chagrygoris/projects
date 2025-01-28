#pragma once
#include "filters.h"

std::vector<float> CalculateCoefficient(float sigma);

class Blur : public Filters {
public:
    float sigma;
    void Run(Image& image) override;
};
