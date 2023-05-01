#include <stdio.h>
#include <iostream>
#include <cstdarg>

#define LOG(msg, ...) { \
    printf(msg, ##__VA_ARGS__); \
    std::cout << std::endl; \
}

// #define LogImpl(type, msg, ...) printf(msg, ##__VA_ARGS__);

// #define LOG_MSG (msg, ...)       LogImpl(LogType::MESSAGE, msg, ##__VA_ARGS__)
// #define LOG_WARNING (msg, ...)   LogImpl(LogType::WARNING, msg, __VA_ARGS__)
// #define LOG_CRITICAL (msg, ...)  LogImpl(LogType::CRITICAL, msg, __VA_ARGS__)
// #define LOG_ERROR (msg, ...)     LogImpl(LogType::ERROR, msg, __VA_ARGS__)