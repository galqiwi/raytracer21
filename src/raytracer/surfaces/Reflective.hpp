//
// Created by galqiwi on 10.10.2021.
//

#ifndef RAY_TRACER_21_REFLECTIVE_HPP
#define RAY_TRACER_21_REFLECTIVE_HPP

#include "ISurface.hpp"

namespace surfaces {

template <typename CoordType>
class Reflective : public surfaces::ISurface<CoordType> {
 public:
  Reflective(Traceable<CoordType>* scene) : scene_(scene) {
  }

  Color GetColor(math3d::Ray<CoordType> ray, math3d::Vector3D<CoordType> norm,
                 math3d::Vector3D<CoordType> hit) {
    if (ray.lifetime > 2) {
      return Color::Default();
    }

    math3d::Vector3D<CoordType> reflected_direction =
        ray.direction - 2 * (ray.direction * norm) * norm;
    math3d::Ray<CoordType> reflected_ray{hit + reflected_direction * 1e-4,
                                         reflected_direction, ray.lifetime + 1};
    return scene_->Trace(reflected_ray);
  }

 private:
  Traceable<CoordType>* scene_;
};

template <typename CoordType>
ISurfacePtr<CoordType> MakeReflectiveSurface(Traceable<CoordType>* scene) {
  return std::make_shared<Reflective<CoordType>>(scene);
}

}  // namespace surfaces

#endif  // RAY_TRACER_21_REFLECTIVE_HPP
