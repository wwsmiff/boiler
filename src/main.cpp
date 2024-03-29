#include "boiler.hpp"
#include <iostream>
#include <string_view>
#include <vector>

std::vector<std::string_view> build_argument_list(int &argc, char *argv[])
{
  argc--;
  argv = argc ? argv + 1 : nullptr;
  std::vector<std::string_view> arguments{};
  for (int i{}; i < argc; ++i)
  {
    arguments.emplace_back(argv[i]);
  }

  return arguments;
}

int main(int argc, char *argv[])
{
  std::vector<std::string_view> arguments = build_argument_list(argc, argv);
  Boiler::Creation::Info creation_info{
      .type = Boiler::Creation::Type::None, .path = "", .language = ""};

  for (size_t i{}; i < arguments.size(); ++i)
  {
    auto current_argument{arguments.at(i)};
    for (size_t j{}; j < current_argument.size(); ++j)
    {
      if (current_argument.at(j++) == '-')
      {
        if (current_argument.at(j) == '-')
        {
          j++;
          if (current_argument.substr(j) == "help")
          {
            Boiler::display_help_message();
          }
          else if (current_argument.substr(j) == "single-file")
          {
            creation_info.type = Boiler::Creation::Type::File;
            // TODO: Implement check for overwriting creation
            if (i == arguments.size() - 1)
            {
              std::cerr << "Expected path." << std::endl;
              return 1;
            }
            else
              creation_info.path = arguments.at(++i);
          }

          else if (current_argument.substr(j) == "lang")
          {
            creation_info.language = arguments.at(i);
            if (i == arguments.size() - 1)
            {
              std::cerr << "Expected language." << std::endl;
              return 1;
            }
            else
            {
              creation_info.language = arguments.at(++i);
            }
          }
          else if (current_argument.substr(j) == "project")
          {
            creation_info.type = Boiler::Creation::Type::Project;
            // TODO: Implement check for overwriting creation
            if (i == arguments.size() - 1)
            {
              std::cerr << "Expected path." << std::endl;
              return 1;
            }
            else
              creation_info.path = arguments.at(++i);
          }
        }
        else if (current_argument.at(j) == 'h')
        {
          Boiler::display_help_message();
        }
        else if (current_argument.at(j) == 's')
        {
          creation_info.type = Boiler::Creation::Type::File;
          // TODO: Implement check for overwriting creation
          if (i == arguments.size() - 1)
          {
            std::cerr << "Expected path." << std::endl;
            return 1;
          }
          else
            creation_info.path = arguments.at(++i);
        }
        else if (current_argument.at(j) == 'l')
        {
          creation_info.language = arguments.at(i);
          if (i == arguments.size() - 1)
          {
            std::cerr << "Expected language." << std::endl;
            return 1;
          }
          else
          {
            creation_info.language = arguments.at(++i);
          }
        }
        else if (current_argument.at(j) == 'p')
        {
          creation_info.type = Boiler::Creation::Type::Project;
          // TODO: Implement check for overwriting creation
          if (i == arguments.size() - 1)
          {
            std::cerr << "Expected path." << std::endl;
            return 1;
          }
          else
            creation_info.path = arguments.at(++i);
        }
        else if (current_argument.at(j) == 'l')
        {
          creation_info.language = arguments.at(i);
          if (i == arguments.size() - 1)
          {
            std::cerr << "Expected language." << std::endl;
            return 1;
          }
          else
          {
            creation_info.language = arguments.at(++i);
          }
        }

        else if (current_argument.at(j) == 'f')
        {
          if (i == arguments.size() - 1)
          {
            std::cerr << "Expected framework." << std::endl;
            return 1;
          }
          else
            creation_info.framework = arguments.at(++i);
        }
      }
    }
  }

  Boiler::create(creation_info);

  return 0;
}
