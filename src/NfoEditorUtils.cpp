#include <NfoEditorUtils.hpp>

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <mutex>
#include <string_view>

namespace NfoEditor {
namespace {
std::filesystem::path getUserDataDir() {
  if (const auto xdgDataHome = getEnv("XDG_DATA_HOME"); !xdgDataHome.empty()) {
    return xdgDataHome;
  }
  return std::filesystem::path(getEnv("HOME")) / ".local" / "share";
}
} // namespace

std::string getEnv(const std::string &name) {
  static std::mutex mutex;
  std::lock_guard<std::mutex> lock{mutex};
  const char *value = std::getenv(name.c_str());
  return value != nullptr ? value : std::string{};
}

std::filesystem::path getNfoEditorDataDir() {
  return getUserDataDir() / "nfo-editor";
}

std::string_view trim(std::string_view input) {
  const auto isNotSpace = [](const unsigned char ch) {
    return std::isspace(ch) == 0;
  };
  const auto firstNonSpacesChar = std::ranges::find_if(input, isNotSpace);
  const size_t prefixLength = std::distance(input.begin(), firstNonSpacesChar);
  input.remove_prefix(prefixLength);

  const auto lastNonSpaceChar =
      std::find_if(input.rbegin(), input.rend(), isNotSpace);
  const size_t suffixLength = std::distance(input.rbegin(), lastNonSpaceChar);
  input.remove_suffix(suffixLength);
  return input;
}

std::string toLower(std::string_view input) {
  std::string result;
  std::ranges::transform(
      input, std::back_inserter(result),
      [](const unsigned char ch) { return std::tolower(ch); });
  return result;
}

} // namespace NfoEditor