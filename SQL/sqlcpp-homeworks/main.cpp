#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <algorithm>

class ClientManager {
private:
    pqxx::connection& conn;

public:
    ClientManager(pqxx::connection& c) : conn(c) {}

    void createTables() {
        pqxx::work tx(conn);

        tx.exec(
            "CREATE TABLE IF NOT EXISTS clients ("
            "    id SERIAL PRIMARY KEY,"
            "    first_name VARCHAR(50) NOT NULL,"
            "    last_name VARCHAR(50) NOT NULL,"
            "    email VARCHAR(100) UNIQUE NOT NULL"
            ");"
        );

        tx.exec(
            "CREATE TABLE IF NOT EXISTS phones ("
            "    id SERIAL PRIMARY KEY,"
            "    client_id INTEGER REFERENCES clients(id) ON DELETE CASCADE,"
            "    phone_number VARCHAR(20) NOT NULL"
            ");"
        );

        tx.commit();
        std::cout << "Таблицы созданы (или уже существуют)\n";
    }

    void addClient(const std::string& firstName,
        const std::string& lastName,
        const std::string& email) {
        try {
            pqxx::work tx(conn);
            tx.exec(
                "INSERT INTO clients (first_name, last_name, email) "
                "VALUES (" +
                tx.quote(firstName) + ", " +
                tx.quote(lastName) + ", " +
                tx.quote(email) + ")"
            );
            tx.commit();
            std::cout << "Клиент добавлен!\n";
        }
        catch (const pqxx::sql_error& e) {
            std::cout << "Ошибка: такой email уже существует!\n";
        }
    }

    void addPhone(int clientId, const std::string& phoneNumber) {
        try {
            pqxx::work tx(conn);

            auto result = tx.exec("SELECT id FROM clients WHERE id = " + std::to_string(clientId));
            if (result.empty()) {
                std::cout << "Клиент с id " << clientId << " не найден!\n";
                return;
            }

            tx.exec(
                "INSERT INTO phones (client_id, phone_number) "
                "VALUES (" + std::to_string(clientId) + ", " + tx.quote(phoneNumber) + ")"
            );
            tx.commit();
            std::cout << "Телефон добавлен!\n";
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }

    void updateClient(int clientId,
        const std::string& firstName,
        const std::string& lastName,
        const std::string& email) {
        pqxx::work tx(conn);

        auto result = tx.exec("SELECT id FROM clients WHERE id = " + std::to_string(clientId));
        if (result.empty()) {
            std::cout << "Клиент с id " << clientId << " не найден!\n";
            return;
        }

        tx.exec(
            "UPDATE clients SET "
            "first_name = " + tx.quote(firstName) + ", "
            "last_name = " + tx.quote(lastName) + ", "
            "email = " + tx.quote(email) + " "
            "WHERE id = " + std::to_string(clientId)
        );
        tx.commit();
        std::cout << "Данные клиента обновлены!\n";
    }

    void deletePhone(int phoneId) {
        pqxx::work tx(conn);

        auto result = tx.exec("SELECT id FROM phones WHERE id = " + std::to_string(phoneId));
        if (result.empty()) {
            std::cout << "Телефон с id " << phoneId << " не найден!\n";
            return;
        }

        tx.exec("DELETE FROM phones WHERE id = " + std::to_string(phoneId));
        tx.commit();
        std::cout << "Телефон удалён!\n";
    }

    void deleteClient(int clientId) {
        pqxx::work tx(conn);

        auto result = tx.exec("SELECT id FROM clients WHERE id = " + std::to_string(clientId));
        if (result.empty()) {
            std::cout << "Клиент с id " << clientId << " не найден!\n";
            return;
        }

        tx.exec("DELETE FROM clients WHERE id = " + std::to_string(clientId));
        tx.commit();
        std::cout << "Клиент и все его телефоны удалены!\n";
    }

    void findClient(const std::string& searchText) {
        pqxx::work tx(conn);

        std::string query =
            "SELECT DISTINCT c.id, c.first_name, c.last_name, c.email, "
            "       STRING_AGG(p.phone_number, ', ') as phones "
            "FROM clients c "
            "LEFT JOIN phones p ON c.id = p.client_id "
            "WHERE c.first_name ILIKE " + tx.quote("%" + searchText + "%") + " "
            "   OR c.last_name ILIKE " + tx.quote("%" + searchText + "%") + " "
            "   OR c.email ILIKE " + tx.quote("%" + searchText + "%") + " "
            "   OR p.phone_number ILIKE " + tx.quote("%" + searchText + "%") + " "
            "GROUP BY c.id";

        auto result = tx.exec(query);

        if (result.empty()) {
            std::cout << "Клиенты не найдены!\n";
            return;
        }

        std::cout << "\n=== РЕЗУЛЬТАТЫ ПОИСКА ===\n";
        for (const auto& row : result) {
            std::cout << "ID: " << row["id"].c_str() << "\n";
            std::cout << "Имя: " << row["first_name"].c_str() << "\n";
            std::cout << "Фамилия: " << row["last_name"].c_str() << "\n";
            std::cout << "Email: " << row["email"].c_str() << "\n";
            std::string phones = row["phones"].is_null() ? "нет телефонов" : row["phones"].c_str();
            std::cout << "Телефоны: " << phones << "\n";
            std::cout << "---\n";
        }
    }

    void showAllClients() {
        pqxx::work tx(conn);

        auto result = tx.exec(
            "SELECT c.id, c.first_name, c.last_name, c.email, "
            "       STRING_AGG(p.phone_number, ', ') as phones "
            "FROM clients c "
            "LEFT JOIN phones p ON c.id = p.client_id "
            "GROUP BY c.id "
            "ORDER BY c.id"
        );

        if (result.empty()) {
            std::cout << "Нет клиентов в базе данных.\n";
            return;
        }

        std::cout << "\n=== ВСЕ КЛИЕНТЫ ===\n";
        for (const auto& row : result) {
            std::cout << "ID: " << row["id"].c_str() << "\n";
            std::cout << "Имя: " << row["first_name"].c_str() << "\n";
            std::cout << "Фамилия: " << row["last_name"].c_str() << "\n";
            std::cout << "Email: " << row["email"].c_str() << "\n";
            std::string phones = row["phones"].is_null() ? "нет телефонов" : row["phones"].c_str();
            std::cout << "Телефоны: " << phones << "\n";
            std::cout << "---\n";
        }
    }
};


int main() {
    try {
        pqxx::connection conn(
            "host=localhost "
            "port=5432 "
            "dbname=test_db "         
            "user=postgres "           
            "password=123456"          
        );

        std::cout << "Подключение к БД успешно!\n\n";

        ClientManager manager(conn);

        manager.createTables();

        std::cout << "\n--- Добавляем клиентов ---\n";
        manager.addClient("Иван", "Петров", "ivan@mail.ru");
        manager.addClient("Мария", "Иванова", "maria@mail.ru");
        manager.addClient("Петр", "Сидоров", "petr@mail.ru");

        std::cout << "\n--- Добавляем телефоны ---\n";
        manager.addPhone(1, "+7-912-345-67-89");
        manager.addPhone(1, "+7-912-345-67-90"); 
        manager.addPhone(2, "+7-922-111-22-33"); 

        manager.showAllClients();

        std::cout << "\n--- Изменяем данные клиента с ID=1 ---\n";
        manager.updateClient(1, "Иван", "Петрович", "ivan_new@mail.ru");

        std::cout << "\n--- Поиск по слову 'Иванов' ---\n";
        manager.findClient("Иванов");

        std::cout << "\n--- Поиск по номеру '+7-912' ---\n";
        manager.findClient("+7-912");

        std::cout << "\n--- Удаляем телефон с ID=2 ---\n";
        manager.deletePhone(2);

        manager.showAllClients();

        std::cout << "\n--- Удаляем клиента с ID=3 ---\n";
        manager.deleteClient(3);

        manager.showAllClients();

    }
    catch (const std::exception& e) {
        std::cout << "Ошибка подключения: " << e.what() << std::endl;
        std::cout << "\nПроверьте настройки подключения в main():\n";
        std::cout << "- dbname (имя базы данных)\n";
        std::cout << "- user (пользователь PostgreSQL)\n";
        std::cout << "- password (пароль)\n";
    }

    return 0;
}