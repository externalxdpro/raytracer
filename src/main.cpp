#include "colour.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#include <format>
#include <iostream>

double hitSphere(const Vec3 &center, double radius, const Ray &r) {
    Vec3 oc = center - r.origin;

    // Do quadratic formula to calculate t in
    // t^2(dir . dir) - 2t(dir) . oc + (oc . oc - radius^2)
    // to check if ray hit sphere
    double a            = r.dir.length_squared();
    double h            = r.dir.dot(oc);
    double c            = oc.length_squared() - radius * radius;
    auto   discriminant = h * h - a * c;

    if (discriminant < 0) {
        return -1;
    } else {
        return (h - std::sqrt(discriminant)) / a;
    }

    return (discriminant >= 0);
}

Colour rayColour(const Ray &r) {
    double t = hitSphere(Vec3(0, 0, -1), 0.5, r);
    if (t > 0) {
        const Vec3 n = (r.at(t) - Vec3(0, 0, -1)).unitVector();
        return Colour(n.x + 1, n.y + 1, n.z + 1) / 2;
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

            Colour pixelColour = rayColour(r);
            writeColour(std::cout, pixelColour);
        }
    }

    std::clog << "\rDone.                 \n";

    return 0;
}
