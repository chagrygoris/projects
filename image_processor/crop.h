#pragma once
#include "filters.h"

class Crop : public Filters {
public:
    int width;
    int height;
    void Run(Image& image) override;
};