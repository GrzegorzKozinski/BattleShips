#pragma once
#include <iostream>
#include <sstream>

template <typename... Args>
void log(const Args&... args)
{
    const bool printFlag{false};
    if (printFlag)
    {
        std::ostringstream oss;
        ((oss << args << " "), ...); // fold expression to concatenate all arguments

        std::cout << oss.str() << std::endl;
    }
}
