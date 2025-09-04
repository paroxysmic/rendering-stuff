#include <iostream>
#include <string>
int main() {
    int ind = 0;
    std::string str = "this is a test of the split mechanic";
    while(str.find(" ", ind) != std::string::npos) {
        std::cout << str.find(" ", ind) << '\n';
        ind = str.find(" ", ind) + 1;
    }
    return 0;
}