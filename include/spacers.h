#pragma once

#include "common.h"
#include "strength.h"
#include "utils.h"

#include <variant>

namespace layout {

class BaseSpacer {
public:
  explicit BaseSpacer(int sz, Strength str = Strength());

  BaseSpacer& operator|(Strength str);

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
class EqSpacer : public BaseSpacer {
  [[nodiscard]] std::vector<kiwi::Constraint> constraints(
      const LinearSymbolic& first, const LinearSymbolic& second) const override;

public:
  EqSpacer(int sz) : BaseSpacer(sz) {}
};

// A spacer which represents a flexible space with a maximum value.
class LeSpacer : public BaseSpacer {
  [[nodiscard]] std::vector<kiwi::Constraint> constraints(
      const LinearSymbolic& first, const LinearSymbolic& second) const override;
};

// A spacer which represents a flexible space with a minimum value.
class GeSpacer : public BaseSpacer {
  [[nodiscard]] std::vector<kiwi::Constraint> constraints(
      const LinearSymbolic& first, const LinearSymbolic& second) const override;
};

// A spacer with a hard minimum and a preference for that minimum.
class FlexSpacer : public BaseSpacer {
public:
  FlexSpacer(int size, Strength str, Strength min_str, Strength eq_str);

private:
  [[nodiscard]] std::vector<kiwi::Constraint> constraints(
      const LinearSymbolic& first, const LinearSymbolic& second) const override;

  Strength min_strength;
  Strength eq_strength;
};

using Spacer = std::variant<EqSpacer, LeSpacer, GeSpacer, FlexSpacer>;

std::vector<kiwi::Constraint> create_constraints(
    const Spacer& spacer, const LinearSymbolic& first, const LinearSymbolic& second);

}  // namespace layout