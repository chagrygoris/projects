#pragma once
#include "filters.h"

class Grayscale : public Filters {
public:
    void Run(Image& image) override;
};