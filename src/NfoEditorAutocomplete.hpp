#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include <marisa/trie.h>

namespace NfoEditor {
class Autocomplete {
public:
  class Completer {
  public:
    Completer(std::shared_ptr<marisa::Trie> trie) : m_trie{std::move(trie)} {}

    [[nodiscard]] std::vector<std::string>
    complete(std::string_view prefix) const;

  private:
    std::shared_ptr<marisa::Trie> m_trie;
  };

  Autocomplete() = default;

  void registerCompletionSource(const std::string &completionSource);

  Completer getCompleter(const std::string &completionSource);

private:
  std::unordered_map<std::string, std::shared_ptr<marisa::Trie>> m_tries;

  static constexpr size_t s_maxMatches = 5;

  static std::shared_ptr<marisa::Trie>
  buildTrie(const std::string &completionSource);
};
} // namespace NfoEditor