#include "layout_helpers.h"

#include "kiwi/debug.h"

using namespace layout;

int main() {
  std::vector<Item_t> v = {make_constrainable("foo"), make_constrainable("bar")};

  auto helper = horizontal(v.begin(), v.end(), 5);
  auto cns    = helper->create_constraints(Constrainable());

  for (auto& c : cns) {
    kiwi::debug::dump(c);
  }

  return 0;
}
