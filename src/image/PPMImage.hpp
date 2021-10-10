//
// Created by galqiwi on 05.10.2021.
//

#ifndef RAY_TRACER_21_PPMIMAGE_HPP
#define RAY_TRACER_21_PPMIMAGE_HPP

#include "IImage.hpp"

namespace image {

IImagePtr MakePPMImage(size_t w, size_t h);

IImagePtr MakePPMImage(const char*);

}  // namespace image

#endif  // RAY_TRACER_21_PPMIMAGE_HPP
