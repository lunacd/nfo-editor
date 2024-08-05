#include <NfoEditorAutocomplete.hpp>
#include <NfoEditorUtils.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <marisa/key.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include <fmt/format.h>
#include <marisa/agent.h>
#include <marisa/keyset.h>
#include <marisa/trie.h>

namespace NfoEditor {
namespace {
std::filesystem::path
getCompletionFilePath(const std::string &completionSource) {
  return getNfoEditorDataDir() / "autocomplete" /
         fmt::format("{}.txt", completionSource);
}

void exportCompletionToFile(
    const std::string &completionSource,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &originalStrings) {
  const auto completionFilePath = getCompletionFilePath(completionSource);
  std::ofstream completionFile{completionFilePath};
  for (const auto &stringPairs : originalStrings) {
    for (const auto &line : stringPairs.second) {
      completionFile << line << "\n";
    }
  }
}
} // namespace

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
  const auto completionFilePath = getCompletionFilePath(completionSource);
  if (!std::filesystem::exists(completionFilePath)) {
    return completionData;
  }

  std::ifstream completionFile{completionFilePath};
  std::string line;
  while (std::getline(completionFile, line)) {
    const auto candidate = std::string(trim(line));
    const auto candidateLower = toLower(candidate);
    if (candidate.empty()) {
      continue;
    }
    completionData->keyset.push_back(candidateLower);
    const auto it = completionData->originalStrings.find(candidateLower);
    if (it == completionData->originalStrings.end()) {
      completionData->originalStrings.emplace(candidateLower,
                                              std::unordered_set{candidate});
    } else {
      it->second.emplace(candidate);
    }
  }
  completionData->trie.build(completionData->keyset);

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

void Autocomplete::Completer::addCandidate(const std::string &candidate) {
  const auto candidateLower = toLower(candidate);
  m_completionData->keyset.push_back(candidateLower);
  m_completionData->trie.build(m_completionData->keyset);
  const auto it = m_completionData->originalStrings.find(candidateLower);
  if (it == m_completionData->originalStrings.end()) {
    m_completionData->originalStrings.emplace(candidateLower,
                                              std::unordered_set{candidate});
  } else {
    it->second.emplace(candidate);
  }
}

void Autocomplete::exportCompletionData() const {
  for (const auto &completionSource : m_completionData) {
    exportCompletionToFile(completionSource.first,
                           completionSource.second->originalStrings);
  }
}
} // namespace NfoEditor