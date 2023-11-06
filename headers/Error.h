#pragma once
#ifndef ERROR_H
#define ERROR_H

#include <map>
#include <iostream>

inline std::map<int, std::string> errors =
{
    {0, "Invalid error code"},
    {1, "Failed to initalize glfw"},
    {2, "Failed to initalize window"},
    {3, "Failed to load Glad"},
    {4, "Error reading shader programs"}
};

inline void throwError(int error_code)
{
    if (errors.find(error_code) != errors.end())
    {
        std::cout << "Error code " << error_code << ": " 
                << errors[error_code] << std::endl;
    } 
    else
    {
        std::cout << "Error code 0: " << errors[0] 
                << " (" << error_code << ")" << std::endl;
    }

    exit(error_code);
}

#endif /* ERROR_H */