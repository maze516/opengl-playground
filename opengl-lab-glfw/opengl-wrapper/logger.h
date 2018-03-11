#pragma once

#include <iostream>

#ifndef NDEBUG
#define DEBUG(x) do { \
    std::cerr << x << std::endl; \
} while (0)

#define PRINT_VALUE(x) do {\
    std::cerr << #x << ": " << x << std::endl;\
} while (0)
#else
#define DEBUG(x)
#define PRINT_VALUE(x)
#endif

#define INFO(x) do { \
    std::cerr << x << std::endl; \
} while (0)


