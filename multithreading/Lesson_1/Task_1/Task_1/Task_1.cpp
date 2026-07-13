#include <iostream>
#include <thread>
#include <chrono>

int clients = 0;
const int MAX_CLIENTS = 10;
bool finished = false;

void clientGenerator()
{
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        clients++;

        std::cout << "Пришел клиент. В очереди: "
            << clients << std::endl;
    }

    finished = true;
}

void operatorWorker()
{
    while (!finished || clients > 0)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (clients > 0)
        {
            clients--;

            std::cout << "Оператор обслужил клиента. Осталось: "
                << clients << std::endl;
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