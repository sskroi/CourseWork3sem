#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <conio.h>
#include "RouteList.hpp"
#include "menu_text.hpp"
using namespace std;

namespace menu {

// фунуция для ввода целого числа в диапазоне [l;r]
int inputInt(const string& text, int l = INT_MIN, int r = INT_MAX) {
	int number;
	string input;

	while (true) {
		system("cls");
		cout << text;

		getline(cin, input);
		stringstream stream(input);

		if ((stream >> number && stream.eof()) && (number >= l && number <= r)) {
			return number;
		} else {
			cout << incorrectIntInputStr(l, r);
			cout << REPEAT_INPUT_STR;
			system("pause > nul");
		}
	}
}

size_t countUTF8Chars(const std::string& str);
// функция для ввода строки с ограничением максимальной длины
string inputString(const string& text, size_t maxLen = 100ULL) {
	string input = "";

	while (true) {
		system("cls");
		cout << text;

		getline(cin, input);

		if (input.size() > 0 && countUTF8Chars(input) <= maxLen) {
			return input;
		} else {
			if (countUTF8Chars(input) < 1) {
				cout << EMPTY_STRING_STR;
			} else {
				cout << incorrectInputStringLenStr(maxLen);
			}
			cout << REPEAT_INPUT_STR;
			system("pause > nul");
		}
	}
}

int mainMenuChoice() {
	system("cls");
	int choice = inputInt(MAIN_MENU_STR, 0, MAIN_MENU_ITEMS_COUNT);
	return choice;
}

void backToMenu() {
	cout << endl << "Нажмите любую клавишу чтобы вернуться в меню . . . ";
	system("pause > nul");
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
			} catch (RouteNotExistErr& ex) {}

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
			system("pause > nul");
		}
	}
	string start = inputString(ADDING_START_STR);
	string end = inputString(ADDING_END_STR);

	list.append(Route(newRouteNum, start, end));

	system("cls");
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
	system("cls");
	if (list.isEmpty()) {
		cout << "Список маршрутов пуст" << endl;
	} else {
		cout << "Список всех маршрутов:\n";
		list.print();
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
	system("cls");

	backToMenu();
}

size_t countUTF8Chars(const std::string& str) {
	size_t count = 0;
	for (size_t i = 0; i < str.length(); ) {
		unsigned char ch = static_cast<unsigned char>(str[i]);

		if (ch <= 0x7F) {
			// single byte character
			++count;
			++i;
		} else if (ch <= 0xDF) {
			// two byte character
			count += 1;
			i += 2;
		} else if (ch <= 0xEF) {
			// three byte character
			count += 1;
			i += 3;
		} else {
			// four byte character
			count += 1;
			i += 4;
		}
	}
	return count;
}

}