#pragma once

#include <pqxx/pqxx>
#include <vector>
#include <string>


struct ClientData {
    int id;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::vector<std::string> phones;
};


class ClientManager {
private:
    pqxx::connection& conn;

    bool clientExists(pqxx::work& tx, int clientId);

public:
    ClientManager(pqxx::connection& c);

    void createTables();

    void addClient(const std::string& firstName,
        const std::string& lastName,
        const std::string& email);

    void addPhone(int clientId, const std::string& phoneNumber);

    void updateClient(int clientId,
        const std::string& firstName,
        const std::string& lastName,
        const std::string& email);

    void deletePhone(int phoneId);

    void deleteClient(int clientId);

    std::vector<ClientData> findClient(const std::string& searchText);

    std::vector<ClientData> getAllClients();
    void clearAllData();
};