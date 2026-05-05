#include <iostream>
#include <vector>
#include <algorithm>

class Counter {
private:
    int sum = 0;
    int count = 0;

public:
    void operator()(int value) {
        if (value % 3 == 0) {
            sum += value;
            count++;
        }
    }

    int get_sum() const {
        return sum;
    }

    int get_count() const {
        return count;
    }
};

int main() {
    std::vector<int> v = { 4, 1, 3, 6, 25, 54 };

    Counter counter;

    counter = std::for_each(v.begin(), v.end(), counter);

    std::cout << "[IN]: ";
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::cout << "[OUT]: get_sum() = " << counter.get_sum() << std::endl;
    std::cout << "[OUT]: get_count() = " << counter.get_count() << std::endl;

}