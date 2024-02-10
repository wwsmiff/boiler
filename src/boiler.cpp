#include "boiler.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

const std::string home = getenv("HOME");

namespace Boiler
{
Boiler::Config::Params config{
    .source_directory = "./",
    .boilerplates_directory =
        (std::filesystem::exists(std::string{home + "/.boiler"}))
            ? std::string{home + "/.boiler/boilerplates/"}
            : "./boilerplates/"};

void display_help_message() { std::cout << help_message_v << std::endl; }
void create_file(const std::filesystem::path &path,
                 const Boiler::Creation::Info &info)
{
  if (std::filesystem::exists(path))
    std::cerr << "File exists." << std::endl;
  else
  {
    std::ofstream dest_file{path};
    std::stringstream path_stream{};
    if (info.framework == "none")
      path_stream << config.boilerplates_directory << info.language
                  << "/source.txt";
    else
      path_stream << config.boilerplates_directory << info.language << '/'
                  << info.framework << "/source.txt";
    if (std::filesystem::exists(path_stream.str()))
    {
      std::ifstream source_file{path_stream.str()};
      dest_file << source_file.rdbuf();
      source_file.close();
      dest_file.close();
    }
    else
    {
      std::cerr << "Language or framework not supported." << std::endl;
    }
  }
}

void create(const Boiler::Creation::Info &info)
{
  if (info.type == Boiler::Creation::Type::File)
  {
    if (std::filesystem::exists(info.path))
      std::cout << "File exists." << std::endl;
    else
      create_file(info.path, info);
  }
  else if (info.type == Boiler::Creation::Project)
  {
    if (std::filesystem::exists(info.path))
      std::cout << "Path exists." << std::endl;

    else
    {
      if (info.language == "c" || info.language == "cpp")
      {
        std::stringstream dest_path{info.path.c_str()};
        std::stringstream cmake_source_path{};
        std::filesystem::create_directory(dest_path.str());
        dest_path.str({});
        dest_path << info.path.c_str() << "/include";
        std::filesystem::create_directory(dest_path.str());
        dest_path.str({});
        dest_path << info.path.c_str() << "/src";
        std::filesystem::create_directory(dest_path.str());
        dest_path << "/main." << info.language;
        create_file(dest_path.str(), info);
        dest_path.str({});
        if (info.framework == "none")
          cmake_source_path << config.boilerplates_directory << info.language
                            << "/CMakeLists.txt";
        else
          cmake_source_path << config.boilerplates_directory << info.language
                            << '/' << info.framework << "/CMakeLists.txt";

        std::ifstream cmake_source{cmake_source_path.str()};
        dest_path << info.path.c_str() << "/CMakeLists.txt";
        std::ofstream cmake_dest{dest_path.str()};
        cmake_dest << cmake_source.rdbuf();
        cmake_source.close();
        cmake_dest.close();
      }
    }
  }
}
}; // namespace Boiler
