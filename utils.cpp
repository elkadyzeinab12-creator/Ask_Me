//
// Created by GTX TOP on 6/24/2026.
//

#include "utils.h"
#include <bits/stdc++.h>
using namespace std;
#include "utils.h"
#include "colors.h"
#include "AskMeManager.h"


int getIntInput(const std::string &prompt) {
    int value;
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        stringstream ss(line);
        char extra;

        if (ss >> value && !(ss >> extra)) {
            return value;
        }
        cout << red << "Invalid input, please try Enter a number\n" << RESET;
    }
}

double getDoubleInput(const std::string &prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        cout << red << "Invalid input, please try Enter a double number\n" << RESET;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string getStringInput(const std::string &prompt) {
    string value;
    while (true) {
        cout << prompt;
        if (std::getline(std::cin >> std::ws, value)) {
            return value;
        }
        return "";
    }
}

char getCharInput(const std::string &prompt) {
    char value;
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        stringstream ss(line);
        char extra;

        if (ss >> value && !(ss >> extra)) {
            return value;
        }
        cout << red << "Invalid input, please try Enter a character \n" << RESET;
    }
}

string getUsername(const std::string &prompt) {
    string username;
    while (true) {
        cout << prompt;
        getline(cin, username);
        for (auto &c : username) {
            if (c == ' ') {
                cout << red << "Invalid username, please try again  \n" << RESET;
            }
        }

        if (!username.empty()) {
            return username;
        }
    }
}

bool getAQ(const std::string &prompt) {
    int AQ;
    while (true) {
        cout << prompt;
        cin >> AQ;
        if (AQ == 0 ) {
            return false;
        }
        if (AQ == 1) {
            return true;
        }
        cout << red << "Invalid input, please try again  \n" << RESET;
    }
}