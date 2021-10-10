//
// Created by galqiwi on 05.10.2021.
//
#include <vector>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <mutex>
#include <shared_mutex>
#include "PPMImage.hpp"

namespace image {

class PPMImage : public IImage {
 public:
  PPMImage(size_t w, size_t h)
      : w_(w), h_(h), data_(w, std::vector<Color>(h, Color{0, 1, 0})) {
  }

  explicit PPMImage(const char* filename) {
    std::ifstream fin(filename);
    std::string type, tmp_buffer;
    fin >> type;
    assert(type == "P3" || type == "P6");
    fin >> w_ >> h_;
    fin >> tmp_buffer;
    assert(tmp_buffer == "255");
    data_ = std::vector<std::vector<Color>>(w_, std::vector<Color>(h_));
    if (type == "P3") {
      ReadP3(fin);
    } else {
      ReadP6(fin);
    }
  }

  void Set(size_t x, size_t y, Color c) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    assert(0 <= x && x < w_);
    assert(0 <= y && y < h_);
    data_[x][y] = c;
  }

  Color Get(size_t x, size_t y) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    assert(0 <= x && x < w_);
    assert(0 <= y && y < h_);
    return data_[x][y];
  }

  size_t Width() const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return w_;
  }

  size_t Height() const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return h_;
  }

  void Save(const std::string filename) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    std::ofstream fout(filename);

    fout << "P3"
         << "\n";
    fout << w_ << " " << h_ << "\n";
    fout << 255 << "\n";
    for (int y = 0; y < h_; ++y) {
      for (int x = 0; x < w_; ++x) {
        PrintPixel(fout, data_[x][y]);
      }
    }

    fout << std::flush;
  }

 private:
  void ReadP3(std::istream& fin) {
    for (int y = 0; y < h_; ++y) {
      for (int x = 0; x < w_; ++x) {
        fin >> data_[x][y].r >> data_[x][y].g >> data_[x][y].b;
      }
    }
  }

  void ReadP6(std::istream& fin) {
    for (int y = 0; y < h_; ++y) {
      for (int x = 0; x < w_; ++x) {
        uint8_t r, g, b;
        fin >> std::noskipws >> b >> r >> g;
        data_[x][y] = Color{r / 255., g / 255., b / 255.};
      }
    }
  }

  void PrintPixel(std::ostream& out, Color color) {
    PrintSubPixel(out, color.r);
    PrintSubPixel(out, color.g);
    PrintSubPixel(out, color.b);
  }
  void inline PrintSubPixel(std::ostream& out, double sub_color) {
    out << std::max(0, std::min(255, (int)(sub_color * 255))) << " ";
  }

 private:
  mutable std::shared_mutex mutex_;
  size_t w_, h_;
  std::vector<std::vector<Color>> data_;
};

IImagePtr MakePPMImage(size_t w, size_t h) {
  return std::make_shared<PPMImage>(w, h);
}

IImagePtr MakePPMImage(const char* filename) {
  return std::make_shared<PPMImage>(filename);
}

}  // namespace image