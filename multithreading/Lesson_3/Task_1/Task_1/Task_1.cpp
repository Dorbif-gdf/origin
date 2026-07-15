#include <iostream>
#include <vector>
#include <future>
#include <algorithm>

void findMin(const std::vector<int>& arr,
    int start,
    std::promise<int> promise)
{
    int minIndex = start;

    for (int i = start + 1; i < arr.size(); i++)
    {
        if (arr[i] < arr[minIndex])
        {
            minIndex = i;
        }
    }

    promise.set_value(minIndex);
}

void selectionSort(std::vector<int>& arr)
{
    for (int i = 0; i < arr.size() - 1; i++)
    {
        std::promise<int> promise;
        std::future<int> future = promise.get_future();

        auto task = std::async(
            std::launch::async,
            findMin,
            std::cref(arr),
            i,
            std::move(promise)
        );

        int minIndex = future.get();

        std::swap(arr[i], arr[minIndex]);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::vector<int> arr = { 8, 5, 2, 9, 1, 7 };

    std::cout << "Исходный массив:\n";

    for (int x : arr)
        std::cout << x << " ";

    std::cout << "\n\n";

    selectionSort(arr);

    std::cout << "Отсортированный массив:\n";

    for (int x : arr)
        std::cout << x << " ";

    std::cout << std::endl;

    return 0;
}