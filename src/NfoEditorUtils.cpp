#include <NfoEditorUtils.hpp>

#include <cstdlib>
#include <mutex>
#include <string_view>

namespace NfoEditor {
namespace {
std::filesystem::path getUserDataDir() {
  if (const auto xdgDataHome = NfoEditor::getEnv("XDG_DATA_HOME");
      !xdgDataHome.empty()) {
    return xdgDataHome;
  }
  return std::filesystem::path(NfoEditor::getEnv("HOME")) / ".local" / "share";
}
} // namespace

std::string getEnv(const std::string &name) {
  static std::mutex mutex;
  std::lock_guard<std::mutex> lock{mutex};
  // NOLINTNEXTLINE(concurrency-mt-unsafe)
  const char *value = std::getenv(name.c_str());
  return value != nullptr ? value : std::string{};
}

std::filesystem::path getNfoEditorDataDir() {
  return getUserDataDir() / "nfo-editor";
}

std::string_view trim(std::string_view input) {
  const auto isNotSpace = [](unsigned char ch) {
    return std::isspace(ch) == 0;
  };
  const size_t prefixLength = std::distance(
      input.cbegin(), std::find_if(input.cbegin(), input.cend(), isNotSpace));
  input.remove_prefix(prefixLength);
  const size_t suffixLength =
      std::distance(input.crbegin(),
                    std::find_if(input.crbegin(), input.crend(), isNotSpace));
  input.remove_suffix(suffixLength);
  return input;
}

} // namespace NfoEditor