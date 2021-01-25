#include "box_helper.h"

namespace layout {

std::vector<kiwi::Constraint> BoxHelper::box_constraints(const Constrainable& c) {
  // Any "contents_" key will do here.
  if (c.variables.contains("contents_left")) {
    return {
        variables.at("top") == c.variables.at("contents_top"),
        variables.at("bottom") == c.variables.at("contents_bottom"),
        variables.at("left") == c.variables.at("contents_left"),
        variables.at("right") == c.variables.at("contents_right")};
  } else {
    return {
        variables.at("top") == c.variables.at("top"), variables.at("bottom") == c.variables.at("bottom"),
        variables.at("left") == c.variables.at("left"), variables.at("right") == c.variables.at("right")};
  }
}
}  // namespace layout