#include "crop.h"

void Crop::Run(Image& image) {
    image.SetHeight(std::min(image.Height(), height));
    image.SetWidth(std::min(image.Width(), width));
}
