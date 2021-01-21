#pragma once

namespace layout {

// Represent a point in 2D space.
template<typename T>
struct Point {
  T x, y;
};

// Represents 2D dimensions.
template<typename T>
struct Size {
  T width, height;
};

// Represents a 2D rectangle.
template<typename T>
struct Rect {
  T x, y, width, height;

  Point<T> pos() {
    return {x, y};
  }

  Size<T> size() {
    return {width, height};
  }
};

// Represents a 2D box (a collection of margins).
template<typename T>
struct Box {
  T top, right, bottom, left;

  Rect<T> rect() {
    return {left, top, right - left, bottom - top};
  }

  Size<T> size() {
    return {right - left, bottom - top};
  }

  Point<T> pos() {
    return {left, top};
  }
};

}  // namespace layout