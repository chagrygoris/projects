#include "EdgeDetection.h"

void EdgeDetection::Run(Image& image) {
    RGB pixel;
    Grayscale g;
    g.Run(image);
    Image temp = Image(image);
    for (int y = 0; y < image.Height(); ++y) {
        for (int x = 0; x < image.Width(); ++x) {
            pixel = static_cast<float>(4) * temp.GetRgb(x, y) - temp.GetRgb(x - 1, y) -
                temp.GetRgb(x + 1, y) -                         // NOLINT
                temp.GetRgb(x, y - 1) - temp.GetRgb(x, y + 1);  // NOLINT
            if (pixel > threshold) {
                pixel = RGB{ 1.0f, 1.0f, 1.0f };
            } else {
                pixel = RGB{ 0.0f, 0.0f, 0.0f };
            }
            image.ChangePixel(pixel, x, y);
        }
    }
}
