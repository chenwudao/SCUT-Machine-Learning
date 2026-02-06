#include <iostream>
#include <cstring>
#include <algorithm> 
using namespace std;

class CHugeInt {
private:
    string num; 

    static string process_leading_zero(const string& s) {
        size_t start = 0;
        while (start < s.size() && s[start] == '0') {
            start++;
        }
        if (start == s.size()) { 
            return "0";
        }
        return s.substr(start);
    }

    static string add(const string& a, const string& b) {
        string res;
        int carry = 0; 
        int i = a.size() - 1; 
        int j = b.size() - 1;

        while (i >= 0 || j >= 0 || carry > 0) {
            int digitA = (i >= 0) ? (a[i] - '0') : 0; 
            int digitB = (j >= 0) ? (b[j] - '0') : 0; 
            int sum = digitA + digitB + carry;
            carry = sum / 10; 
            res.push_back((sum % 10) + '0'); 
            i--; 
            j--;
        }
        reverse(res.begin(), res.end()); 
        return process_leading_zero(res); 
    }

public:
    CHugeInt(const char* s) {
        string str(s);
        num = process_leading_zero(str);
    }

    CHugeInt(int n) {
        char buf[20]; 
        sprintf(buf, "%d", n);
        num = process_leading_zero(buf);
    }

    CHugeInt operator+(const CHugeInt& other) const {
        string sum_str = add(this->num, other.num);
        return CHugeInt(sum_str.c_str());
    }

    friend CHugeInt operator+(int n, const CHugeInt& h) {
        CHugeInt n_h(n);
        return h + n_h;
    }

    friend ostream& operator<<(ostream& os, const CHugeInt& h) {
        os << h.num;
        return os;
    }
};

int main() {
    char s[210];
    int n;
    while (cin >> s >> n) {
        CHugeInt a(s);
        CHugeInt b(n);
        cout << a + b << endl;
        cout << n + a << endl;
        cout << a + n << endl;
    }
    return 0;
}