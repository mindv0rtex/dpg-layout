#include "constrainable.h"

namespace layout {

Constrainable::Constrainable() noexcept
    : hug_width(ConstraintStrength::STRONG), hug_height(ConstraintStrength::STRONG),
      resist_width(ConstraintStrength::STRONG), resist_height(ConstraintStrength::STRONG),
      limit_width(ConstraintStrength::IGNORE), limit_height(ConstraintStrength::IGNORE) {}

LinearSymbolic Constrainable::get(const std::string& name) const {
  if (variables.contains(name)) {
    return variables.at(name);
  }
  if (expressions.contains(name)) {
    return expressions.at(name);
  }
  throw LayoutLogicError(std::string("Invalid Constrainable symbolic name: ").append(name).c_str());
}

Constrainable make_constrainable(const std::string& name) {
  Constrainable c;

  // Left boundary.
  c.variables.try_emplace("left", name + "_left");
  // Top boundary.
  c.variables.try_emplace("top", name + "_top");
  // Width.
  c.variables.try_emplace("width", name + "_width");
  // Height.
  c.variables.try_emplace("height", name + "_height");

  // Right boundary.
  c.expressions.try_emplace("right", c.variables.at("left") + c.variables.at("width"));
  // Bottom boundary.
  c.expressions.try_emplace("bottom", c.variables.at("top") + c.variables.at("height"));
  // Horizontal center.
  c.expressions.try_emplace("h_center", c.variables.at("left") + 0.5 * c.variables.at("width"));
  // Vertical center.
  c.expressions.try_emplace("v_center", c.variables.at("top") + 0.5 * c.variables.at("height"));

  return c;
}

// An abstract constrainable that contains other widgets.
Constrainable make_contents_constrainable(const std::string& name) {
  auto c = make_constrainable(name);

  // Left contents boundary.
  c.variables.try_emplace("contents_left", name + "_contents_left");
  // Right contents boundary.
  c.variables.try_emplace("contents_right", name + "_contents_right");
  // Top contents boundary.
  c.variables.try_emplace("contents_top", name + "_contents_top");
  // Bottom contents boundary.
  c.variables.try_emplace("contents_bottom", name + "_contents_bottom");

  // Contents width.
  c.expressions.try_emplace("contents_width", c.variables.at("contents_right") - c.variables.at("contents_left"));
  // Contents height.
  c.expressions.try_emplace("contents_height", c.variables.at("contents_bottom") - c.variables.at("contents_top"));
  // Contents horizontal center.
  c.expressions.try_emplace(
      "contents_h_center", c.variables.at("contents_left") + 0.5 * c.variables.at("contents_width"));
  // Contents vertical center.
  c.expressions.try_emplace(
      "contents_v_center", c.variables.at("contents_top") + 0.5 * c.variables.at("contents_height"));

  return c;
}

}  // namespace layout