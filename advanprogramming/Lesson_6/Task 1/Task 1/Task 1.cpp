#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n; 

    std::vector<int> v(n);

    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
    }

    std::sort(v.begin(), v.end());
    auto it = std::unique(v.begin(), v.end());
    v.erase(it, v.end());

    for (int num : v) {
        std::cout << num << " ";
    }

}