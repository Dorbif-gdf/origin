#include <iostream>
#include <mutex>

class Data
{
public:
    int value;

    std::mutex mtx;

    Data(int value)
        : value(value)
    {
    }
};

void swapLock(Data& first, Data& second)
{
    std::lock(first.mtx, second.mtx);

    std::lock_guard<std::mutex> lock1(first.mtx, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(second.mtx, std::adopt_lock);

    std::swap(first.value, second.value);
}

void swapScoped(Data& first, Data& second)
{
    std::scoped_lock lock(first.mtx, second.mtx);

    std::swap(first.value, second.value);
}

void swapUnique(Data& first, Data& second)
{
    std::unique_lock<std::mutex> lock1(first.mtx, std::defer_lock);
    std::unique_lock<std::mutex> lock2(second.mtx, std::defer_lock);

    std::lock(lock1, lock2);

    std::swap(first.value, second.value);
}

int main()
{
    setlocale(LC_ALL, "Russian");

    Data first(10);
    Data second(20);

    std::cout << "До обмена:\n";
    std::cout << "first = " << first.value << '\n';
    std::cout << "second = " << second.value << "\n\n";

    swapLock(first, second);

    std::cout << "После swapLock:\n";
    std::cout << "first = " << first.value << '\n';
    std::cout << "second = " << second.value << "\n\n";

    swapScoped(first, second);

    std::cout << "После swapScoped:\n";
    std::cout << "first = " << first.value << '\n';
    std::cout << "second = " << second.value << "\n\n";

    swapUnique(first, second);

    std::cout << "После swapUnique:\n";
    std::cout << "first = " << first.value << '\n';
    std::cout << "second = " << second.value << '\n';

    return 0;
}