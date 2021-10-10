#include <memory>
#include <mutex>
#include <deque>

#include "raytracer/Scene.hpp"
#include "raytracer/objects/Sphere.hpp"
#include "raytracer/Camera.hpp"

#include "image/PPMImage.hpp"
#include "raytracer/objects/Plain.hpp"
#include "raytracer/surfaces/Phong.hpp"
#include "threadpool/ThreadPool.hpp"
#include "raytracer/surfaces/Reflective.hpp"
#include "raytracer/Sky.hpp"

using Vector3Dd = math3d::Vector3D<double>;

int main() {
  Scene<double> scene(
      std::make_shared<Sky<double>>(image::MakePPMImage("../sky.ppm")));

  scene.AddObject(
      std::make_shared<objects::Sphere<double>>(Vector3Dd{0.0, 2, -10}, 1)
          ->WithSurface(surfaces::MakeReflectiveSurface<double>(&scene)));

  scene.AddObject(
      std::make_shared<objects::Sphere<double>>(Vector3Dd{1.5, 0, -10}, 1)
          ->WithSurface(
              surfaces::MakeGlowingSurface<double>(Color{10, 10, 6}, &scene)));

  scene.AddObject(
      std::make_shared<objects::Sphere<double>>(Vector3Dd{0, -2, -10}, 1)
          ->WithSurface(
              surfaces::MakeGlowingSurface<double>(Color{10, 6, 10}, &scene)));

  scene.AddObject(
      std::make_shared<objects::Sphere<double>>(Vector3Dd{-1.5, 0, -10}, 1)
          ->WithSurface(
              surfaces::MakeOpaqueSurface<double>(1, 1, &scene, 400)));

  scene.AddObject(
      std::make_shared<objects::Sphere<double>>(Vector3Dd{-3, -2, -10}, 1)
          ->WithSurface(surfaces::MakeReflectiveSurface<double>(&scene)));

  scene.AddObject(
      std::make_shared<objects::Sphere<double>>(Vector3Dd{3, -2, -10}, 1)
          ->WithSurface(surfaces::MakeReflectiveSurface<double>(&scene)));

  //  scene.AddObject(std::make_shared<objects::Plain<double>>(
  //      Vector3Dd{0, 1, 0}, Vector3Dd{0, -1.5, 0},
  //      surfaces::MakeGlowingSurface<double>(0.05, &scene),
  //      surfaces::MakeGlowingSurface<double>(0.6, &scene))
  //  );

  auto camera =
      camera::Camera(camera::CameraParameters<double>{{0, 0, 0},
                                                      {0, 1, 0},
                                                      {0, 0, -1},
                                                      M_PI / 3 * 1920 / 1080,
                                                      M_PI / 3,
                                                      &scene});

  camera.TakePhoto(image::MakePPMImage(1920, 1000), 20, 20, 16)
      ->Save("test.ppm");
}
