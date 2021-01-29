#pragma once

#include "box_helper.h"
#include "constrainable.h"
#include "constraint_helper.h"
#include "spacers.h"

#include <iterator>
#include <utility>

namespace layout {

using Item_t = std::variant<LinearSymbolic, Constrainable, Spacer>;

template<typename Iterator>
class SequenceHelper : public ConstraintHelper {
public:
  SequenceHelper(std::string first_name, std::string last_name, Iterator first, Iterator last, int spacing = 10)
      : anchor_names{std::move(first_name), std::move(last_name)}, first{first}, last{last}, spacing{spacing} {}

private:
  [[nodiscard]] std::vector<kiwi::Constraint> constraints(const Constrainable&) override {
    using T = typename std::iterator_traits<Iterator>::value_type;
    static_assert(std::is_same_v<std::decay_t<T>, Item_t>);

    if (std::holds_alternative<Spacer>(*first)) {
      throw LayoutLogicError("First sequence item cannot be a spacer.");
    }

    if (first + 1 == last) {
      throw LayoutLogicError("Need at least two items in a sequence.");
    }

    std::vector<kiwi::Constraint> cns;
    for (; first + 1 != last; ++first) {
      LinearSymbolic first_anchor = get_anchor(*first, anchor_names.first);

      const auto next_it  = first + 1;
      bool next_is_spacer = std::holds_alternative<Spacer>(*next_it);
      const Spacer& s     = next_is_spacer ? std::get<Spacer>(*next_it) : Spacer{spacing};

      if (next_is_spacer) {
        if (first + 2 == last) {
          throw LayoutLogicError("Last sequence item cannot be a spacer.");
        }
        if (std::holds_alternative<Spacer>(*(first + 2))) {
          throw LayoutLogicError("Cannot have two consecutive spacers in a sequence.");
        }
        ++first;
      }

      LinearSymbolic second_anchor = get_anchor(*(first + 1), anchor_names.second);

      auto current_cns = ::layout::create_constraints(s, first_anchor, second_anchor);
      std::move(current_cns.begin(), current_cns.end(), std::back_inserter(cns));
    }
    return cns;
  }

  [[nodiscard]] LinearSymbolic get_anchor(const Item_t& item, const std::string& name) const {
    return std::holds_alternative<LinearSymbolic>(item) ? std::get<LinearSymbolic>(item)
                                                        : std::get<Constrainable>(item).get(name);
  }

  // The anchor names to form a constraint pair.
  std::pair<std::string, std::string> anchor_names;

  Iterator first, last;

  // Default spacing between items.
  int spacing;
};
}  // namespace layout