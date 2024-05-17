#include <fstream>

#include "..\computer_club\computer_club.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        throw std::invalid_argument("Unexpected number of arguments");
    }
    std::ifstream inFile(argv[1]);
    if (!inFile) {
        throw std::invalid_argument("Unable to open file: " + std::string(argv[1]));
    }

    ComputerClub club{};
    club.getConfigInfo(inFile);
    club.startSimulation(inFile);

    inFile.close();
    return 0;
}
