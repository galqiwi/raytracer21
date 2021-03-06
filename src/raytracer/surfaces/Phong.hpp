//
// Created by galqiwi on 06.10.2021.
//

#ifndef RAY_TRACER_21_PHONG_HPP
#define RAY_TRACER_21_PHONG_HPP

#include "ISurface.hpp"

namespace surfaces {

template <typename CoordType>
class Phong : public surfaces::ISurface<CoordType> {
 public:
  Phong(Color ambient, double diffuse, double specular,
        Traceable<CoordType>* scene, size_t n_reflections)
      : ambient_(ambient),
        diffuse_(diffuse),
        specular_(specular),
        scene_(scene),
        n_reflections_(n_reflections) {
  }

  Color GetColor(math3d::Ray<CoordType> ray, math3d::Vector3D<CoordType> norm,
                 math3d::Vector3D<CoordType> hit) {
    if (ray.lifetime > 2) {
      return ambient_;
    }

    auto ey = norm;
    auto ex = math3d::NormAndRotate90(ey);
    auto ez = ex % ey;

    Color diffuse{0, 0, 0};
    Color specular{0, 0, 0};

    if (n_reflections_ == 0) {
      return ambient_;
    }

    for (size_t i = 0; i < n_reflections_; ++i) {
      auto random_unit = math3d::RandomUnitVector<CoordType>();
      random_unit.y = abs(random_unit.y);
      auto direction = ChangeBasis(random_unit, ex, ey, ez);
      Color intensity = scene_->Trace(math3d::Ray<CoordType>{
          hit + direction * 1e-4, direction, ray.lifetime + 1});

      auto specular_intensity =
          (ray.direction * (2. * (direction * norm) * norm - direction));
      if (specular_intensity < 0) {
        specular_intensity = 0;
      }
      diffuse = diffuse + intensity * abs(norm * direction);
      specular = specular + intensity * specular_intensity;
    }

    return ambient_ + diffuse * (diffuse_ / n_reflections_) +
           specular * (specular_ / n_reflections_);
  }

 private:
  Color ambient_;
  double diffuse_;
  double specular_;
  Traceable<CoordType>* scene_;
  size_t n_reflections_;
};

template <typename CoordType>
ISurfacePtr<CoordType> MakeGlowingSurface(Color color,
                                          Traceable<CoordType>* scene) {
  return std::make_shared<Phong<CoordType>>(color, 0.5, 0.5, scene, 0);
}

template <typename CoordType>
ISurfacePtr<CoordType> MakeOpaqueSurface(CoordType opacity, CoordType gloss,
                                         Traceable<CoordType>* scene,
                                         size_t quality) {
  return std::make_shared<Phong<CoordType>>(Color{0, 0, 0}, opacity, gloss,
                                            scene, quality);
}

}  // namespace surfaces

#endif  // RAY_TRACER_21_PHONG_HPP
