//
// Created by galqiwi on 05.10.2021.
//

#ifndef RAY_TRACER_21_IOBJECT_HPP
#define RAY_TRACER_21_IOBJECT_HPP

#include <optional>
#include "Vector3D.hpp"

namespace objects {

template <typename CoordType>
class IObject {
 public:
  virtual std::optional<CoordType> Intersects(math::Ray<CoordType> ray) = 0;
  virtual Color IntersectColor(math::Ray<CoordType> ray) = 0;
};

template <typename CoordType>
using IObjectPtr = std::shared_ptr<IObject<CoordType>>;

}  // namespace objects

#endif  // RAY_TRACER_21_IOBJECT_HPP
