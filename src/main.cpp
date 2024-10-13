#include "colour.hpp"
#include "vec3.hpp"

#include <format>
#include <iostream>

int main(int argc, char *argv[]) {
    const int imgWidth = 256, imgHeight = 256;

    std::cout << "P3\n";
    std::cout << std::format("{} {}\n", imgWidth, imgHeight);
    std::cout << "255\n";

    for (int j = 0; j < imgHeight; j++) {
        std::clog << std::format("\rScanlines remaining: {} ", imgHeight - j)
                  << std::flush;
        for (int i = 0; i < imgWidth; i++) {
            Colour pixelColour = {(double)i / (imgWidth - 1),
                                  (double)j / (imgHeight - 1), 0};
            writeColour(std::cout, pixelColour);
        }
    }

    std::clog << "\rDone.                 \n";

    return 0;
}
