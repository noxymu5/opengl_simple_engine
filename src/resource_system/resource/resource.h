#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

#define INIT_RESOURCE(resourceType) static std::string Name() { return #resourceType; }

class Resource {
};

#endif