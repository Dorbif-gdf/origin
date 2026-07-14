#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <windows.h>

std::mutex consoleMutex;

void setCursorPosition(short x, short y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD pos = { x, y };

    SetConsoleCursorPosition(hConsole, pos);
}

void worker(int number, int iterations)
{
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i <= iterations; i++)
    {
        {
            std::lock_guard<std::mutex> lock(consoleMutex);

            setCursorPosition(0, number);

            int percent = i * 100 / iterations;

            int barWidth = 20;

            int progress = percent * barWidth / 100;

            std::cout << "Поток N" << number + 1
                << " | ID: " << std::this_thread::get_id()
                << " | [";

            for (int j = 0; j < barWidth; j++)
            {
                if (j < progress)
                    std::cout << char('#');   // █
                else
                    std::cout << '-';
            }

            std::cout << "] "
                << percent << "%     ";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    auto end = std::chrono::steady_clock::now();

    double seconds =
        std::chrono::duration<double>(end - start).count();

    {
        std::lock_guard<std::mutex> lock(consoleMutex);

        setCursorPosition(0, number);

        std::cout << "Поток N" << number + 1
            << " | ID: " << std::this_thread::get_id()
            << " | [####################] 100%"
            << " | Время: "
            << seconds
            << " сек          ";
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int threadCount;
    int iterations;

    std::cout << "Введите количество потоков: ";
    std::cin >> threadCount;

    std::cout << "Введите длину расчета: ";
    std::cin >> iterations;

    std::vector<std::thread> threads;

    for (int i = 0; i < threadCount; i++)
    {
        threads.emplace_back(worker, i, iterations);
    }

    for (auto& t : threads)
    {
        t.join();
    }

    setCursorPosition(0, threadCount + 2);

    std::cout << "\nВсе потоки завершили работу.\n";

    return 0;
}