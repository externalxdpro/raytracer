#ifndef CAMERA_H_
#define CAMERA_H_

#include "colour.hpp"
#include "hittable.hpp"
#include "util.hpp"
#include "vec3.hpp"

#include <format>
#include <iostream>

class Camera {
  public:
    double aspectRatio     = 1.0;
    int    imgWidth        = 100;
    int    samplesPerPixel = 10;
    int    maxDepth        = 10;

    void render(const Hittable &world) {
        initialize();

        std::cout << "P3\n";
        std::cout << std::format("{} {}\n", imgWidth, imgHeight);
        std::cout << "255\n";

        for (int j = 0; j < imgHeight; j++) {
            std::clog << std::format("\rScanlines remaining: {} ",
                                     imgHeight - j)
                      << std::flush;
            for (int i = 0; i < imgWidth; i++) {
                Colour pixelColour = {0, 0, 0};
                for (int sample = 0; sample < samplesPerPixel; sample++) {
                    Ray r = getRay(i, j);
                    pixelColour += rayColour(r, maxDepth, world);
                }
                Colour scaled = pixelColour * pixelSamplesScale;
                writeColour(std::cout, scaled);
            }
        }

        std::clog << "\rDone.                 \n";
    }

  private:
    int    imgHeight;
    double pixelSamplesScale;
    Vec3   center;
    Vec3   pixel0Pos;
    Vec3   pixelDeltaU;
    Vec3   pixelDeltaV;

    void initialize() {
        imgHeight = int(imgWidth / aspectRatio);
        imgHeight = (imgHeight < 1) ? 1 : imgHeight;

        pixelSamplesScale = 1.0 / samplesPerPixel;

        center = {0, 0, 0};

        double focalLength    = 1;
        double viewportHeight = 2;
        double viewportWidth  = viewportHeight * (double)(imgWidth) / imgHeight;

        Vec3 viewportU = {viewportWidth, 0, 0};
        Vec3 viewportV = {0, -viewportHeight, 0};

        pixelDeltaU = viewportU / imgWidth;
        pixelDeltaV = viewportV / imgHeight;

        Vec3 viewportTopLeft =
            center - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
        pixel0Pos = viewportTopLeft + (pixelDeltaU + pixelDeltaV) / 2;
    }

    Ray getRay(int i, int j) const {
        Vec3 offset      = sampleSquare();
        Vec3 pixelSample = pixel0Pos + (pixelDeltaU * (i + offset.x)) +
                           (pixelDeltaV * (j + offset.y));

        Vec3 origin = center;
        Vec3 dir    = pixelSample - origin;
        return {origin, dir};
    }

    Vec3 sampleSquare() const {
        return {randDouble() - 0.5, randDouble() - 0.5, 0};
    }

    Colour rayColour(const Ray &r, int depth, const Hittable &world) const {
        if (depth <= 0) {
            return {0, 0, 0};
        }

        Hittable::HitRecord rec;
        if (world.hit(r, Interval(0.001, inf), rec)) {
            Vec3 dir = rec.normal.randOnHemisphere();
            return rayColour(Ray(rec.p, dir), depth - 1, world) * 0.5;
        }

        Vec3   unitDir = r.dir.unitVector();
        double a       = (unitDir.y + 1) / 2;
        return Colour(1, 1, 1) * (1.0 - a) + Colour(0.5, 0.7, 1.0) * a;
    }
};

#endif // CAMERA_H_
