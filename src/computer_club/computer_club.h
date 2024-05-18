#ifndef COMPUTER_CLUB_H
#define COMPUTER_CLUB_H

#include <fstream>
#include <map>
#include <vector>
#include <queue>

class ComputerClub {
private:
    struct Table {
        size_t revenue = 0;
        size_t busyTime = 0;
        bool isBusy = false;
        size_t clientArrivalTime = 0;
    };
    std::vector<Table> tables;

    int openTime;
    int closeTime;
    size_t pricePerHour;

    std::map<std::string /*client_name*/, int /*table number*/> clients;
    std::queue<std::string> clientsQueue;
public:
    ComputerClub() : openTime(0), closeTime(0), pricePerHour(0) {};

    void getConfigInfo(std::ifstream &inFile);
    void startSimulation(std::ifstream &inFile);

    bool isClientInClub(const std::string &clientName) const;
    bool isThereFreeTable() const;
    bool isClientPlaying(const std::string &clientName);
    void setClientTable(const std::string &clientName, int tableNumber);
    void addClientToQueue(const std::string &clientName);
    void removeClient(const std::string &clientName);

    int getOpenTime() const { return openTime; }
    int getCloseTime() const { return closeTime; }
    size_t getPricePerHour() const { return pricePerHour; }
    size_t getNumberOfTables() const { return tables.size(); }
    size_t getClientsQueueSize() const { return clientsQueue.size(); }
    std::string getClientFromQueue() { std::string client = clientsQueue.front(); clientsQueue.pop(); return client; }

    Table& getTableInfo(const size_t &tableNumber) { return tables[tableNumber]; }
    int getClientTableNumber(const std::string &clientName) const { return clients.at(clientName); }

    void printTablesInfo() const;
    void printClientAction(int time, int ID, const std::string& body) const;

    void kickOutAllClients();
};

#endif //COMPUTER_CLUB_H
