#include "common.h"
#include "constrainable.h"
#include "sequence_helper.h"

#include "kiwi/debug.h"

int main() {
  std::vector<layout::SequenceHelper::Item_t> v = {
      layout::make_constrainable("foo"), layout::make_constrainable("bar"), layout::Spacer{10},
      layout::make_constrainable("zee")};

  layout::SequenceHelper sh("right", "left", 5);

  auto cns = sh.constraints(v.begin(), v.end());

  for (auto& c : cns) {
    kiwi::debug::dump(c);
  }

  return 0;
}
