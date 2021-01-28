#pragma once

#include "common.h"
#include "strength.h"

#include "kiwi/expression.h"
#include "kiwi/variable.h"

#include <string>
#include <unordered_map>
#include <variant>

namespace layout {

// An abstract constrainable class.
struct Constrainable {
  Constrainable() noexcept;

  [[nodiscard]] LinearSymbolic get(const std::string& name) const;

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

Constrainable make_constrainable(const std::string& name);

// An abstract constrainable that contains other widgets.
Constrainable make_contents_constrainable(const std::string& name);

}  // namespace layout