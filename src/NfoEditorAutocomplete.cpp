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
  auto it = m_completionData.find(completionSource);
  if (it == m_completionData.end()) {
    const auto completionData = buildCompletionData(completionSource);
    it = m_completionData.emplace(completionSource, completionData).first;
  }

  return it->second;
} // namespace NfoEditor

void Autocomplete::registerCompletionSource(
    const std::string &completionSource) {
  getCompleter(completionSource);
}

std::shared_ptr<Autocomplete::CompletionData>
Autocomplete::buildCompletionData(const std::string &completionSource) {
  auto completionData = std::make_shared<CompletionData>();

  // Check $XDG_DATA_HOME/nfo-editor/autocomplete/<source>.txt for completions
  const auto completionFilePath = getNfoEditorDataDir() / "autocomplete" /
                                  fmt::format("{}.txt", completionSource);
  if (!std::filesystem::exists(completionFilePath)) {
    return completionData;
  }

  marisa::Keyset keyset;
  std::ifstream completionFile{completionFilePath};
  std::string line;
  while (std::getline(completionFile, line)) {
    const auto candidate = std::string(trim(line));
    const auto candidateLower = toLower(candidate);
    if (candidate.empty()) {
      continue;
    }
    keyset.push_back(candidateLower);
    const auto it = completionData->originalStrings.find(candidateLower);
    if (it == completionData->originalStrings.end()) {
      completionData->originalStrings.emplace(candidateLower,
                                             std::unordered_set{candidate});
    } else {
      it->second.emplace(candidate);
    }
  }
  completionData->trie.build(keyset);

  return completionData;
}

std::vector<std::string>
Autocomplete::Completer::complete(std::string_view prefix) const {
  marisa::Agent agent;
  agent.set_query(prefix);
  std::vector<std::string> matches;
  matches.reserve(s_maxMatches);

  while (m_completionData->trie.predictive_search(agent) &&
         matches.size() < s_maxMatches) {
    const auto match = agent.key().str();
    const auto &originalStrings =
        m_completionData->originalStrings.at(std::string(match));
    matches.insert(matches.end(), originalStrings.begin(),
                   originalStrings.end());
  }

  return matches;
}
} // namespace NfoEditor