#ifndef APPLICATION_ARGUMENTS_H
#define APPLICATION_ARGUMENTS_H

#include <string>
#include <map>

enum class ArgumentType {
    APPLICATION_ROOT,
    RESOURCES_ROOT
};

class ApplicationArguments {
public:
    ApplicationArguments(int argc, char* argv[]);

    std::string GetArgument(ArgumentType type);
private:
    std::map<ArgumentType, std::string> argumentsMap;

    void ParseArguments(int argc, char* argv[]);
};

#endif