#include "negativ.h"

void Negative::Run(Image& image) {
    for (int y = 0; y < image.Height(); ++y) {
        for (int x = 0; x < image.Width(); ++x) {
            image.ChangePixel(1.0f + (-1.0f) * image.GetRgb(x, y), x, y);
        }
    }
}
