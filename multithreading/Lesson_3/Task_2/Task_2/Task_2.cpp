#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
#include <iterator>

template<typename Iterator, typename Function>
void parallel_for_each(Iterator begin, Iterator end, Function func)
{
    auto length = std::distance(begin, end);

    if (length <= 2)
    {
        for (; begin != end; ++begin)
        {
            func(*begin);
        }
        return;
    }

    Iterator middle = begin;
    std::advance(middle, length / 2);

    auto future = std::async(
        std::launch::async,
        parallel_for_each<Iterator, Function>,
        begin,
        middle,
        func
    );

    parallel_for_each(middle, end, func);

    future.get();
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::vector<int> numbers = { 1,2,3,4,5,6,7,8,9,10 };

    parallel_for_each(
        numbers.begin(),
        numbers.end(),
        [](int& value)
        {
            value *= 2;
        });

    std::cout << "Результат:\n";

    for (int value : numbers)
    {
        std::cout << value << " ";
    }

    return 0;
}