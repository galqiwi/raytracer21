//
// Created by galqiwi on 05.10.2021.
//

#ifndef RAY_TRACER_21_PLAIN_HPP
#define RAY_TRACER_21_PLAIN_HPP

#include "IObject.hpp"
#include "../surfaces/Phong.hpp"

namespace objects {

template <typename CoordType>
class Plain : public objects::IObject<CoordType> {
 public:
  Plain(math3d::Vector3D<CoordType> norm, math3d::Vector3D<CoordType> point,
        surfaces::ISurfacePtr<CoordType> black_surface,
        surfaces::ISurfacePtr<CoordType> white_surface)
      : norm_(norm),
        point_(point),
        black_surface_(black_surface),
        white_surface_(white_surface) {
  }
  std::optional<CoordType> Intersects(math3d::Ray<CoordType> ray) {
    CoordType dist = ((point_ - ray.point) * norm_) / (ray.direction * norm_);
    if (dist > 0) {
      return dist;
    } else {
      return std::nullopt;
    }
  }

  virtual Color IntersectColor(math3d::Ray<CoordType> ray) {
    auto intersection = Intersects(ray);
    if (!intersection.has_value()) {
      throw NoIntersection();
    }

    math3d::Vector3D<CoordType> hit =
        ray.point + math3d::Norm(ray.direction) * intersection.value();

    int x = static_cast<int>(std::floor(hit.x));
    int z = static_cast<int>(std::floor(hit.z));

    bool is_white = ((abs(x % 2) + abs(z % 2)) % 2) == 1;
    if (is_white) {
      return white_surface_->GetColor(ray, norm_, hit);
    } else {
      return black_surface_->GetColor(ray, norm_, hit);
    }
  }

 private:
  math3d::Vector3D<CoordType> norm_;
  math3d::Vector3D<CoordType> point_;
  surfaces::ISurfacePtr<CoordType> black_surface_;
  surfaces::ISurfacePtr<CoordType> white_surface_;
};

}  // namespace objects

#endif  // RAY_TRACER_21_PLAIN_HPP
