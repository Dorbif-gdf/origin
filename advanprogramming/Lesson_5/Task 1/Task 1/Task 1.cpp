#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    std::string text;
    std::getline(std::cin, text);

    std::map<char, int> freq;
    for (char c : text) {
        freq[c]++;
    }

    std::vector<std::pair<char, int>> vec(freq.begin(), freq.end());

    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    for (const auto& p : vec) {
        std::cout << p.first << ": " << p.second << std::endl;
    }

}