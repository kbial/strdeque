#include <iostream>
#include "strdequeconst.h"

namespace
{
#ifndef NDEBUG
    const bool debug = true;
#else
    const bool debug = false;
#endif
}

namespace jnp1
{
    unsigned long emptystrdeque()
    {
        const static std::string emptystrdeque_name = "emptystrdeque";
        static bool is_initialized = false;
        static std::ios_base::Init init;

        if (!debug) return 0L;

        std::cerr << emptystrdeque_name << "()" << std::endl;
        if (!is_initialized)
        {
            std::cerr << "strdequeconst init invoked" << std::endl;
            is_initialized = true;
        }

        return 0L;
    }
}