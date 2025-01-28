#include "blur.h"

std::vector<float> CalculateCoefficient(float sigma) {
    std::vector<float> res;
    int radius = std::ceil(4 * sigma);// NOLINT
    float value = 0;
    for (int i = -radius; i <= radius; ++i) {
        value = exp(-powf(i, 2.0f) / (2 * powf(sigma, 2.0f))) / sqrt(2 * atan(1) * 4 * powf(sigma, 2.0f));// NOLINT
        res.push_back(value);
    }
    return res;
}

void Blur::Run(Image &image) {
    int radius = std::ceil(4 * sigma);// NOLINT
    std::vector<float> weights = CalculateCoefficient(sigma);
    RGB pixel;
    Image current = image;
    for (int y = 0; y < image.Height(); ++y) {
        for (int x = 0; x < image.Width(); ++x) {
            pixel = RGB{0.0f, 0.0f, 0.0f};
            for (int i = 0; i < 2 * radius + 1; ++i) {
                pixel = pixel + weights[i] * current.GetRgb(x + i - radius, y);
            }
            image.ChangePixel(pixel, x, y);
        }
    }
    current = image;
    for (int y = 0; y < image.Height(); ++y) {
        for (int x = 0; x < image.Width(); ++x) {
            pixel = RGB{0.0f, 0.0f, 0.0f};
            for (int i = 0; i < 2 * radius + 1; ++i) {
                pixel = pixel + weights[i] * current.GetRgb(x, y + i - radius);
            }
            image.ChangePixel(pixel, x, y);
        }
    }
}
