//
// Created by Deymos on 18/05/2024.
//

#ifndef ACTIONS_H
#define ACTIONS_H

#include <fstream>
#include <sstream>
#include <iostream>

#include "..\parser\parser.h"
#include "computer_club.h"

class Actions {
private:
    size_t time;
    size_t id;
    std::string clientName;
    size_t tableNumber;

    void clientArrival(const ComputerClub *club) {

    }

    void clientTookTable(const ComputerClub *club) {

    }

    void clientWait(const ComputerClub *club) {

    }

    void clientLeft(const ComputerClub *club) {

    }

public:
    void processAction(const ComputerClub *club, const std::string &action) {
        std::stringstream ss(action);
        std::string lexeme;
        ss >> lexeme;
        time = Parser::getTimeInMinutes(lexeme);
        if (time == -1 || ss.eof()) {
            std::cout << action << std::endl;
            throw std::invalid_argument("Expected time, id and client name");
        }
        ss >> lexeme;
        if (!Parser::isIntPosNumber(lexeme) || ss.eof()) {
            std::cout << action << std::endl;
            throw std::invalid_argument("Expected positive integer id and client name");
        }
        id = std::stoi(lexeme);
        ss >> lexeme;
        if (!Parser::isCorrectName(lexeme)) {
            std::cout << action << std::endl;
            throw std::invalid_argument("Expected client name");
        }
        clientName = lexeme;
        tableNumber = 0;
        if (id == 2) {
            ss >> lexeme;
            if (!Parser::isIntPosNumber(lexeme)) {
                std::cout << action << std::endl;
                throw std::invalid_argument("Expected table number");
            }
            tableNumber = std::stoi(lexeme);
            if (tableNumber == 0 || tableNumber > club->getNumberOfTables()) {
                std::cout << action << std::endl;
                throw std::invalid_argument("Invalid table number");
            }
        }
        if (!ss.eof()) {
            std::cout << action << std::endl;
            throw std::invalid_argument("Unexpected data");
        }

        switch (id) {
            case 1:
                clientArrival(club);
                break;
            case 2:
                clientTookTable(club);
                break;
            case 3:
                clientWait(club);
                break;
            case 4:
                clientLeft(club);
                break;
            default:
                std::cout << action << std::endl;
                throw std::invalid_argument("Invalid id");
        }
    }
};

#endif //ACTIONS_H
