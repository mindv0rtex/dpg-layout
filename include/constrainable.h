#pragma once

#include "strength.h"

#include "kiwi/expression.h"
#include "kiwi/variable.h"

#include <string>

namespace layout {

// An abstract constrainable class.
struct Constrainable {
  explicit Constrainable(const std::string& name)
      : left(name.append("_left")), top(name.append("_top")), width(name.append("_width")),
        height(name.append("_height")), right(left + width), bottom(top + height), h_center(left + 0.5 * width),
        v_center(top + 0.5 * height), hug_width(ConstraintStrength::STRONG), hug_height(ConstraintStrength::STRONG),
        resist_width(ConstraintStrength::STRONG), resist_height(ConstraintStrength::STRONG),
        limit_width(ConstraintStrength::IGNORE), limit_height(ConstraintStrength::IGNORE) {}

  // Left boundary.
  kiwi::Variable left;

  // Top boundary.
  kiwi::Variable top;

  // Width.
  kiwi::Variable width;

  // Height.
  kiwi::Variable height;

  // Right boundary.
  kiwi::Expression right;

  // Bottom boundary.
  kiwi::Expression bottom;

  // Horizontal center.
  kiwi::Expression h_center;

  // Vertical center.
  kiwi::Expression v_center;

  // How strongly a widget hugs its width hint, i.e. width == hint | hug_width
  ConstraintStrength hug_width;

  // How strongly a widget hugs its height hint, i.e. height == hint | hug_height
  ConstraintStrength hug_height;

  // How strongly a widget resists clipping its width hint, i.e. width >= hint | resist_width
  ConstraintStrength resist_width;

  // How strongly a widget resists clipping its height hint, i.e. height >= hint | resist_height
  ConstraintStrength resist_height;

  // How strongly a widget resists expanding its width hint, i.e. width <= hint | limit_width
  ConstraintStrength limit_width;

  // How strongly a widget resists expanding its height hint, i.e. height <= hint | limit_height
  ConstraintStrength limit_height;
};

// An abstract constrainable that contains other widgets.
struct ContentsConstrainable : Constrainable {
  explicit ContentsConstrainable(const std::string& name)
      : Constrainable(name), contents_left(name.append("_contents_left")),
        contents_right(name.append("_contents_right")), contents_top(name.append("_contents_top")),
        contents_bottom(name.append("_contents_bottom")), contents_width(contents_right - contents_left),
        contents_height(contents_bottom - contents_top), contents_h_center(contents_left + 0.5 * contents_width),
        contents_v_center(contents_top + 0.5 * contents_height) {}

  // Left contents boundary.
  kiwi::Variable contents_left;

  // Right contents boundary.
  kiwi::Variable contents_right;

  // Top contents boundary.
  kiwi::Variable contents_top;

  // Bottom contents boundary.
  kiwi::Variable contents_bottom;

  // Contents width.
  kiwi::Expression contents_width;

  // Contents height.
  kiwi::Expression contents_height;

  // Contents horizontal center.
  kiwi::Expression contents_h_center;

  // Contents vertical center.
  kiwi::Expression contents_v_center;
};

}  // namespace layout