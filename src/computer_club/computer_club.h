//
// Created by Deymos on 17/05/2024.
//

#ifndef COMPUTER_CLUB_H
#define COMPUTER_CLUB_H

#include <fstream>
#include <map>
#include <vector>

class ComputerClub {
private:
    struct Table {
        size_t revenue = 0;
        size_t busyTime = 0;
    };
    std::vector<Table> tables;

    size_t openTime;
    size_t closeTime;
    size_t pricePerHour;

    std::map<std::string /*client_name*/, size_t /*arrival time*/> clients;
public:
    ComputerClub() = default;
    ~ComputerClub() = default;

    void getConfigInfo(std::ifstream &inFile);
    void startSimulation(std::ifstream &inFile);

    size_t getOpenTime() const { return openTime; }
    size_t getCloseTime() const { return closeTime; }
    size_t getPricePerHour() const { return pricePerHour; }
    size_t getNumberOfTables() const { return tables.size(); }

    void printTablesInfo() const;
};

#endif //COMPUTER_CLUB_H
