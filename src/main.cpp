#include <iostream>
#include "command.h"

int main()
{
    int commandCount;
    std::cout << "Enter the number of commands: ";
    std::cin >> commandCount;
    std::cout << "Average time is: " << smd::calculateAverageTime(commandCount);
    return 0;
}