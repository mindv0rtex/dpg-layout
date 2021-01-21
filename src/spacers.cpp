#include "spacers.h"

namespace layout {
FlexSpacer::FlexSpacer(int size, Strength min_str, Strength eq_str)
    : size(size), min_strength(min_str.empty() ? Strength(ConstraintStrength::REQUIRED) : min_str),
      eq_strength(eq_str.empty() ? Strength(ConstraintStrength::MEDIUM) * 1.25 : eq_str) {}

std::vector<kiwi::Constraint> create_constraints(
    const Spacer& spacer, const LinearSymbolic& first, const LinearSymbolic& second, Strength s) {
  kiwi::Expression e = std::visit([](auto& f, auto& s) { return s - f; }, first, second);

  auto cns = std::visit(
      utils::overload{
          [&](const EqSpacer& s) -> std::vector<kiwi::Constraint> { return {e == s.size}; },
          [&](const LeSpacer& s) -> std::vector<kiwi::Constraint> {
            return {e <= s.size, e >= 0.0};
          },
          [&](const GeSpacer& s) -> std::vector<kiwi::Constraint> { return {e >= s.size}; },
          [&](const FlexSpacer& s) -> std::vector<kiwi::Constraint> {
            return {e >= s.size | s.min_strength, e == s.size | s.eq_strength};
          }},
      spacer);
  if (!s.empty() && !s.ignored()) {
    std::transform(cns.begin(), cns.end(), cns.begin(), [&](auto& cn) { return cn | s; });
  }
  return cns;
}
}  // namespace layout