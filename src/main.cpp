#include "boiler.hpp"
#include <iostream>
#include <string_view>
#include <vector>

std::vector<std::string_view> build_argument_list(int &argc, char *argv[]) {
  argc--;
  argv = argc ? argv + 1 : nullptr;
  std::vector<std::string_view> arguments{};
  for (int i{}; i < argc; ++i) {
    arguments.emplace_back(argv[i]);
  }

  return arguments;
}

int main(int argc, char *argv[]) {
  std::vector<std::string_view> arguments = build_argument_list(argc, argv);

  for (size_t i{}; i < arguments.size();) {
    std::string_view current_argument{arguments.at(i)};
    for (size_t j{}; j < current_argument.size();) {
      char c = current_argument.at(j++);
      switch (c) {
      case '-':
        if (current_argument.at(j) == 'h') {
          Boiler::display_help_message();
          i++;
        } else if (current_argument.at(j) == 'l') {
          std::string_view lang{};
          std::string_view path{};
          if (i == arguments.size() - 1) {
            std::cerr << "Expected language.\n";
            return 1;
          } else {
            i++;
            lang = arguments.at(i);
            if (i == arguments.size() - 1) {
              std::cerr << "Expected file path.\n";
              return 1;
            } else {
              i++;
              path = arguments.at(i);
              Boiler::create_file(path, lang);
              i++;
            }
          }
        } else if (current_argument.at(j) == '-') {
          j++;
          if (current_argument.substr(j) == "help") {
            Boiler::display_help_message();
            i++;
          } else if (current_argument.substr(j) == "lang") {
            std::string_view lang{};
            std::string_view path{};
            if (i == arguments.size() - 1) {
              std::cerr << "Expected language.\n";
              return 1;
            } else {
              i++;
              lang = arguments.at(i);
              if (i == arguments.size() - 1) {
                std::cerr << "Expected file path.\n";
                return 1;
              } else {
                i++;
                path = arguments.at(i);
                Boiler::create_file(path, lang);
                i++;
              }
            }
          }
        }
        break;
      }
    }
  }

  return 0;
}
