#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
#include <random>
#include <string>

void sumVectors(const std::vector<int>& a,
    const std::vector<int>& b,
    std::vector<int>& result,
    size_t begin,
    size_t end)
{
    for (size_t i = begin; i < end; i++)
    {
        result[i] = a[i] + b[i];
    }
}

double calculate(size_t size, int threadCount)
{
    std::vector<int> a(size);
    std::vector<int> b(size);
    std::vector<int> result(size);

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(1, 100);

    for (size_t i = 0; i < size; i++)
    {
        a[i] = dist(gen);
        b[i] = dist(gen);
    }

    std::vector<std::thread> threads;

    size_t blockSize = size / threadCount;

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < threadCount; i++)
    {
        size_t begin = i * blockSize;

        size_t end = (i == threadCount - 1)
            ? size
            : begin + blockSize;

        threads.emplace_back(sumVectors,
            std::cref(a),
            std::cref(b),
            std::ref(result),
            begin,
            end);
    }

    for (auto& t : threads)
        t.join();

    auto finish = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed = finish - start;

    return elapsed.count();
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::vector<size_t> sizes =
    {
        1000,
        10000,
        100000,
        1000000
    };

    std::vector<int> threadCounts =
    {
        1,
        2,
        4,
        8,
        16
    };

    std::cout << "Количество аппаратных потоков: "
        << std::thread::hardware_concurrency()
        << "\n\n";

    std::cout << std::setw(12) << "";

    for (size_t size : sizes)
    {
        std::cout << std::setw(12) << size;
    }

    std::cout << "\n";

    for (int threads : threadCounts)
    {
        std::cout << std::setw(12)
            << std::to_string(threads) + " потоков";

        for (size_t size : sizes)
        {
            double time = calculate(size, threads);

            std::cout << std::setw(12)
                << std::fixed
                << std::setprecision(6)
                << time;
        }

        std::cout << "\n";
    }

    return 0;
}