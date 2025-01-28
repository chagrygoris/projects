#pragma once
#include <vector>
#include "RGB.cpp"

class Image {
private:
    int x_pixels_per_m_;
    int y_pixels_per_m_;
    int width_;
    int height_;
    std::vector<std::vector<RGB>> pixels_;

public:
    unsigned char info_[40];    // NOLINT
    unsigned char header_[14];  // NOLINT
    Image();
    Image(int width, int height);

    RGB GetRgb(int x, int y) const;
    void ChangePixel(RGB rgb, int x, int y);

    int Width() const;
    int Height() const;

    void SetWidth(int value);
    void SetHeight(int value);
    int GetXPixels() const;
    int GetYPixels() const;

    friend void SaveFile(const char* path, Image& image);

    void Read(const char* path);
};
