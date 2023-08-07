#pragma once

#include <string>

#define INIT_RESOURCE(resourceType) static std::string Name() { return #resourceType; }

class Resource {
};