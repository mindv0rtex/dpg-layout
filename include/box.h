#pragma once

#include "constrainable.h"

#include <vector>

namespace layout {

struct Box: Constrainable {

  std::vector<kiwi::Constraint> box_constraints(const Constrainable& c);

  std::vector<kiwi::Constraint> box_constraints(const ContentsConstrainable& c);
};


}  // namespace layout