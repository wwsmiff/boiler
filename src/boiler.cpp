#include "boiler.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

namespace Boiler {

Boiler::Config::Params config{.source_directory = "./",
                              .boilerplates_directory = "./boilerplates/"};

void display_help_message() { std::cout << help_message_v << std::endl; }
void create_file(const std::filesystem::path &path, std::string_view language) {
  if (std::filesystem::exists(path))
    std::cout << "File exists." << std::endl;
  else {
    std::ofstream dest_file{path};
    std::stringstream path_stream{};
    path_stream << config.boilerplates_directory << language << "/source.txt";
    if (std::filesystem::exists(path_stream.str())) {
      std::ifstream source_file{path_stream.str()};
      dest_file << source_file.rdbuf();
      source_file.close();
    } else {
      std::cout << "Language or framework doesn't exist." << std::endl;
    }
    dest_file.close();
  }
}
}; // namespace Boiler
