#include "RGB.h"

RGB::RGB() : r_(0), g_(0), b_(0) {}

RGB::RGB(float r, float g, float b) : r_(r), g_(g), b_(b) {}

bool operator>(RGB lhs, float threshold) {
    if (lhs.r_ > threshold) {
        return true;
    }
    if (lhs.g_ > threshold) {
        return true;
    }
    if (lhs.b_ > threshold) {
        return true;
    }
    return false;
}


RGB& RGB::operator=(const RGB& rgb) {
    r_ = rgb.r_;
    g_ = rgb.g_;
    b_ = rgb.b_;
    return *this;
}

RGB::~RGB() {}

RGB operator+(RGB lhs, RGB rhs) {
    RGB temp;
    temp.r_ = lhs.r_ + rhs.r_;
    temp.g_ = lhs.g_ + rhs.g_;
    temp.b_ = lhs.b_ + rhs.b_;
    return temp;
}

RGB operator-(RGB lhs, RGB rhs) {
    RGB temp;
    temp.r_ = lhs.r_ - rhs.r_;
    temp.g_ = lhs.g_ - rhs.g_;
    temp.b_ = lhs.b_ - rhs.b_;
    return temp;
}

RGB operator+(float lhs, RGB rhs) {
    RGB temp;
    temp.r_ = lhs + rhs.r_;
    temp.g_ = lhs + rhs.g_;
    temp.b_ = lhs + rhs.b_;
    return temp;
}

RGB operator*(float lhs, RGB rhs) {
    RGB temp;
    temp.r_ = lhs * rhs.r_;
    temp.g_ = lhs * rhs.g_;
    temp.b_ = lhs * rhs.b_;
    return temp;
}
