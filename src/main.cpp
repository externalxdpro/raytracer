#include "material.hpp"
#include "vec3.hpp"

#include "camera.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

#include <memory>

int main(int argc, char *argv[]) {
    HittableList world;

    std::shared_ptr matGround =
        std::make_shared<Lambertian>(Colour(0.8, 0.8, 0));
    std::shared_ptr matCenter =
        std::make_shared<Lambertian>(Colour(0.1, 0.2, 0.5));
    std::shared_ptr matLeft   = std::make_shared<Dielectric>(1.5);
    std::shared_ptr matBubble = std::make_shared<Dielectric>(1.0 / 1.5);
    std::shared_ptr matRight =
        std::make_shared<Metal>(Colour(0.8, 0.6, 0.2), 1);

    world.add(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100, matGround));
    world.add(std::make_shared<Sphere>(Vec3(0, 0, -1.2), 0.5, matCenter));
    world.add(std::make_shared<Sphere>(Vec3(-1, 0, -1), 0.5, matLeft));
    world.add(std::make_shared<Sphere>(Vec3(-1, 0, -1), 0.4, matBubble));
    world.add(std::make_shared<Sphere>(Vec3(1, 0, -1), 0.5, matRight));

    Camera cam;
    cam.aspectRatio     = 16.0 / 9.0;
    cam.imgWidth        = 400;
    cam.samplesPerPixel = 100;
    cam.maxDepth        = 50;

    cam.vfov     = 20;
    cam.lookFrom = {-2, 2, 1};
    cam.lookAt   = {0, 0, -1};
    cam.vUp      = {0, 1, 0};

    cam.defocusAngle = 10;
    cam.focusDist    = 3.4;

    cam.render(world);

    return 0;
}
