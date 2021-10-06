//
// Created by galqiwi on 05.10.2021.
//

#ifndef RAY_TRACER_21_COLOR_HPP
#define RAY_TRACER_21_COLOR_HPP

struct Color {
  double r, g, b;

  static Color Default();
};

std::ostream& operator<<(std::ostream& out, const Color& color);

#endif  // RAY_TRACER_21_COLOR_HPP
