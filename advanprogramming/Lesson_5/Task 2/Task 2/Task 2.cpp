#include <iostream>
#include <set>

int main() {
    int n;
    std::cin >> n;

    std::set<int, std::greater<int>> numbers;

    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        numbers.insert(x);
    }

    for (int num : numbers) {
        std::cout << num << std::endl;
    }

}