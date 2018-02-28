#pragma once

#include <iostream>

#ifdef SHOW_DEBUG_INFO
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
