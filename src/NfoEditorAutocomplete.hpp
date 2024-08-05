#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <marisa/trie.h>

namespace NfoEditor {
class Autocomplete {
public:
  Autocomplete();

  auto complete(std::string_view prefix) -> std::vector<std::string>;

private:
  marisa::Trie m_trie;

  static constexpr size_t s_maxMatches = 5;
};
} // namespace NfoEditor