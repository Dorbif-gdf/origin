#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

std::atomic<int> clients{ 0 };
std::atomic<bool> finished{ false };

const int MAX_CLIENTS = 10;

void clientGenerator()
{
    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        ++clients;

        std::cout << "Пришел клиент. В очереди: "
            << clients.load() << std::endl;
    }

    finished.store(true);
}

void operatorWorker()
{
    while (!finished.load() || clients.load() > 0)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (clients.load() > 0)
        {
            --clients;

            std::cout << "Оператор обслужил клиента. Осталось: "
                << clients.load() << std::endl;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::thread producer(clientGenerator);
    std::thread worker(operatorWorker);

    producer.join();
    worker.join();

    std::cout << "\nВсе клиенты обслужены!" << std::endl;

    return 0;
}