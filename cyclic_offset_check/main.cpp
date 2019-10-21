#include <iostream>
#include <string>

int *zFunction(const std::string &str) {
    int *z = new int[str.size()];
    z[0] = 0;
    int left = 0;
    int right = 0;
    for (unsigned int i = 1; i < str.size(); i++) {
        if (i > right) {
            left = right = i;
            while (right < str.size() && str[right] == str[right - left]) {
                right++;
            }
            z[i] = right - left;
            right--;
        } else {
            //we are operating inside box
            int j = i - left;
            //if value does not stretches till right bound then just copy it.
            if (z[j] < right - i + 1) {
                z[i] = z[j];
            } else { //otherwise try to see if there are more matches.
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
    std::string tmp = str1 + (char) CHAR_MAX + str2;
    int *z = zFunction("abaabbaba");
    for (unsigned int i = 0; i < 9; i++)
        std::cout << z[i] << " ";

    return true;
}

int main() {
    isCyclicOffset("456", "123");
    return 0;
}