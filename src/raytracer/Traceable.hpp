//
// Created by galqiwi on 06.10.2021.
//

#ifndef RAY_TRACER_21_TRACEABLE_HPP
#define RAY_TRACER_21_TRACEABLE_HPP

#include "Color.hpp"
#include "../math3d/Vector3D.hpp"

template <typename CoordType>
class Traceable {
 public:
  virtual Color Trace(math3d::Ray<CoordType> ray) = 0;
};

template <typename CoordType>
using TraceablePtr = std::shared_ptr<Traceable<CoordType>>;

#endif  // RAY_TRACER_21_TRACEABLE_HPP
