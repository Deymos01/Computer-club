#ifndef PARSER_H
#define PARSER_H

#include <algorithm>

class Parser {
private:

public:
    Parser() = default;

    ~Parser() = default;

    static bool isIntPosNumber(const std::string &str) {
        if (str.empty()) { return false; }
        if (std::ranges::any_of(str.begin(), str.end(), [](char ch) -> bool { return !isdigit(ch); })) {
            return false;
        }
        return true;
    }

    static int getTimeInMinutes(const std::string &str) {
        if (str.length() != 5) { return -1; }
        if (str[2] != ':') { return -1; }
        if (!isdigit(str[0]) || !isdigit(str[1]) || !isdigit(str[3]) || !isdigit(str[4])) { return -1; }
        int hours = (str[0] - '0') * 10 + (str[1] - '0');
        int minutes = (str[3] - '0') * 10 + (str[4] - '0');
        if (hours > 23 || minutes > 59) { return -1; }
        return hours * 60 + minutes;
    }

    static bool isCorrectName(const std::string &str) {
        if (str.empty()) { return false; }
        if (std::ranges::any_of(str.begin(), str.end(), [](char ch) -> bool { return !isalpha(ch) && !isdigit(ch) && ch != '_'; })) {
            return false;
        }
        return true;
    }
};

#endif //PARSER_H
