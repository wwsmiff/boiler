#include "boiler.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace Boiler
{
Boiler::Config::Params config{.source_directory = "./",
                              .boilerplates_directory = "./boilerplates/"};

void display_help_message() { std::cout << help_message_v << std::endl; }
void create_file(const std::filesystem::path &path, std::string_view language)
{
  if (std::filesystem::exists(path))
    std::cout << "File exists." << std::endl;
  else
  {
    std::ofstream dest_file{path};
    std::stringstream path_stream{};
    path_stream << config.boilerplates_directory << language << "/source.txt";
    if (std::filesystem::exists(path_stream.str()))
    {
      std::ifstream source_file{path_stream.str()};
      dest_file << source_file.rdbuf();
      source_file.close();
    }
    else
    {
      std::cout << "Language or framework doesn't exist." << std::endl;
    }
    dest_file.close();
  }
}

void create(const Boiler::Creation::Info &info)
{
  if (info.type == Boiler::Creation::Type::File)
  {
    if (std::filesystem::exists(info.path))
      std::cout << "File exists." << std::endl;
    else
    {
      std::ofstream dest_file{info.path};
      std::stringstream path_stream{};
      path_stream << config.boilerplates_directory << info.language
                  << "/source.txt";
      if (std::filesystem::exists(path_stream.str()))
      {
        std::ifstream source_file{path_stream.str()};
        dest_file << source_file.rdbuf();
        source_file.close();
      }
      else
      {
        std::cout << "Language or framework doesn't exist." << std::endl;
      }
      dest_file.close();
    }
  }
  else if (info.type == Boiler::Creation::Project)
  {
    if (std::filesystem::exists(info.path))
      std::cout << "Path exists." << std::endl;
    else
    {
      if (info.language == "c" || info.language == "cpp")
      {
        std::stringstream path_stream{};
        std::filesystem::create_directory(info.path);
        path_stream << info.path.c_str() << "/src";
        std::filesystem::create_directory(path_stream.str());
        path_stream.str(std::string{});
        path_stream << info.path.c_str() << "/include";
        std::filesystem::create_directory(path_stream.str());
        path_stream.str(std::string{});
        if (info.language == "c")
        {
          path_stream << info.path.c_str() << "/src/main.c";
          create_file(path_stream.str(), "c");
        }
        if (info.language == "cpp")
        {
          path_stream << info.path.c_str() << "/src/main.cpp";
          create_file(path_stream.str(), "cpp");
          path_stream.str(std::string{});
          path_stream << config.boilerplates_directory << info.language
                      << "/CMakeLists.txt";
          std::ifstream cmake_in(path_stream.str());
          path_stream.str(std::string{});
          path_stream << info.path.c_str() << "/CMakeLists.txt";
          std::ofstream cmake_out(path_stream.str());
          cmake_out << cmake_in.rdbuf();
          cmake_in.close();
          cmake_out.close();
        }
      }
    }
  }
}

}; // namespace Boiler
