//
// Created by Deymos on 17/05/2024.
//

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

    Actions actions;
    std::string line;
    while (inFile.peek() != EOF) {
        std::getline(inFile, line);
        std::cout << line << '\n';
        actions.processAction(this, line);
    }

    std::cout << std::setfill('0') << std::setw(2) << closeTime / 60 << ':' << std::setw(2) << closeTime % 60 << '\n';
    printTablesInfo();
}

void ComputerClub::printTablesInfo() const {
    for (size_t i = 0; i < tables.size(); ++i) {
        std::cout << i + 1 << ' ' << tables[i].revenue << ' ' <<
                  std::setfill('0') << std::setw(2) << tables[i].busyTime / 60 << ':' <<
                  std::setw(2) << tables[i].busyTime % 60 << '\n';
    }
}