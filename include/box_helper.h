#pragma once

#include "constrainable.h"

#include <vector>

namespace layout {

struct BoxHelper : Constrainable {

  std::vector<kiwi::Constraint> box_constraints(const Constrainable& c);
};


}  // namespace layout