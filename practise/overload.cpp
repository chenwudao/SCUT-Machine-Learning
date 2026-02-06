#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class String{
    public:
        String(const std::string& str) : p(str) {}
        friend std::ostream& operator<<(std::ostream& os, const String& s);

    private:
        std::string p;
};

std::ostream& operator<<(std::ostream& os, const String& s) {
    std::string result = s.p;
    std::vector<int> letter_pos;
    std::vector<char> letters;

    for (int i = 0; i < result.size(); ++i) {
        if ((result[i] >= 'A' && result[i] <= 'Z') || (result[i] >= 'a' && result[i] <= 'z')) {
            letter_pos.push_back(i);
            letters.push_back(result[i]);
        }
    }

    std::sort(letters.begin(), letters.end());

    for (int i = 0; i < letter_pos.size(); ++i) {
        result[letter_pos[i]] = letters[i];
    }

    os << result;
    return os;
}

int main(){
    std::string input;
    while(std::getline(std::cin, input)) {
        if (input.empty()) break;
        String s(input);
        std::cout << s << std::endl;
    }
    return 0;
}