//
// Created by galqiwi on 10.10.2021.
//

#ifndef RAY_TRACER_21_SKY_HPP
#define RAY_TRACER_21_SKY_HPP

#include "Traceable.hpp"

template <typename CoordType>
class Sky : public Traceable<CoordType> {
 public:
  explicit Sky(image::IImagePtr image)
      : image_(image), block_size_(image->Height() / 3) {
  }
  Color Trace(math3d::Ray<CoordType> ray) {
    auto ray_x_a = abs(ray.direction.x);
    auto ray_y_a = abs(ray.direction.y);
    auto ray_z_a = abs(ray.direction.z);
    auto cube_v = ray.direction;
    cube_v = cube_v / std::max(std::max(ray_x_a, ray_y_a), ray_z_a);
    if (ray_y_a > ray_x_a && ray_y_a > ray_z_a) {
      int x = block_size_ * (cube_v.x / 2 + 1.5);
      int y = block_size_ * (cube_v.z / 2 + 0.5);
      x = std::max(std::min(x, (int)block_size_ * 2 - 1), (int)block_size_);
      y = std::max(std::min(y, (int)block_size_ - 1), 0);
      if (cube_v.y < 0) {
        y += 2 * block_size_;
      }
      return image_->Get(x, y);
    } else {
      int x = ((cube_v.z > cube_v.x) ? (cube_v.z + cube_v.x + 2)
                                     : (6 - cube_v.z - cube_v.x)) *
              block_size_ / 2;
      x = std::max(std::min(x, (int)block_size_ * 4 - 1), 0);
      size_t y = block_size_ * (1.5 - cube_v.y / 2);
      return image_->Get(x, y);
    }
  }

 private:
  image::IImagePtr image_;
  size_t block_size_;
};

#endif  // RAY_TRACER_21_SKY_HPP
