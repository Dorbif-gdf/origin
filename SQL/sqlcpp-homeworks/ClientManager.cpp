#include "ClientManager.h"
#include <iostream>

ClientManager::ClientManager(pqxx::connection& c) : conn(c) {}

bool ClientManager::clientExists(pqxx::work& tx, int clientId) {
    auto result = tx.exec(
        "SELECT id FROM clients WHERE id = " + std::to_string(clientId)
    );
    return !result.empty();
}

void ClientManager::createTables() {
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
}

void ClientManager::addClient(const std::string& firstName,
    const std::string& lastName,
    const std::string& email) {
    pqxx::work tx(conn);
    tx.exec(
        "INSERT INTO clients (first_name, last_name, email) "
        "VALUES (" +
        tx.quote(firstName) + ", " +
        tx.quote(lastName) + ", " +
        tx.quote(email) + ")"
    );
    tx.commit();
}

void ClientManager::addPhone(int clientId, const std::string& phoneNumber) {
    pqxx::work tx(conn);

    if (!clientExists(tx, clientId)) {
        throw std::runtime_error("Клиент с ID " + std::to_string(clientId) + " не найден");
    }

    tx.exec(
        "INSERT INTO phones (client_id, phone_number) "
        "VALUES (" + std::to_string(clientId) + ", " + tx.quote(phoneNumber) + ")"
    );
    tx.commit();
}

void ClientManager::updateClient(int clientId,
    const std::string& firstName,
    const std::string& lastName,
    const std::string& email) {
    pqxx::work tx(conn);

    if (!clientExists(tx, clientId)) {
        throw std::runtime_error("Клиент с ID " + std::to_string(clientId) + " не найден");
    }

    tx.exec(
        "UPDATE clients SET "
        "first_name = " + tx.quote(firstName) + ", "
        "last_name = " + tx.quote(lastName) + ", "
        "email = " + tx.quote(email) + " "
        "WHERE id = " + std::to_string(clientId)
    );
    tx.commit();
}

void ClientManager::deletePhone(int phoneId) {
    pqxx::work tx(conn);

    auto result = tx.exec("SELECT id FROM phones WHERE id = " + std::to_string(phoneId));
    if (result.empty()) {
        throw std::runtime_error("Телефон с ID " + std::to_string(phoneId) + " не найден");
    }

    tx.exec("DELETE FROM phones WHERE id = " + std::to_string(phoneId));
    tx.commit();
}

void ClientManager::deleteClient(int clientId) {
    pqxx::work tx(conn);

    if (!clientExists(tx, clientId)) {
        throw std::runtime_error("Клиент с ID " + std::to_string(clientId) + " не найден");
    }

    tx.exec("DELETE FROM clients WHERE id = " + std::to_string(clientId));
    tx.commit();
}

std::vector<ClientData> ClientManager::findClient(const std::string& searchText) {
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

    std::vector<ClientData> foundClients;

    for (const auto& row : result) {
        ClientData client;
        client.id = row["id"].as<int>();
        client.firstName = row["first_name"].c_str();
        client.lastName = row["last_name"].c_str();
        client.email = row["email"].c_str();

        // Разбиваем телефоны из строки в вектор
        std::string phonesStr = row["phones"].is_null() ? "" : row["phones"].c_str();
        if (!phonesStr.empty()) {
            size_t pos = 0;
            while ((pos = phonesStr.find(", ")) != std::string::npos) {
                client.phones.push_back(phonesStr.substr(0, pos));
                phonesStr.erase(0, pos + 2);
            }
            client.phones.push_back(phonesStr);
        }

        foundClients.push_back(client);
    }

    return foundClients;
}

std::vector<ClientData> ClientManager::getAllClients() {
    pqxx::work tx(conn);

    auto result = tx.exec(
        "SELECT c.id, c.first_name, c.last_name, c.email, "
        "       STRING_AGG(p.phone_number, ', ') as phones "
        "FROM clients c "
        "LEFT JOIN phones p ON c.id = p.client_id "
        "GROUP BY c.id "
        "ORDER BY c.id"
    );

    std::vector<ClientData> allClients;

    for (const auto& row : result) {
        ClientData client;
        client.id = row["id"].as<int>();
        client.firstName = row["first_name"].c_str();
        client.lastName = row["last_name"].c_str();
        client.email = row["email"].c_str();

        std::string phonesStr = row["phones"].is_null() ? "" : row["phones"].c_str();
        if (!phonesStr.empty()) {
            size_t pos = 0;
            while ((pos = phonesStr.find(", ")) != std::string::npos) {
                client.phones.push_back(phonesStr.substr(0, pos));
                phonesStr.erase(0, pos + 2);
            }
            client.phones.push_back(phonesStr);
        }

        allClients.push_back(client);
    }

    return allClients;
}

void ClientManager::clearAllData() {
    pqxx::work tx(conn);
    tx.exec("DELETE FROM phones");
    tx.exec("DELETE FROM clients");
    tx.commit();
}