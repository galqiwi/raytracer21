//
// Created by galqiwi on 05.10.2021.
//

#ifndef RAY_TRACER_21_SCENE_HPP
#define RAY_TRACER_21_SCENE_HPP

#include <memory>
#include <optional>
#include <vector>
#include "Color.hpp"
#include "../math3d/Vector3D.hpp"
#include "objects/IObject.hpp"
#include "Traceable.hpp"

template <typename CoordType>
class Scene : public Traceable<CoordType> {
 public:
  Scene() : sky_(std::nullopt) {
  }

  Scene(TraceablePtr<CoordType> sky) : sky_(sky) {
  }

  Color Trace(math3d::Ray<CoordType> ray) {
    std::optional<CoordType> min_distance{std::nullopt};
    objects::IObjectPtr<CoordType> closest_object{nullptr};

    for (const auto& object : objects_) {
      auto intersection = object->Intersects(ray);
      if (intersection.has_value()) {
        if (!min_distance.has_value() ||
            min_distance.value() > intersection.value()) {
          min_distance = intersection.value();
          closest_object = object;
        }
      }
    }

    if (min_distance.has_value()) {
      return closest_object->IntersectColor(ray);
    } else {
      if (sky_.has_value()) {
        return sky_.value()->Trace(ray);
      } else {
        return Color::Default();
      }
    }
  }

  void AddObject(objects::IObjectPtr<CoordType> object) {
    objects_.push_back(std::move(object));
  }

 private:
  std::vector<objects::IObjectPtr<CoordType>> objects_;
  std::optional<TraceablePtr<CoordType>> sky_;
};

#endif  // RAY_TRACER_21_SCENE_HPP
