#include <iostream>
#include <vector>

template <typename T>
class table {
private:
    std::vector<std::vector<T>> data;

public:
    table(size_t rows, size_t cols) {
        data.resize(rows, std::vector<T>(cols));
    }

    std::vector<T>& operator[](size_t index) {
        return data[index];
    }

    const std::vector<T>& operator[](size_t index) const {
        return data[index];
    }

    std::pair<size_t, size_t> Size() const {
        return { data.size(), data.empty() ? 0 : data[0].size() };
    }
};

int main() {
    table<int> test(2, 3);

    test[0][0] = 4;
    std::cout << test[0][0] << std::endl;

    auto size = test.Size();
    std::cout << "Rows: " << size.first << ", Cols: " << size.second << std::endl;

}