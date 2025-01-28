#include "grayscale.h"

void Grayscale::Run(Image& image) {
    for (int y = 0; y < image.Height(); ++y) {
        for (int x = 0; x < image.Width(); ++x) {
            RGB pixel = image.GetRgb(x, y);
            float value = 0.299 * pixel.r_ + 0.587 * pixel.g_ + 0.114 * pixel.b_;  // NOLINT
            value = std::min(1.0f, std::max(0.0f, pixel.r_));
            image.ChangePixel(RGB{ value, value, value }, x, y);
        }
    }
}
