// main.cpp
#include <iostream>
#include "Package.h"

int main() {
    // 测试普通包裹
    Package basic("Tom", "123 Main St", "City", "CA", 12345,
                  "Jerry", "456 Oak Rd", "Town", "NY", 67890,
                  10.0, 2.0);
    std::cout << "Basic package cost: $" << basic.calculateCost() << std::endl;

    // 测试两日达包裹
    TwoDayPackage twoDay("Tom", "123 Main St", "City", "CA", 12345,
                         "Jerry", "456 Oak Rd", "Town", "NY", 67890,
                         5.0, 1.5, 3.0);
    std::cout << "Two-day package cost: $" << twoDay.calculateCost() << std::endl;

    // 测试隔夜达包裹
    OvernightPackage overnight("Tom", "123 Main St", "City", "CA", 12345,
                               "Jerry", "456 Oak Rd", "Town", "NY", 67890,
                               5.0, 1.5, 0.5);
    std::cout << "Overnight package cost: $" << overnight.calculateCost() << std::endl;

    return 0;
}