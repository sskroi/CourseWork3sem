#include <iostream>
#include <limits>
#include <iomanip>
#include <string>
#include <algorithm>

#include "menu_text.h"
#include "menu.h"
#include "RouteList.h"

using namespace std;

namespace menu {

// фунуция для ввода целого числа в диапазоне [l;r]
int inputInt(std::string prompt, int l, int r) {
    int inputNum;
    char ch;
    std::cout << "\x1B[2J\x1B[H" << prompt;
    std::cin >> inputNum;

    while (cin.fail() || inputNum < l || inputNum > r) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n\x1B[38;5;167mНекорректный ввод:\x1B[0m введите целое число в диапазоне [" << l << "; " << r << "]\n";
        std::cout << "Нажмите \x1B[38;5;216mEnter\x1B[0m для повторного ввода . . . ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "\x1B[2J\x1B[H" << prompt;
        std::cin >> inputNum;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return inputNum;
}

// функция для ввода строки с ограничением максимальной длины
string inputString(const string& prompt, size_t maxLen) {
    string input = "";

    while (true) {
        clearConsole();
        cout << prompt;

        getline(cin, input);
        stripString(input);

        if (input.size() > 0 && countUTF8Chars(input) <= maxLen) {
            return input;
        } else {
            if (countUTF8Chars(input) < 1) {
                cout << EMPTY_STRING_STR;
            } else {
                cout << "\n" << INCORRECT_INPUT_STR;
                cout << "максимальная длина строки " << maxLen << " символов\n";
            }
            cout << REPEAT_INPUT_STR;
            waitEnter();
        }
    }
}

void findRoute(RouteList& list) {
    int userChoice;

    while (true) {
        userChoice = inputInt(ROUTE_FIND_MENU_STR, 0, ROUTE_FIND_MENU_ITEMS_COUNT_STR);

        RouteList result;

        if (userChoice == 1) {
            int routeNumber = inputInt(FINDING_NUM_STR, 1);

            try {
                result.append(list.findByNum(routeNumber));
            } catch (RouteList::RouteNotExistErr& ex) {}

        } else if (userChoice == 2) {
            string routeStart = inputString(FINDING_START_STR);

            result = list.findByStart(routeStart);

        } else if (userChoice == 3) {
            string routeEnd = inputString(FINDING_END_STR);

            result = list.findByEnd(routeEnd);

        } else if (userChoice == 0) {
            return;
        }

        cout << FINDING_RESULT_STR;
        if (result.isEmpty()) {
            cout << FINDING_NO_RESULT_STR;
        } else {
            result.print();
        }

        backToMenu();
    }
}

void addRoute(RouteList& list) {
    int newRouteNum;

    while (true) {
        newRouteNum = inputInt(ADDING_ROUTE_NUM_STR, 1);

        if (!list.isRouteInList(newRouteNum)) {
            break;
        } else {
            cout << ADDING_ALREADY_EXIST_STR;
            cout << REPEAT_INPUT_STR;
            waitEnter();
        }
    }
    string start = inputString(ADDING_START_STR);
    string end = inputString(ADDING_END_STR);

    list.append(Route(newRouteNum, start, end));

    clearConsole();
    cout << ADDING_SUCCESS_STR << list.findByNum(newRouteNum);
    backToMenu();
}

void deleteRoute(RouteList& list) {
    int numOfRoute = inputInt(DELETING_NUM_STR, 1);

    if (!list.isRouteInList(numOfRoute)) {
        cout << DELETING_NOT_EXIST_STR;
    } else {
        list.deleteByNum(numOfRoute);
        cout << DELETING_SUCCESS;
    }

    backToMenu();
}

void printRouteList(RouteList& list) {
    clearConsole();
    if (list.isEmpty()) {
        cout << "Список маршрутов пуст" << endl;
    } else {
        int maxNumLen = list.maxNumLen();

        if (maxNumLen > 5) {
            maxNumLen -= 5;
        } else {
            maxNumLen = 0;
        }

        cout << setw(10 + maxNumLen) << "Номер" << " | " << "Откуда -> Куда" << endl;
        list.print(5 + maxNumLen);
    }
    backToMenu();
}

void changeRoute(RouteList& list) {
    int routeNum = inputInt(CHANGE_INPUT_NUM_STR, 1);

    if (!list.isRouteInList(routeNum)) {
        cout << CHANGE_NOT_EXIST_STR;
        backToMenu();

    } else {
        int userChoice;

        while (true) {
            userChoice = inputInt(CHANGE_HEADER_STR + list.findByNum(routeNum).str()
                + CHANGE_MENU_STR, 0, CHANGE_MENU_ITEMS_COUNT);

            if (userChoice == 1) {
                int newRouteNum = inputInt(CHANGE_NEW_NUM_STR, 1);

                if (list.isRouteInList(newRouteNum)) {
                    cout << CHANGE_ALREADY_EXIST_STR;

                } else {
                    list.changeRouteNumber(routeNum, newRouteNum);

                    cout << CHANGE_SUCCESS;
                    cout << list.findByNum(newRouteNum);

                    routeNum = newRouteNum;

                }
            } else if (userChoice == 2) {
                string newStart = inputString(CHANGE_INPUT_START_STR);

                list.changeRouteStart(routeNum, newStart);

                cout << CHANGE_SUCCESS;
                cout << list.findByNum(routeNum);

            } else if (userChoice == 3) {
                string newEnd = inputString(CHANGE_INPUT_END_STR);

                list.changeRouteEnd(routeNum, newEnd);

                cout << CHANGE_SUCCESS;
                cout << list.findByNum(routeNum);


            } else if (userChoice == 0) {
                return;
            }

            backToMenu();
        }
    }
}

void sortRouteList(RouteList& list) {
    clearConsole();
    cout << SORT_PROCESSING;
    list.sort();
}

void stripString(string& s) {
    // Удаление пробельных символов слева
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
        }));

    // Удаление пробельных символов справа
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

size_t countUTF8Chars(const std::string& str) {
    size_t count = 0;
    for (size_t i = 0; i < str.length(); ) {
        unsigned char ch = static_cast<unsigned char>(str[i]);

        if (ch <= 0x7F) {
            ++count;
            ++i;
        } else if (ch <= 0xDF) {
            count += 1;
            i += 2;
        } else if (ch <= 0xEF) {
            count += 1;
            i += 3;
        } else {
            count += 1;
            i += 4;
        }
    }
    return count;
}

int mainMenuChoice() {
    clearConsole();
    int choice = inputInt(MAIN_MENU_STR, 0, MAIN_MENU_ITEMS_COUNT);
    return choice;
}

void backToMenu() {
    cout << endl << BACK_TO_MENU_STR;
    waitEnter();
}

void waitEnter() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void clearConsole() {
    std::cout << "\x1B[2J\x1B[H";
}

}