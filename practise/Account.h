#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
using namespace std;

class Account {
public:
    Account(double initialBalance) : balance(initialBalance) {}
    virtual ~Account() {}

    virtual void credit(double amount) {
        balance += amount;
    }

    virtual bool debit(double amount) {
        if (amount > balance) {
            return false;
        }
        balance -= amount;
        return true;
    }

    double getBalance() const {
        return balance;
    }

protected:
    double balance;
};

class SavingsAccount : public Account {
    double interestRate;
public:
    SavingsAccount(double initialBalance, double rate) 
        : Account(initialBalance), interestRate(rate) {}
    
    double calculateInterest() const {
        return balance * interestRate;
    }
};

class CheckingAccount : public Account {
    double fee;
public:
    CheckingAccount(double initialBalance, double f) 
        : Account(initialBalance), fee(f) {}
    
    void credit(double amount) {
        Account::credit(amount);
        balance -= fee;
    }
    
    bool debit(double amount) {
        if (Account::debit(amount)) {
            balance -= fee;
            return true;
        }
        return false;
    }
};

#endif