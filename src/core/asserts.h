#include "core/logging.h"

#define ASSERT(condition, message, ...) \
{ \
    if (!(condition)) { \
        LOG(message, ##__VA_ARGS__); \
        __builtin_trap(); \
    } \
}

#define ASSERT_FAIL(message, ...) ASSERT(false, message, ##__VA_ARGS__)