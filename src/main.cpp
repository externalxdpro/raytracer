#include "camera.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

#include <memory>

int main(int argc, char *argv[]) {
    HittableList world;
    world.add(std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100));

    Camera cam;
    cam.aspectRatio = 16.0 / 9.0;
    cam.imgWidth    = 400;

    cam.render(world);

    return 0;
}
