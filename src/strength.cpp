#include "strength.h"

namespace layout {

Strength::Strength(double d) : value{d} {}

Strength::Strength(ConstraintStrength cs) : value{cs} {}

// Is the strength value empty
bool Strength::empty() const {
  return std::holds_alternative<std::monostate>(value);
}

// Is the strength value ignored.
bool Strength::ignored() const {
  return std::holds_alternative<ConstraintStrength>(value)
      && (std::get<ConstraintStrength>(value) == ConstraintStrength::IGNORE);
}

// Quantify the strength value.
double Strength::as_double() const {
  if (std::holds_alternative<double>(value)) {
    return std::get<double>(value);
  } else {
    switch (std::get<ConstraintStrength>(value)) {
    case ConstraintStrength::WEAK: return kiwi::strength::weak;
    case ConstraintStrength::MEDIUM: return kiwi::strength::medium;
    case ConstraintStrength::STRONG: return kiwi::strength::strong;
    case ConstraintStrength::REQUIRED: return kiwi::strength::required;
    case ConstraintStrength::IGNORE:
      // as_double() should not be called on IGNORE values.
      throw std::runtime_error("IGNORE constraint strength cannot be converted to double.");
    }
  }
}

// Helper function to multiply the strength by a number.
Strength operator*(const Strength& s, double x) {
  if (s.empty() || s.ignored()) {
    return s;
  }
  return Strength(s.as_double() * x);
}

// Make a new constraint with a possibly updated strength value.
kiwi::Constraint operator|(const kiwi::Constraint& constraint, const Strength& strength) {
  if (strength.empty()) {
    return constraint;
  }
  assert(!strength.ignored());
  return constraint | strength.as_double();
}
}  // namespace layout
