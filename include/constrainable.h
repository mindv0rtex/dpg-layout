#pragma once

#include "strength.h"

#include "kiwi/expression.h"
#include "kiwi/variable.h"

#include <string>
#include <unordered_map>
#include <variant>

namespace layout {

// An abstract constrainable class.
struct Constrainable {
  explicit Constrainable(const std::string& name)
      : hug_width(ConstraintStrength::STRONG), hug_height(ConstraintStrength::STRONG),
        resist_width(ConstraintStrength::STRONG), resist_height(ConstraintStrength::STRONG),
        limit_width(ConstraintStrength::IGNORE), limit_height(ConstraintStrength::IGNORE) {
    // Left boundary.
    variables.try_emplace("left", name + "_left");
    // Top boundary.
    variables.try_emplace("top", name + "_top");
    // Width.
    variables.try_emplace("width", name + "_width");
    // Height.
    variables.try_emplace("height", name + "_height");

    // Right boundary.
    expressions.try_emplace("right", variables.at("left") + variables.at("width"));
    // Bottom boundary.
    expressions.try_emplace("bottom", variables.at("top") + variables.at("height"));
    // Horizontal center.
    expressions.try_emplace("h_center", variables.at("left") + 0.5 * variables.at("width"));
    // Vertical center.
    expressions.try_emplace("v_center", variables.at("top") + 0.5 * variables.at("height"));
  }

  std::unordered_map<std::string, kiwi::Variable> variables;
  std::unordered_map<std::string, kiwi::Expression> expressions;

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
  explicit ContentsConstrainable(const std::string& name) : Constrainable(name) {
    // Left contents boundary.
    variables.try_emplace("contents_left", name + "_contents_left");
    // Right contents boundary.
    variables.try_emplace("contents_right", name + "_contents_right");
    // Top contents boundary.
    variables.try_emplace("contents_top", name + "_contents_top");
    // Bottom contents boundary.
    variables.try_emplace("contents_bottom", name + "_contents_bottom");

    // Contents width.
    expressions.try_emplace("contents_width", variables.at("contents_right") - variables.at("contents_left"));
    // Contents height.
    expressions.try_emplace("contents_height", variables.at("contents_bottom") - variables.at("contents_top"));
    // Contents horizontal center.
    expressions.try_emplace("contents_h_center", variables.at("contents_left") + 0.5 * variables.at("contents_width"));
    // Contents vertical center.
    expressions.try_emplace("contents_v_center", variables.at("contents_top") + 0.5 * variables.at("contents_height"));
  }
};

}  // namespace layout