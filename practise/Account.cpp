#include <iostream>
#include "Account.h"
using namespace std;

int main() {
    // 测试基类Account
    Account acc(-100);
    cout << "Account balance: " << acc.getBalance() << endl;

    acc.credit(500);
    cout << "After credit 500: " << acc.getBalance() << endl;

    bool success = acc.debit(200);
    cout << "After debit 200: " << acc.getBalance() << " (" << (success ? "Success" : "Fail") << ")\n";

    success = acc.debit(400);
    cout << "After debit 400: " << acc.getBalance() << " (" << (success ? "Success" : "Fail") << ")\n\n";

    // 测试SavingsAccount
    SavingsAccount sa(1000, 0.05);
    cout << "SavingsAccount balance: " << sa.getBalance() << endl;
    
    double interest = sa.calculateInterest();
    sa.credit(interest);
    cout << "After interest credit: " << sa.getBalance() << "\n\n";

    // 测试CheckingAccount
    CheckingAccount ca(500, 2);
    cout << "CheckingAccount balance: " << ca.getBalance() << endl;

    ca.credit(100);
    cout << "After credit 100: " << ca.getBalance() << endl;

    success = ca.debit(200);
    cout << "After debit 200: " << ca.getBalance() << " (" << (success ? "Success" : "Fail") << ")\n";

    success = ca.debit(400);
    cout << "After debit 400: " << ca.getBalance() << " (" << (success ? "Success" : "Fail") << ")\n";

    return 0;
}