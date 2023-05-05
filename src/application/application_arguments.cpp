#include "application_arguments.h"

#include "core/asserts.h"
#include "core/logging.h"

static const std::map<std::string, ArgumentType> stringToArgumentType = {
    {"-resourcesRoot", ArgumentType::RESOURCES_ROOT}
};

ApplicationArguments::ApplicationArguments(int argc, char* argv[]) {
    ParseArguments(argc, argv);
}

std::string ApplicationArguments::GetArgument(ArgumentType type) {
    auto it = argumentsMap.find(type);
    ASSERT(it != argumentsMap.end(), "can not find specified argument")

    return it->second;
}

void ApplicationArguments::ParseArguments(int argc, char* argv[]) {
    argumentsMap[ArgumentType::APPLICATION_ROOT] = argv[0];

    if (argc == 1) {
        LOG("No arguments to parse")
    }

    for(int idx = 1; idx < argc; idx += 2) {
        std::string argString(argv[idx]);
        auto it = stringToArgumentType.find(argString);

        ASSERT(it != stringToArgumentType.end(), "unsupported argument type")
        ASSERT(idx + 1 < argc, "no value for argument")

        argumentsMap[it->second] = argv[idx + 1];
    }
}