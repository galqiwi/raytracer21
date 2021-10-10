cmake_minimum_required(VERSION 3.20)
project(ray_tracer_21)

set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(ray_tracer_21 src/main.cpp src/raytracer/Scene.hpp src/math3d/Vector3D.hpp src/raytracer/Color.cpp src/raytracer/Color.hpp src/raytracer/objects/IObject.hpp src/raytracer/objects/Sphere.hpp src/image/IImage.hpp src/image/PPMImage.cpp src/image/PPMImage.hpp src/raytracer/Camera.hpp src/raytracer/objects/Plain.hpp src/raytracer/surfaces/ISurface.hpp src/raytracer/Traceable.hpp src/raytracer/surfaces/Phong.hpp src/threadpool/ThreadPool.cpp src/threadpool/ThreadPool.hpp src/raytracer/Camera.cpp src/raytracer/Sky.hpp)

target_link_libraries(ray_tracer_21 PRIVATE Threads::Threads)