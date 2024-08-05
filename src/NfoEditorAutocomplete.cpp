#include <NfoEditorAutocomplete.hpp>
#include <iostream>
#include <marisa/agent.h>
#include <marisa/keyset.h>

namespace NfoEditor {
Autocomplete::Autocomplete() {
  marisa::Keyset keyset;
  keyset.push_back("alpha");
  keyset.push_back("beta");
  keyset.push_back("gamma");

  m_trie.build(keyset);
}

auto Autocomplete::complete(std::string_view prefix)
    -> std::vector<std::string> {
  marisa::Agent agent;
  agent.set_query(prefix);
  std::vector<std::string> matches;
  matches.reserve(s_maxMatches);

  while (m_trie.predictive_search(agent) && matches.size() < s_maxMatches) {
    matches.emplace_back(agent.key().str());
  }

  return matches;
}
} // namespace NfoEditor