#include "box.h"

namespace layout {

std::vector<kiwi::Constraint> Box::box_constraints(const Constrainable& c) {
  return {top == c.top, bottom == c.bottom, left == c.left, right == c.right};
}

std::vector<kiwi::Constraint> Box::box_constraints(const ContentsConstrainable& c) {
  return {top == c.contents_top, bottom == c.contents_bottom, left == c.contents_left, right == c.contents_right};
}

}  // namespace layout