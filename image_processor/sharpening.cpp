#include "sharpening.h"

void Sharpening::Run(Image &image) {
    Image temp = Image(image);
    RGB pixel;
    for (int y = 0; y < image.Height(); ++y) {
        for (int x = 0; x < image.Width(); ++x) {
            pixel = static_cast<float>(5) * temp.GetRgb(x, y) - temp.GetRgb(x - 1, y) -// NOLINT
                    temp.GetRgb(x + 1, y) -                                            // NOLINT
                    temp.GetRgb(x, y - 1) - temp.GetRgb(x, y + 1);                     // NOLINT
            pixel.r_ = std::min(1.0f, std::max(0.0f, pixel.r_));
            pixel.g_ = std::min(1.0f, std::max(0.0f, pixel.g_));
            pixel.b_ = std::min(1.0f, std::max(0.0f, pixel.b_));
            image.ChangePixel(pixel, x, y);
        }
    }
}
