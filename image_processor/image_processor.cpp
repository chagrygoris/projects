#include "EdgeDetection.cpp"
#include "Image.cpp"
#include "blur.cpp"
#include "crop.cpp"
#include "grayscale.cpp"
#include "negativ.cpp"
#include "open_save.cpp"
#include "sharpening.cpp"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cout << "enter at least one filter" << std::endl;
        return 0;
    }
    Image lenna;
    lenna.Read(argv[1]);// NOLINT
    std::vector<std::string> args;
    for (int i = 0; i < argc; ++i) {
        if (args[i] == "-crop") {
            Crop crop;
            crop.width = std::stoi(args[++i]);
            crop.height = std::stoi(args[++i]);
            crop.Run(lenna);
            ++i;
            continue;
        } else if (args[i] == "-sharp") {
            Sharpening sharp;
            sharp.Run(lenna);
            ++i;
            continue;
        } else if (args[i] == "-gs") {
            Grayscale gs;
            gs.Run(lenna);
            ++i;
            continue;
        } else if (args[i] == "-blur") {
            Blur blur;
            blur.sigma = std::stof(args[++i]);
            blur.Run(lenna);
            ++i;
            continue;
        } else if (args[i] == "-neg") {
            Negative negativ;
            negativ.Run(lenna);
            ++i;
            continue;
        } else if (args[i] == "-edge") {
            EdgeDetection ed;
            ed.threshold = std::stof(args[++i]);
            ed.Run(lenna);
            ++i;
            continue;
        }
        args.push_back(std::string(argv[i]));
    }
    int i = 3;// NOLINT
    while (i < args.size()) {
    }
    SaveFile(argv[2], lenna);// NOLINT
    return 0;
}
