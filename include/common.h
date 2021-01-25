#pragma once

#include "kiwi/expression.h"

#include <variant>

namespace layout {
using LinearSymbolic = std::variant<kiwi::Variable, kiwi::Expression, kiwi::Term>;

class NotImplemented : public std::logic_error {
public:
  explicit NotImplemented(const char* prefix)
      : std::logic_error(std::string(prefix).append(" : Function not implemented!")){};
};

}  // namespace layout