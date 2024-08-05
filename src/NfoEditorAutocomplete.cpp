#include <NfoEditorAutocomplete.hpp>
#include <NfoEditorUtils.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <fmt/format.h>
#include <marisa/agent.h>
#include <marisa/keyset.h>
#include <marisa/trie.h>

namespace NfoEditor {

Autocomplete::Completer
Autocomplete::getCompleter(const std::string &completionSource) {
  auto it = m_tries.find(completionSource);
  if (it == m_tries.end()) {
    const auto trie = buildTrie(completionSource);
    it = m_tries.emplace(completionSource, trie).first;
  }

  return it->second;
} // namespace NfoEditor

void Autocomplete::registerCompletionSource(
    const std::string &completionSource) {
  getCompleter(completionSource);
}

std::shared_ptr<marisa::Trie>
Autocomplete::buildTrie(const std::string &completionSource) {
  auto trie = std::make_shared<marisa::Trie>();

  // Check $XDG_DATA_HOME/nfo-editor/autocomplete/<source>.txt for completions
  const auto completionFilePath = getNfoEditorDataDir() / "autocomplete" /
                                  fmt::format("{}.txt", completionSource);
  if (!std::filesystem::exists(completionFilePath)) {
    return trie;
  }

  marisa::Keyset keyset;
  std::ifstream completionFile{completionFilePath};
  std::string line;
  while (std::getline(completionFile, line)) {
    const auto candidate = trim(line);
    if (candidate.empty()) {
      continue;
    }
    keyset.push_back(candidate);
  }
  trie->build(keyset);

  return trie;
}

std::vector<std::string>
Autocomplete::Completer::complete(std::string_view prefix) const {
  marisa::Agent agent;
  agent.set_query(prefix);
  std::vector<std::string> matches;
  matches.reserve(s_maxMatches);

  while (m_trie->predictive_search(agent) && matches.size() < s_maxMatches) {
    matches.emplace_back(agent.key().str());
  }

  return matches;
}
} // namespace NfoEditor