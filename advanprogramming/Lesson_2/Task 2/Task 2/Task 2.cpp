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

    smart_array(const smart_array& other) {
        capacity = other.capacity;
        size = other.size;
        data = new int[capacity];

        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    smart_array& operator=(const smart_array& other) {
        if (this == &other) {
            return *this; 
        }

        delete[] data;

        capacity = other.capacity;
        size = other.size;
        data = new int[capacity];

        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }

        return *this;
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
    smart_array arr(5);
    arr.add_element(1);
    arr.add_element(4);
    arr.add_element(155);

    smart_array new_array(2);
    new_array.add_element(44);
    new_array.add_element(34);

    arr = new_array;

    std::cout << arr.get_element(0) << std::endl; 
    std::cout << arr.get_element(1) << std::endl; 
}