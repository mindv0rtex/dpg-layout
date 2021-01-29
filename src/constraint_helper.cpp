#include "constraint_helper.h"

namespace layout {

ConstraintHelper::ConstraintHelper(Strength str) : strength(str) {}

ConstraintHelper& ConstraintHelper::operator|(Strength str) {
  strength = str;
  return *this;
}

[[nodiscard]] std::vector<kiwi::Constraint> ConstraintHelper::create_constraints(const Constrainable& c) {
  auto cns = this->constraints(c);
  if (!strength.empty() && !strength.ignored()) {
    std::transform(cns.begin(), cns.end(), cns.begin(), [&](auto& cn) { return cn | strength; });
  }
  return cns;
}

}  // namespace layout