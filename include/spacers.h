#pragma once

#include "strength.h"
#include "utils.h"

#include <variant>

namespace layout {

// A spacer which represents a fixed amount of space.
struct EqSpacer {
  int size;
};

// A spacer which represents a flexible space with a maximum value.
struct LeSpacer {
  int size;
};

// A spacer which represents a flexible space with a minimum value.
struct GeSpacer {
  int size;
};

// A spacer with a hard minimum and a preference for that minimum.
struct FlexSpacer {
  FlexSpacer(int size, Strength min_str, Strength eq_str);

  int size;
  Strength min_strength;
  Strength eq_strength;
};

using Spacer         = std::variant<EqSpacer, LeSpacer, GeSpacer, FlexSpacer>;
using LinearSymbolic = std::variant<kiwi::Variable, kiwi::Expression, kiwi::Term>;

std::vector<kiwi::Constraint> create_constraints(
    const Spacer& spacer, const LinearSymbolic& first, const LinearSymbolic& second, Strength s = Strength());

}  // namespace layout