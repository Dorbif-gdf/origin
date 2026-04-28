#include <iostream>
#include <stdexcept>

class smart_array {
private:
    int* data;
    int capacity;   
    int size;       

public:
    smart_array(int cap) : capacity(cap), size(0) {
        if (cap <= 0) {
            throw std::invalid_argument("Capacity must be > 0");
        }
        data = new int[capacity];
    }

    void add_element(int value) {
        if (size >= capacity) {
            int new_capacity = capacity * 2;
            int* new_data = new int[new_capacity];

            for (int i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }

            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }

        data[size++] = value;
    }

    int get_element(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    ~smart_array() {
        delete[] data;
    }
};

int main() {
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);

        std::cout << arr.get_element(1) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

}