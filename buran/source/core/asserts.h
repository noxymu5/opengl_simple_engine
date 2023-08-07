#include "core/logging.h"

#define ASSERT(condition, message, ...) \
{ \
    if (!(condition)) { \
        LOG(message, ##__VA_ARGS__); \
        __debugbreak(); \
    } \
}

#define ASSERT_FAIL(message, ...) ASSERT(false, message, ##__VA_ARGS__)