#include "material.hpp"
#include "vec3.hpp"

#include "camera.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

#include <memory>

int main(int argc, char *argv[]) {
    HittableList world;

    double R = std::cos(pi / 4);

    std::shared_ptr matLeft  = std::make_shared<Lambertian>(Colour(0, 0, 1));
    std::shared_ptr matRight = std::make_shared<Lambertian>(Colour(1, 0, 0));

    world.add(std::make_shared<Sphere>(Vec3(-R, 0, -1), R, matLeft));
    world.add(std::make_shared<Sphere>(Vec3(R, 0, -1), R, matRight));

    Camera cam;
    cam.aspectRatio     = 16.0 / 9.0;
    cam.imgWidth        = 400;
    cam.samplesPerPixel = 100;
    cam.maxDepth        = 50;

    cam.vfov = 90;

    cam.render(world);

    return 0;
}
