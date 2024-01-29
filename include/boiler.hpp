#pragma once

#include <cstdint>
#include <filesystem>
#include <string_view>

namespace Boiler {

namespace Config {
struct Params {
  std::string_view source_directory{};
  std::string_view boilerplates_directory{};
};
}; // namespace Config

/* clang-format off */

constexpr std::string_view help_message_v{
    "Boiler - Create files containing boilerplate code quickly.\n"
    "Usage: boiler <arguments>\n"
    "Arguments:\n"
    "\t-h, --help:\t\tDisplay the help message.\n"
    "\t-l, --lang <language>:\tCreate file(s) associated to specified language.\n"};

/* clang-format off */

void display_help_message();
void create_file(const std::filesystem::path &path, std::string_view language);
}; // namespace Boiler
