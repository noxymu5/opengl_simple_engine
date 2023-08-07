#pragma once

#include <string>
#include <map>

enum class ArgumentType {
    APPLICATION_ROOT,
    RESOURCES_ROOT,
    SCENE_NAME
};

class ApplicationArguments {
public:
    ApplicationArguments(int argc, char* argv[]);

    std::string TryGetArgument(ArgumentType type);
    std::string GetArgument(ArgumentType type);
private:
    std::map<ArgumentType, std::string> argumentsMap;

    void ParseArguments(int argc, char* argv[]);
};