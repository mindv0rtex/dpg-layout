#pragma once

#include "strength.h"

namespace layout {

struct Constrainable;

class ConstraintHelper {
public:
  ConstraintHelper() = default;
  virtual ~ConstraintHelper() {};

  explicit ConstraintHelper(Strength str);

  ConstraintHelper& operator|(Strength str);

  // Called to generate the constraints for the component.
  [[nodiscard]] std::vector<kiwi::Constraint> create_constraints(const Constrainable& c);

private:
  // Generate constraints for the given component.
  [[nodiscard]] virtual std::vector<kiwi::Constraint> constraints(const Constrainable&) = 0;

  Strength strength;
};
}  // namespace layout