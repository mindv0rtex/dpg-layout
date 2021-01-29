#pragma once

#include "sequence_helper.h"

namespace layout {

// Create a left-to-right SequenceHelper object.
template<typename Iterator>
std::unique_ptr<ConstraintHelper> horizontal(Iterator first, Iterator last, int spacing = 10) {
  return std::make_unique<SequenceHelper<Iterator>>("right", "left", first, last, spacing);
}

// Create a top-to-bottom SequenceHelper object.
template<typename Iterator>
std::unique_ptr<ConstraintHelper> vertical(Iterator first, Iterator last, int spacing = 10) {
  return std::make_unique<SequenceHelper<Iterator>>("bottom", "top", first, last, spacing);
}

// Create a SequenceHelper object that aligns an achor among all members of a sequence.
template<typename Iterator>
std::unique_ptr<ConstraintHelper> align(std::string anchor, Iterator first, Iterator last) {
  return std::make_unique<SequenceHelper<Iterator>>(anchor, anchor, first, last, 0);
}

}  // namespace layout