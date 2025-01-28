#pragma once
#include "filters.h"
#include "grayscale.cpp"

class EdgeDetection : public Filters {
public:
    float threshold;
    void Run(Image& image) override;
};