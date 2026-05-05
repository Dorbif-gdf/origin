#include <iostream>
#include <vector>
#include <sstream>

template <typename T>
T square(T value) {
    return value * value;
}

template <typename T>
std::vector<T> square(const std::vector<T>& vec) {
    std::vector<T> result;
    for (const auto& x : vec) {
        result.push_back(square(x));
    }
    return result;
}

int main() {
    int x;
    std::cin >> x;

    std::cout << "[IN]: " << x << std::endl;
    std::cout << "[OUT]: " << square(x) << std::endl;

    std::cin.ignore();

    std::string input;
    std::getline(std::cin, input);

    std::cout << "[IN]: " << input << std::endl;

    std::vector<int> vec;
    std::stringstream ss(input);
    int num;
    char comma;

    while (ss >> num) {
        vec.push_back(num);
        ss >> comma; 
    }

    std::vector<int> result = square(vec);

    std::cout << "[OUT]: ";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i];
        if (i != result.size() - 1) {
            std::cout << ", ";
        }
    }

}