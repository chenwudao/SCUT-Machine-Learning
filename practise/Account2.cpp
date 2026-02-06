#include <iostream>
#include <vector>
#include "Account.h"

using namespace std;

int main() {
    // Create a vector to hold Account pointers.
    vector<Account*> accounts;

    // Populate the vector with a mix of SavingsAccount and CheckingAccount objects.
    // For example:
    accounts.push_back(new SavingsAccount(1000.0, 0.05));   // Initial balance = $1000, interest rate = 5%
    accounts.push_back(new CheckingAccount(1200.0, 1.50));    // Initial balance = $1200, fee = $1.50 per transaction
    accounts.push_back(new SavingsAccount(1500.0, 0.03));     // Initial balance = $1500, interest rate = 3%
    accounts.push_back(new CheckingAccount(800.0, 2.00));     // Initial balance = $800, fee = $2.00 per transaction

    double amount;

    // Process each account
    for (size_t i = 0; i < accounts.size(); i++) {
        cout << "\n--- Processing Account #" << (i + 1) << " ---\n";
        cout << "Current balance: $" << accounts[i]->getBalance() << "\n";

        // Withdraw an amount
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        accounts[i]->debit(amount);

        // Deposit an amount
        cout << "Enter amount to deposit: ";
        cin >> amount;
        accounts[i]->credit(amount);

        // If this is a SavingsAccount, calculate and credit interest
        SavingsAccount* savingsPtr = dynamic_cast<SavingsAccount*>(accounts[i]);
        if (savingsPtr != nullptr) {
            double interest = savingsPtr->calculateInterest();
            cout << "Calculated interest: $" << interest << "\n";
            accounts[i]->credit(interest);
        }

        // Print updated balance after transactions
        cout << "Updated balance: $" << accounts[i]->getBalance() << "\n";
    }

    // Clean up dynamically allocated memory.
    for (Account* acc : accounts) {
        delete acc;
    }
    accounts.clear();

    return 0;
}