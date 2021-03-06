//
// Created by galqiwi on 05.10.2021.
//

#ifndef RAY_TRACER_21_IIMAGE_HPP
#define RAY_TRACER_21_IIMAGE_HPP

#include <memory>
#include <cstddef>
#include <string>
#include <iostream>
#include "../raytracer/Color.hpp"
namespace image {

class IImage {
 public:
  virtual void Set(size_t x, size_t y, Color c) = 0;
  virtual Color Get(size_t x, size_t y) = 0;
  virtual size_t Width() const = 0;
  virtual size_t Height() const = 0;
  virtual void Save(const std::string filename) = 0;
};

using IImagePtr = std::shared_ptr<IImage>;

}  // namespace image

#endif  // RAY_TRACER_21_IIMAGE_HPP
