#ifndef CAMERA_H_
#define CAMERA_H_

#include "util.hpp"

class Camera {
  public:
    double aspectRatio = 1.0;
    int    imgWidth    = 100;

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
                Vec3 pixelCenter =
                    pixel0Pos + (pixelDeltaU * i) + (pixelDeltaV * j);
                Vec3 rayDir = pixelCenter - center;
                Ray  r      = {center, rayDir};

                Colour pixelColour = rayColour(r, world);
                writeColour(std::cout, pixelColour);
            }
        }

        std::clog << "\rDone.                 \n";
    }

  private:
    int  imgHeight;
    Vec3 center;
    Vec3 pixel0Pos;
    Vec3 pixelDeltaU;
    Vec3 pixelDeltaV;

    void initialize() {
        imgHeight = int(imgWidth / aspectRatio);
        imgHeight = (imgHeight < 1) ? 1 : imgHeight;

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

    Colour rayColour(const Ray &r, const Hittable &world) const {
        Hittable::HitRecord rec;
        if (world.hit(r, Interval(0, inf), rec)) {
            return (rec.normal + Colour(1, 1, 1)) / 2;
        }

        Vec3   unitDir = r.dir.unitVector();
        double a       = (unitDir.y + 1) / 2;
        return Colour(1, 1, 1) * (1.0 - a) + Colour(0.5, 0.7, 1.0) * a;
    }
};

#endif // CAMERA_H_
