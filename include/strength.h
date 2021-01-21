#pragma once

#include "kiwi/constraint.h"
#include "kiwi/strength.h"
#include "kiwi/symbolics.h"

#include <variant>

namespace layout {
enum class ConstraintStrength { IGNORE, WEAK, MEDIUM, STRONG, REQUIRED };

// An optional strength of some constraint.
class Strength {
public:
  Strength() = default;
  explicit Strength(double d);
  explicit Strength(ConstraintStrength cs);

  // Is the strength value empty
  [[nodiscard]] bool empty() const;

  // Is the strength value ignored.
  [[nodiscard]] bool ignored() const;

  // Quantify the strength value.
  [[nodiscard]] double as_double() const;

  // Helper function to multiply the strength by a number.
  friend Strength operator*(const Strength& s, double x);

private:
  // TODO: Do we need both std::monostate and ConstraintStrength::IGNORE?
  std::variant<std::monostate, double, ConstraintStrength> value;
};

// Make a new constraint with a possibly updated strength value.
kiwi::Constraint operator|(const kiwi::Constraint& constraint, const Strength& strength);

}  // namespace layout