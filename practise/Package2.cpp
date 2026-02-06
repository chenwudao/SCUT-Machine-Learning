#include <iostream>
#include <vector>
#include <memory>
#include "Package.h"

int main() {
    // Create vector of Package pointers
    std::vector<std::unique_ptr<Package>> packages;

    // Add different types of packages
    packages.push_back(std::make_unique<TwoDayPackage>("Alice", "123 Maple St", "Boston", "MA", 12345,
                                                       "Bob", "456 Oak St", "Chicago", "IL", 67890, 
                                                       5.0, 2.0, 5.0));
    packages.push_back(std::make_unique<OvernightPackage>("Charlie", "789 Pine St", "Seattle", "WA", 11223,
                                                          "David", "321 Birch St", "San Francisco", "CA", 44556, 
                                                          3.0, 2.5, 1.0));

    double totalCost = 0.0;

    // Process packages polymorphically
    for (const auto& pkg : packages) {
        std::cout << "Sender: " << pkg->senderName << "\n"
                  << "Recipient: " << pkg->recipientName << "\n"
                  << "Shipping Cost: $" << pkg->calculateCost() << "\n\n";
        totalCost += pkg->calculateCost();
    }

    // Print total shipping cost
    std::cout << "Total shipping cost: $" << totalCost << std::endl;

    return 0;
}
