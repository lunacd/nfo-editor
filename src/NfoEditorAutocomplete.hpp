#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <marisa/trie.h>

namespace NfoEditor {
class Autocomplete {
public:
  struct CompletionData {
    marisa::Trie trie;
    std::unordered_map<std::string, std::unordered_set<std::string>>
        originalStrings;
  };

  class Completer {
  public:
    Completer(std::shared_ptr<CompletionData> completionData)
        : m_completionData{std::move(completionData)} {}

    [[nodiscard]] std::vector<std::string>
    complete(std::string_view prefix) const;

  private:
    std::shared_ptr<CompletionData> m_completionData;
  };

  Autocomplete() = default;

  void registerCompletionSource(const std::string &completionSource);

  Completer getCompleter(const std::string &completionSource);

private:
  std::unordered_map<std::string, std::shared_ptr<CompletionData>>
      m_completionData;

  static constexpr size_t s_maxMatches = 5;

  static std::shared_ptr<CompletionData>
  buildCompletionData(const std::string &completionSource);
};
} // namespace NfoEditor