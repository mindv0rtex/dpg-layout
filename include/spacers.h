#pragma once

#include "common.h"
#include "strength.h"
#include "utils.h"

#include <variant>

namespace layout {

class Spacer {
public:
  explicit Spacer(int sz, Strength str = Strength());

  Spacer& operator|(Strength str);

  [[nodiscard]] std::vector<kiwi::Constraint> create_constraints(
      const LinearSymbolic& first, const LinearSymbolic& second) const;

protected:
  int size;
  Strength strength;

private:
  [[nodiscard]] virtual std::vector<kiwi::Constraint> constraints(
      const LinearSymbolic&, const LinearSymbolic&) const = 0;
};

// A spacer which represents a fixed amount of space.
class EqSpacer : public Spacer {
  [[nodiscard]] std::vector<kiwi::Constraint> constraints(
      const LinearSymbolic& first, const LinearSymbolic& second) const override;
};

// A spacer which represents a flexible space with a maximum value.
class LeSpacer : Spacer {
  [[nodiscard]] std::vector<kiwi::Constraint> constraints(
      const LinearSymbolic& first, const LinearSymbolic& second) const override;
};

// A spacer which represents a flexible space with a minimum value.
class GeSpacer : Spacer {
  [[nodiscard]] std::vector<kiwi::Constraint> constraints(
      const LinearSymbolic& first, const LinearSymbolic& second) const override;
};

// A spacer with a hard minimum and a preference for that minimum.
class FlexSpacer : Spacer {
public:
  FlexSpacer(int size, Strength str, Strength min_str, Strength eq_str);

private:
  [[nodiscard]] std::vector<kiwi::Constraint> constraints(
      const LinearSymbolic& first, const LinearSymbolic& second) const override;

  Strength min_strength;
  Strength eq_strength;
};

}  // namespace layout