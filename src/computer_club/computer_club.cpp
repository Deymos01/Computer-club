#include <fstream>
#include <iostream>
#include <iomanip>
#include "computer_club.h"
#include "..\parser\parser.h"
#include "..\computer_club\actions.h"

void ComputerClub::getConfigInfo(std::ifstream &inFile) {
    std::string line;
    std::getline(inFile, line);
    if (!Parser::isIntPosNumber(line)) {
        std::cout << line << std::endl;
        throw std::invalid_argument("Expected positive integer number");
    }
    size_t numberOfTables = std::stoi(line);
    std::getline(inFile, line);
    if (std::count(line.begin(), line.end(), ' ') != 1) {
        std::cout << line << std::endl;
        throw std::invalid_argument("Expected opening hours");
    }
    size_t spacePos = line.find(' ');
    int openT = Parser::getTimeInMinutes(line.substr(0, spacePos));
    int closeT = Parser::getTimeInMinutes(line.substr(spacePos + 1));
    if (openT < 0 || closeT < 0 || openT >= closeT) {
        std::cout << line << std::endl;
        throw std::invalid_argument("Invalid opening hours");
    }
    openTime = openT;
    closeTime = closeT;
    std::getline(inFile, line);
    if (!Parser::isIntPosNumber(line)) {
        std::cout << line << std::endl;
        throw std::invalid_argument("Expected positive integer number");
    }
    pricePerHour = std::stoi(line);
    tables.resize(numberOfTables);
}

void ComputerClub::startSimulation(std::ifstream &inFile) {
    std::cout << std::setfill('0') << std::setw(2) << openTime / 60 << ':' << std::setw(2) << openTime % 60 << '\n';

    std::string line;
    while (inFile.peek() != EOF) {
        std::getline(inFile, line);
        std::cout << line << '\n';
        Actions::processAction(this, line);
    }

    kickOutAllClients();
    std::cout << std::setfill('0') << std::setw(2) << closeTime / 60 << ':' << std::setw(2) << closeTime % 60 << '\n';
    printTablesInfo();
}

bool ComputerClub::isClientInClub(const std::string &clientName) const {
    return clients.find(clientName) != clients.end();
}

bool ComputerClub::isThereFreeTable() const {
    for (const auto &table : tables) {
        if (!table.isBusy) {
            return true;
        }
    }
    return false;
}

bool ComputerClub::isClientPlaying(const std::string &clientName) {
    return clients[clientName] != -1;
}

void ComputerClub::setClientTable(const std::string &clientName, int tableNumber) {
    clients[clientName] = tableNumber;
}

void ComputerClub::addClientToQueue(const std::string &clientName) {
    clientsQueue.push(clientName);
}

void ComputerClub::removeClient(const std::string &clientName) {
    clients.erase(clientName);
}

void ComputerClub::kickOutAllClients() {
    std::string time = {
            (char)(closeTime / 60 / 10 + '0'),
            (char)(closeTime / 60 % 10 + '0'),
            ':',
            (char)(closeTime % 60 / 10 + '0'),
            (char)(closeTime % 60 % 10 + '0'),
    };
    std::string action = time + " 11 ";

    while (!clients.empty()) {
        auto& client = *clients.begin();
        Actions::processAction(this, action + client.first);
    }
}

void ComputerClub::printTablesInfo() const {
    for (size_t i = 0; i < tables.size(); ++i) {
        std::cout << i + 1 << ' ' << tables[i].revenue << ' ' <<
                  std::setfill('0') << std::setw(2) << tables[i].busyTime / 60 << ':' <<
                  std::setw(2) << tables[i].busyTime % 60 << '\n';
    }
}

void ComputerClub::printClientAction(int time, int ID, const std::string& body) const {
    std::cout << std::setfill('0') << std::setw(2) <<
              time / 60 << ':' << std::setw(2) << time % 60 << ' ' << ID << ' ' << body << '\n';
}