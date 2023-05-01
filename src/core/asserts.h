#include "core/logging.h"

#define ASSERT(condition, message) \
{ \
    if (!(condition)) { \
        LOG("%s", message); \
        __builtin_trap(); \
    } \
}

#define ASSERT_FAIL(message) ASSERT(false, message)