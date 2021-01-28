#include "spacers.h"

namespace layout {

// ------------------------------------------------------------------
// Spacer
// ------------------------------------------------------------------

BaseSpacer::BaseSpacer(int sz, Strength str) : size(sz), strength(str) {}

BaseSpacer& BaseSpacer::operator|(Strength str) {
  strength = str;
  return *this;
}

std::vector<kiwi::Constraint> BaseSpacer::create_constraints(
    const LinearSymbolic& first, const LinearSymbolic& second) const {
  auto cns = this->constraints(first, second);
  if (!strength.empty() && !strength.ignored()) {
    std::transform(cns.begin(), cns.end(), cns.begin(), [&](auto& cn) { return cn | strength; });
  }
  return cns;
}

// ------------------------------------------------------------------
// EqSpacer
// ------------------------------------------------------------------

std::vector<kiwi::Constraint> EqSpacer::constraints(const LinearSymbolic& first, const LinearSymbolic& second) const {
  kiwi::Expression e = std::visit([](auto& f, auto& s) { return s - f; }, first, second);
  return {e == size};
}

// ------------------------------------------------------------------
// LeSpacer
// ------------------------------------------------------------------

std::vector<kiwi::Constraint> LeSpacer::constraints(const LinearSymbolic& first, const LinearSymbolic& second) const {
  kiwi::Expression e = std::visit([](auto& f, auto& s) { return s - f; }, first, second);
  return {e <= size, e >= 0.0};
}

// ------------------------------------------------------------------
// GeSpacer
// ------------------------------------------------------------------

std::vector<kiwi::Constraint> GeSpacer::constraints(const LinearSymbolic& first, const LinearSymbolic& second) const {
  kiwi::Expression e = std::visit([](auto& f, auto& s) { return s - f; }, first, second);
  return {e >= size};
}

// ------------------------------------------------------------------
// FlexSpacer
// ------------------------------------------------------------------

FlexSpacer::FlexSpacer(int size, Strength str, Strength min_str, Strength eq_str)
    : BaseSpacer(size, str), min_strength(min_str.empty() ? Strength(ConstraintStrength::REQUIRED) : min_str),
      eq_strength(eq_str.empty() ? Strength(ConstraintStrength::MEDIUM) * 1.25 : eq_str) {}

std::vector<kiwi::Constraint> FlexSpacer::constraints(const LinearSymbolic& first, const LinearSymbolic& second) const {
  kiwi::Expression e = std::visit([](auto& f, auto& s) { return s - f; }, first, second);
  return {e >= size | min_strength, e == size | eq_strength};
}

std::vector<kiwi::Constraint> create_constraints(
    const Spacer& spacer, const LinearSymbolic& first, const LinearSymbolic& second) {
  return std::visit([&](const auto& s) { return s.create_constraints(first, second); }, spacer);
}

}  // namespace layout