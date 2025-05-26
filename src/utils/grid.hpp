#pragma once
#include <vector>
#include <stdexcept>

namespace utils {

template<typename T>
class Grid {
public:
    Grid(size_t width, size_t height) : width_(width), height_(height), data_(width * height) {}

    T& at(size_t x, size_t y) {
        if (x >= width_ || y >= height_) throw std::out_of_range("Grid index out of range");
        return data_[y * width_ + x];
    }

    const T& at(size_t x, size_t y) const {
        if (x >= width_ || y >= height_) throw std::out_of_range("Grid index out of range");
        return data_[y * width_ + x];
    }

    size_t getWidth() const { return width_; }
    size_t getHeight() const { return height_; }

private:
    size_t width_, height_;
    std::vector<T> data_;
};

} // namespace utils
