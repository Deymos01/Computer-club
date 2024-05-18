#ifndef ACTIONS_H
#define ACTIONS_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "..\parser\parser.h"
#include "computer_club.h"

class Actions {
private:
    static int time_;
    static size_t actionID_;
    static std::string clientName_;
    static int tableNumber_;

    static void clientArrival(ComputerClub *club) {
        if (club->isClientInClub(clientName_)) {
            club->printClientAction(time_, 13, "YouShallNotPass");
            return;
        }
        if (club->getOpenTime() > time_ || club->getCloseTime() < time_) {
            club->printClientAction(time_, 13, "NotOpenYet");
            return;
        }
        club->setClientTable(clientName_, -1);
    }

    static void clientTookTable(ComputerClub *club) {
        if (!club->isClientInClub(clientName_)) {
            club->printClientAction(time_, 13, "ClientUnknown");
            return;
        }
        if (club->getTableInfo(tableNumber_).isBusy) {
            club->printClientAction(time_, 13, "PlaceIsBusy");
            return;
        }
        if (club->isClientPlaying(clientName_)) {
            Actions::closeTable(club, club->getClientTableNumber(clientName_));
        }
        club->getTableInfo(tableNumber_).isBusy = true;
        club->getTableInfo(tableNumber_).clientArrivalTime = time_;
        club->setClientTable(clientName_, tableNumber_);
    }

    static void clientWait(ComputerClub *club) {
        if (club->isThereFreeTable()) {
            club->printClientAction(time_, 13, "ICanWaitNoLonger!");
            return;
        }
        if (club->getClientsQueueSize() == club->getNumberOfTables()) {
            club->printClientAction(time_, 11, clientName_);
            Actions::clientLeft(club);
            return;
        }
        club->addClientToQueue(clientName_);
    }

    static void clientLeft(ComputerClub *club) {
        if (!club->isClientInClub(clientName_)) {
            club->printClientAction(time_, 13, "ClientUnknown");
            return;
        }

        tableNumber_ = club->getClientTableNumber(clientName_);
        club->removeClient(clientName_);
        if (0 <= tableNumber_ && tableNumber_ < club->getNumberOfTables()) {
            Actions::closeTable(club, tableNumber_);

            if (club->getClientsQueueSize() > 0 && time_ < club->getCloseTime()) {
                clientName_ = club->getClientFromQueue();
                club->printClientAction(time_, 12, clientName_ + ' ' + std::to_string(tableNumber_ + 1));
                Actions::clientTookTable(club);
            }
        }
    }

    static void kickOutClient(ComputerClub *club) {
        if (!club->isClientInClub(clientName_)) {
            club->printClientAction(time_, 13, "ClientUnknown");
            return;
        }
        club->printClientAction(time_, 11, clientName_);
        Actions::clientLeft(club);
    }

    static void closeTable(ComputerClub *club, int tableNumber) {
        club->getTableInfo(tableNumber).revenue += (time_ - club->getTableInfo(tableNumber).clientArrivalTime + 59) / 60 * club->getPricePerHour();
        club->getTableInfo(tableNumber).busyTime += time_ - club->getTableInfo(tableNumber).clientArrivalTime;
        club->getTableInfo(tableNumber).isBusy = false;
    }

public:
    static void processAction(ComputerClub *club, const std::string &action) {
        std::stringstream ss(action);
        std::string lexeme;
        ss >> lexeme;
        time_ = Parser::getTimeInMinutes(lexeme);
        if (time_ == -1 || ss.eof()) {
            std::cout << action << std::endl;
            throw std::invalid_argument("Expected time_, actionID_ and client name");
        }
        ss >> lexeme;
        if (!Parser::isIntPosNumber(lexeme) || ss.eof()) {
            std::cout << action << std::endl;
            throw std::invalid_argument("Expected positive integer actionID_ and client name");
        }
        actionID_ = std::stoi(lexeme);
        ss >> lexeme;
        if (!Parser::isCorrectName(lexeme)) {
            std::cout << action << std::endl;
            throw std::invalid_argument("Expected valid client name");
        }
        clientName_ = lexeme;
        tableNumber_ = 0;
        if (actionID_ == 2) {
            ss >> lexeme;
            if (!Parser::isIntPosNumber(lexeme)) {
                std::cout << action << std::endl;
                throw std::invalid_argument("Expected table number");
            }
            tableNumber_ = std::stoi(lexeme) - 1;
            if (tableNumber_ < 0 || tableNumber_ >= club->getNumberOfTables()) {
                std::cout << action << std::endl;
                throw std::invalid_argument("Invalid table number");
            }
        }
        if (!ss.eof()) {
            std::cout << action << std::endl;
            throw std::invalid_argument("Unexpected data");
        }

        switch (actionID_) {
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
            case 11:
                kickOutClient(club);
                break;
            default:
                std::cout << action << std::endl;
                throw std::invalid_argument("Invalid actionID_");
        }
    }
};

int Actions::time_ = 0;
size_t Actions::actionID_ = 0;
std::string Actions::clientName_;
int Actions::tableNumber_ = -1;

#endif //ACTIONS_H
