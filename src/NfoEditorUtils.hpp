#pragma once

#include <filesystem>

namespace NfoEditor {

std::string getEnv(const std::string &name);
std::filesystem::path getNfoEditorDataDir();
std::string_view trim(std::string_view input);
std::string toLower(std::string_view input);

} // namespace NfoEditor
