#include "Image.h"

Image::Image() : width_(0), height_(0) {
}

Image::Image(int width, int height) : width_(width), height_(height), pixels_(height_, std::vector<RGB>(width_)) {
}

int Image::Width() const {
    return width_;
}

int Image::Height() const {
    return height_;
}

int Image::GetXPixels() const {
    return x_pixels_per_m_;
}
int Image::GetYPixels() const {
    return y_pixels_per_m_;
}

void Image::SetHeight(int value) {
    value = std::min(height_, value);
    std::vector<std::vector<RGB>> temp = pixels_;
    for (int i = height_ - value; i < height_; ++i) {
        pixels_[i - height_ + value] = temp[i];
    }
    height_ = value;
}

void Image::SetWidth(int value) {
    width_ = value;
}

RGB Image::GetRgb(int x, int y) const {
    if (x <= -1) {
        x = 0;
    } else if (x >= width_) {
        x = width_ - 1;
    }
    if (y <= -1) {
        y = 0;
    } else if (y >= height_) {
        y = height_ - 1;
    }
    return pixels_[y][x];
}

void Image::ChangePixel(RGB rgb, int x, int y) {
    pixels_[y][x] = rgb;
}
