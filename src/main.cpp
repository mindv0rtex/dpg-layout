#include "spacers.h"
#include "strength.h"

#include <iostream>

int main() {
  layout::Strength s{100.0};
  kiwi::Variable x1("x1");
  kiwi::Constraint c{x1 >= 0};
  auto c2 = c | s;
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
