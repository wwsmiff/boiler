#pragma once

#include <cstdint>
#include <filesystem>
#include <string_view>

namespace Boiler
{

namespace Config
{
struct Params
{
  std::string_view source_directory{};
  std::string_view boilerplates_directory{};
};
}; // namespace Config

namespace Creation
{

enum Type
{
  None = 0x0,
  File = 0x1,
  Project = 0x2,
};

struct Info
{
  Type type;
  std::filesystem::path path{};
  std::string_view language{};
};

}; // namespace Creation

/* clang-format off */

constexpr std::string_view help_message_v{
    "Boiler - Create files containing boilerplate code quickly.\n"
    "Usage: boiler <arguments> <path>\n"
    "Arguments:\n"
    "\t-h, --help\t\t\tDisplay the help message.\n"
    "\t-l, --lang <language>\t\tCreate a file associated to specified language.\n"
    "\t-s, --single-file <path>\tCreate file(s) associated to specified language.\n"
    "\t-p, --project <path>\tCreate file(s) associated to specified language.\n"

};

/* clang-format on */

void display_help_message();

void create_file(const std::filesystem::path &path, std::string_view language);
void create(const Boiler::Creation::Info &info);

}; // namespace Boiler
