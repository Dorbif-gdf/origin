#include <iostream>
#include <pqxx/pqxx>
#include "ClientManager.h"


void printClients(const std::vector<ClientData>& clients) {
    if (clients.empty()) {
        std::cout << "  Клиенты не найдены\n";
        return;
    }

    for (const auto& client : clients) {
        std::cout << "  ID: " << client.id << "\n";
        std::cout << "  Имя: " << client.firstName << "\n";
        std::cout << "  Фамилия: " << client.lastName << "\n";
        std::cout << "  Email: " << client.email << "\n";
        std::cout << "  Телефоны: ";
        if (client.phones.empty()) {
            std::cout << "нет телефонов";
        }
        else {
            for (size_t i = 0; i < client.phones.size(); ++i) {
                std::cout << client.phones[i];
                if (i < client.phones.size() - 1) std::cout << ", ";
            }
        }
        std::cout << "\n  ---\n";
    }
}


template<typename Func>
void safeExecute(const std::string& operationName, Func func) {
    try {
        func();
        std::cout << "[OK] " << operationName << "\n";
    }
    catch (const pqxx::sql_error& e) {
        std::cout << "[ERROR] " << operationName << " - Ошибка SQL:\n";
        std::cout << "  " << e.what() << "\n";
        std::cout << "  Запрос: " << e.query() << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "[ERROR] " << operationName << " - " << e.what() << "\n";
    }
}

int main() {

    std::cout << "========================================\n";
    std::cout << "   УПРАВЛЕНИЕ КЛИЕНТАМИ (C++ + PostgreSQL)\n";
    std::cout << "========================================\n\n";

    try {
        pqxx::connection conn(
            "host=localhost "
            "port=5432 "
            "dbname=test "    
            "user=postgres "              
            "password=54142431"      
        );

        std::cout << "[OK] Подключение к PostgreSQL\n";

        ClientManager manager(conn);

        std::cout << "\n--- 1. СОЗДАНИЕ ТАБЛИЦ ---\n";
        safeExecute("Создание таблиц", [&]() {
            manager.createTables();
            });

        std::cout << "\n--- 2. ДОБАВЛЕНИЕ КЛИЕНТОВ ---\n";
        safeExecute("Добавление Ивана", [&]() {
            manager.addClient("Иван", "Петров", "ivan@example.com");
            });
        safeExecute("Добавление Марии", [&]() {
            manager.addClient("Мария", "Иванова", "maria@example.com");
            });
        safeExecute("Добавление Петра", [&]() {
            manager.addClient("Петр", "Сидоров", "petr@example.com");
            });
        safeExecute("Добавление Анны", [&]() {
            manager.addClient("Анна", "Кузнецова", "anna@example.com");
            });

        std::cout << "\n--- 3. ДОБАВЛЕНИЕ ТЕЛЕФОНОВ ---\n";
        safeExecute("Телефон для ID=1", [&]() {
            manager.addPhone(1, "+7-912-345-67-89");
            });
        safeExecute("Телефон для ID=1 (второй)", [&]() {
            manager.addPhone(1, "+7-912-345-67-90");
            });
        safeExecute("Телефон для ID=2", [&]() {
            manager.addPhone(2, "+7-922-111-22-33");
            });
        safeExecute("Телефон для ID=4", [&]() {
            manager.addPhone(4, "+7-933-444-55-66");
            });

        std::cout << "\n--- 4. ВСЕ КЛИЕНТЫ ---\n";
        try {
            auto clients = manager.getAllClients();
            printClients(clients);
        }
        catch (const std::exception& e) {
            std::cout << "[ERROR] Получение списка клиентов: " << e.what() << "\n";
        }

        std::cout << "\n--- 5. ОБНОВЛЕНИЕ КЛИЕНТА ID=1 ---\n";
        safeExecute("Обновление данных", [&]() {
            manager.updateClient(1, "Иван", "Петрович", "ivan.new@example.com");
            });

        std::cout << "\n--- 6. ПОИСК КЛИЕНТОВ ---\n";

        std::cout << "  Поиск по 'Иванов':\n";
        try {
            auto results = manager.findClient("Иванов");
            printClients(results);
        }
        catch (const std::exception& e) {
            std::cout << "  [ERROR] " << e.what() << "\n";
        }

        std::cout << "  Поиск по 'anna':\n";
        try {
            auto results = manager.findClient("anna");
            printClients(results);
        }
        catch (const std::exception& e) {
            std::cout << "  [ERROR] " << e.what() << "\n";
        }

        std::cout << "  Поиск по '+7-912':\n";
        try {
            auto results = manager.findClient("+7-912");
            printClients(results);
        }
        catch (const std::exception& e) {
            std::cout << "  [ERROR] " << e.what() << "\n";
        }

        std::cout << "\n--- 7. УДАЛЕНИЕ ТЕЛЕФОНА ID=2 ---\n";
        safeExecute("Удаление телефона", [&]() {
            manager.deletePhone(2);
            });

        std::cout << "\n--- 8. ОБНОВЛЁННЫЙ СПИСОК КЛИЕНТОВ ---\n";
        try {
            auto clients = manager.getAllClients();
            printClients(clients);
        }
        catch (const std::exception& e) {
            std::cout << "[ERROR] Получение списка клиентов: " << e.what() << "\n";
        }

        std::cout << "\n--- 9. УДАЛЕНИЕ КЛИЕНТА ID=3 ---\n";
        safeExecute("Удаление клиента", [&]() {
            manager.deleteClient(3);
            });

        std::cout << "\n--- 10. ФИНАЛЬНЫЙ СПИСОК КЛИЕНТОВ ---\n";
        try {
            auto clients = manager.getAllClients();
            printClients(clients);
        }
        catch (const std::exception& e) {
            std::cout << "[ERROR] Получение списка клиентов: " << e.what() << "\n";
        }

        std::cout << "\n========================================\n";
        std::cout << "   ВСЕ ТЕСТЫ ВЫПОЛНЕНЫ!\n";
        std::cout << "========================================\n";

    }
    catch (const pqxx::sql_error& e) {
        std::cout << "\n[FATAL] Ошибка подключения к PostgreSQL:\n";
        std::cout << "  " << e.what() << "\n";
        std::cout << "  Запрос: " << e.query() << "\n";
        std::cout << "\nПроверьте настройки подключения в main():\n";
        std::cout << "  - dbname: имя базы данных\n";
        std::cout << "  - user: ваш пользователь PostgreSQL\n";
        std::cout << "  - password: ваш пароль\n";
        return 1;
    }
    catch (const std::exception& e) {
        std::cout << "\n[FATAL] " << e.what() << "\n";
        return 1;
    }

    return 0;
}