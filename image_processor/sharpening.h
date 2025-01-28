#pragma once
#include "filters.h"

class Sharpening : public Filters {
public:
    void Run(Image &image) override;
};