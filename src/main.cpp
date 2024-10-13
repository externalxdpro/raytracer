#include "util.hpp"

#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include <memory>

Colour rayColour(const Ray &r, const Hittable &world) {
    Hittable::HitRecord rec;
    if (world.hit(r, 0, inf, rec)) {
        return (rec.normal + Colour(1, 1, 1)) / 2;
    }

    Vec3   unitDir = r.dir.unitVector();
    double a       = (unitDir.y + 1) / 2;
    return Colour(1, 1, 1) * (1.0 - a) + Colour(0.5, 0.7, 1.0) * a;
}

int main(int argc, char *argv[]) {
    const double aspectRatio = 16.0 / 9.0;
    const int    imgWidth    = 400;

    int imgHeight = int(imgWidth / aspectRatio);
    imgHeight     = (imgHeight < 1) ? 1 : imgHeight;

    HittableList world;
    world.add(std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100));

    double focalLength    = 1;
    double viewportHeight = 2;
    double viewportWidth  = viewportHeight * (double)(imgWidth) / imgHeight;
    Vec3   camCenter      = {0, 0, 0};

    Vec3 viewportU = {viewportWidth, 0, 0};
    Vec3 viewportV = {0, -viewportHeight, 0};

    Vec3 pixelDeltaU = viewportU / imgWidth;
    Vec3 pixelDeltaV = viewportV / imgHeight;

    Vec3 viewportTopLeft =
        camCenter - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
    Vec3 pixel0Pos = viewportTopLeft + (pixelDeltaU + pixelDeltaV) / 2;

    std::cout << "P3\n";
    std::cout << std::format("{} {}\n", imgWidth, imgHeight);
    std::cout << "255\n";

    for (int j = 0; j < imgHeight; j++) {
        std::clog << std::format("\rScanlines remaining: {} ", imgHeight - j)
                  << std::flush;
        for (int i = 0; i < imgWidth; i++) {
            Vec3 pixelCenter =
                pixel0Pos + (pixelDeltaU * i) + (pixelDeltaV * j);
            Vec3 rayDir = pixelCenter - camCenter;
            Ray  r      = {camCenter, rayDir};

            Colour pixelColour = rayColour(r, world);
            writeColour(std::cout, pixelColour);
        }
    }

    std::clog << "\rDone.                 \n";

    return 0;
}
