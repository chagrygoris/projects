#pragma once
#include "filters.h"

class Negative : public Filters {
public:
    void Run(Image& image) override;
};