#include <map>
#include <iostream>

std::map<int, std::string> error_list =
{
    {1, "Failed to initalize window"}
};

void throwError(int error_code)
{
    std::cout << "Error code " << error_code << ": " 
              << error_list[error_code] << std::endl;
}
