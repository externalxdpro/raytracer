#include "material.hpp"
#include "vec3.hpp"

#include "camera.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

#include <memory>

int main(int argc, char *argv[]) {
    HittableList world;

    std::shared_ptr matGround =
        std::make_shared<Lambertian>(Colour(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Vec3(0, -1000, 0), 1000, matGround));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double matType = randDouble();
            Vec3 center = {a + 0.9 * randDouble(), 0.2, b + 0.9 * randDouble()};

            if ((center - Vec3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> material;
                if (matType < 0.8) {
                    Colour albedo = Colour::rand() * Colour::rand();
                    material      = std::make_shared<Lambertian>(albedo);
                } else if (matType < 0.95) {
                    Colour albedo = Colour::rand(0.5, 1);
                    double fuzz   = randDouble(0, 0.5);
                    material      = std::make_shared<Metal>(albedo, fuzz);
                } else {
                    material = std::make_shared<Dielectric>(1.5);
                }
                world.add(std::make_shared<Sphere>(center, 0.2, material));
            }
        }
    }

    std::shared_ptr mat1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Vec3(0, 1, 0), 1.0, mat1));

    std::shared_ptr mat2 = std::make_shared<Lambertian>(Colour(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Vec3(-4, 1, 0), 1.0, mat2));

    std::shared_ptr mat3 = std::make_shared<Metal>(Colour(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Vec3(4, 1, 0), 1.0, mat3));

    Camera cam;
    cam.aspectRatio     = 16.0 / 9.0;
    cam.imgWidth        = 1200;
    cam.samplesPerPixel = 100;
    cam.maxDepth        = 50;

    cam.vfov     = 20;
    cam.lookFrom = {13, 2, 3};
    cam.lookAt   = {0, 0, 0};
    cam.vUp      = {0, 1, 0};

    cam.defocusAngle = 0.6;
    cam.focusDist    = 10.0;

    cam.render(world);

    return 0;
}
