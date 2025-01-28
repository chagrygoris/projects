#pragma once
#include "Image.h"
#include <vector>
#include <string>
#include <cmath>
#include <numeric>

class Filters {
private:
    std::vector<std::string> arguments_;

public:
    virtual void Run(Image &image) {};
    virtual ~Filters() = default;
};
