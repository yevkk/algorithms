#include <iostream>
#include <string>

unsigned int *zFunction(const std::string &str) {
    auto *z = new unsigned int[str.size()];
    z[0] = 0;
    unsigned int left = 0;
    unsigned int right = 0;
    for (unsigned int i = 1; i < str.size(); i++) {
        if (i > right) {
            left = right = i;
            while (right < str.size() && str[right] == str[right - left]) {
                right++;
            }
            z[i] = right - left;
            right--;
        } else {
            unsigned int j = i - left;
            if (z[j] < right - i + 1) {
                z[i] = z[j];
            } else {
                left = i;
                while (right < str.size() && str[right] == str[right - left]) {
                    right++;
                }
                z[i] = right - left;
                right--;
            }
        }
    }
    return z;
}

bool isCyclicOffset(const std::string &str1, const std::string &str2) {
    std::string tmp = str1 + (char) CHAR_MAX + str2 + str2;
    auto *z = zFunction(tmp);
    for (unsigned int i = str1.size() + 1; i < tmp.size(); i++) {
        if (z[i] == str2.size()) return true;
    }
    return false;
}

int main() {
    std::cout << std::boolalpha << isCyclicOffset("This is a sample text", "mple textThis is a sa");
    return 0;
}