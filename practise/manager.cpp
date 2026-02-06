#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

class Manager {
public:
    string id;
    string name;
    double basicsalary;
    static double total;
    static int count;

    Manager(const string& id_, const string& name_, double basicsalary_)
        : id(id_), name(name_), basicsalary(basicsalary_) {
        count++;
    }
    virtual ~Manager() {}
    virtual double getSalary() const = 0;
    virtual string getType() const = 0;
};
double Manager::total = 0;
int Manager::count = 0;

class CustManager : public Manager {
public:
    double deduction, seasonbonus;
    CustManager(const string& id_, const string& name_, double basicsalary_, double deduction_, double seasonbonus_)
        : Manager(id_, name_, basicsalary_), deduction(deduction_), seasonbonus(seasonbonus_) {}
    double getSalary() const override {
        return basicsalary + deduction + seasonbonus * 4;
    }
    string getType() const override {
        return "CustManager";
    }
};

class SalesManager : public Manager {
public:
    double salebonus, annualbonus;
    SalesManager(const string& id_, const string& name_, double basicsalary_, double salebonus_, double annualbonus_)
        : Manager(id_, name_, basicsalary_), salebonus(salebonus_), annualbonus(annualbonus_) {}
    double getSalary() const override {
        return basicsalary + salebonus + annualbonus;
    }
    string getType() const override {
        return "SalesManager";
    }
};

int main() {
    int K;
    while (cin >> K) {
        vector<Manager*> managers;
        Manager::total = 0;
        Manager::count = 0;
        for (int i = 0; i < K; ++i) {
            int type;
            string id, name;
            double basicsalary;
            cin >> type >> id >> name >> basicsalary;
            if (type == 1) {
                double deduction, seasonbonus;
                cin >> deduction >> seasonbonus;
                managers.push_back(new CustManager(id, name, basicsalary, deduction, seasonbonus));
            } else {
                double salebonus, annualbonus;
                cin >> salebonus >> annualbonus;
                managers.push_back(new SalesManager(id, name, basicsalary, salebonus, annualbonus));
            }
        }
        for (auto m : managers) {
            Manager::total += m->getSalary();
        }
        stable_sort(managers.begin(), managers.end(), [](Manager* a, Manager* b) {
            return a->getSalary() > b->getSalary();
        });
        for (auto m : managers) {
            cout << m->id << " " << m->name << " " << m->getType() << " ";
            cout << fixed << setprecision(2) << m->getSalary() << endl;
        }
        double avg = Manager::total / Manager::count;
        for (auto m : managers) {
            if (m->getSalary() >= avg) {
                cout << m->id << " " << m->name << " " << m->getType() << " ";
                cout << fixed << setprecision(2) << m->getSalary() << endl;
            }
        }
        for (auto m : managers) delete m;
    }
    return 0;
}