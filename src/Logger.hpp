#pragma once
#include <sstream>
#include <iostream>

template <typename... Args>
void log(const Args &...args)
{
    const bool printFlag{1};
    if(printFlag)
    {
        std::ostringstream oss;
        ((oss << args << " "), ...); // fold expression to concatenate all arguments

        std::cout << oss.str() << std::endl;
    }
}

