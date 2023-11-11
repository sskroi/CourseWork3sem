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
string inputString(const string& text, size_t maxLen = 100) {
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
	int choice = inputInt(MENU_STR, 0, 7);
	return choice;
}

int changeMenuChoice(int numOfRoute, RouteList& list) {
	system("cls");
	string header = "Изменение - " + list.findByNum(numOfRoute).str();
	int choice = inputInt(header + ROUTE_CHANGE_MENU_STR, 1, 4);
	return choice;
}

void backToMenu() {
	cout << endl << "Нажмите любую клавишу чтобы вернуться в меню . . . ";
	system("pause > nul");
}

void addInRouteListFromKeyBoard(RouteList& list) {
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

void findRouteByNumberFromKeyboard(RouteList& list) {
	int n = inputInt("Введите номер маршрута, который хотите найти", 1);
	list.findByNum(n);
	backToMenu();
}

void deleteByNumberFromKeyboard(RouteList& list) {
	int n = inputInt("Введите номер маршрута, который хотите удалить", 1);
	list.deleteByNum(n);
	backToMenu();
}

void printRouteList(RouteList& list) {
	system("cls");
	if (list.isEmpty()) { cout << "Список маршрутов пуст" << endl; } else {
		cout << "Список всех маршрутов:" << endl;
		list.print();
	}
	backToMenu();
}

void changeRoute(RouteList& list) {
	int numOfRoute = inputInt("Введите номер маршрута, который хотите изменить: ", 1);

	if (!list.isRouteInList(numOfRoute)) {
		cout << "Маршрут с таким номером не существует" << endl;
	} else {
		int choice;
		while (true) {
			choice = changeMenuChoice(numOfRoute, list);

			if (choice == 1) {
				int newNumOfRoute = inputInt("Введите новый номер маршрута: ");

				if (list.isRouteInList(newNumOfRoute)) {
					cout << "Маршрут с таким номером уже существует" << endl;
					backToMenu();
				} else {
					list.changeNumber(numOfRoute, newNumOfRoute);

					cout << "Номер маршрута изменён с " << numOfRoute << " на " << newNumOfRoute << endl;
					cout << list.findByNum(newNumOfRoute);

					numOfRoute = newNumOfRoute;

					backToMenu();
				}
			} else if (choice == 2) {
				string new_start = inputString("Введите новый начальный пункт: ");

				list.changeStart(numOfRoute, new_start);

				cout << "Изменения внесены:" << endl;
				cout << list.findByNum(numOfRoute);

				backToMenu();
			} else if (choice == 3) {
				string new_end = inputString("Введите новый конечный пункт: ");

				list.changeEnd(numOfRoute, new_end);

				cout << "Изменения внесены:" << endl;
				cout << list.findByNum(numOfRoute);

				backToMenu();
			} else if (choice == 4) {
				return;
			}
		}
	}
	backToMenu();
}

void sortRouteList(RouteList& list) {
	system("cls");
	if (list.isEmpty()) { cout << "Список маршрутов пуст" << endl; } else {
		if (list.size() > 5000) {
			cout << "Объем данных слишком большой. Сортировка может занять длительное время." << endl;
			cout << "НЕ рекомендуется делать сортировку с таким объёмом данных." << endl;
			cout << "Если вы желаете продолжить нажмите 0\n\nЛюбая другая клавиша отменит действие . . . ";
			char ch = _getch();
			if (ch != '0') { return; }
			system("cls");
			cout << "Начат процесс сортировки. Ожидайте." << endl;
		}
		list.sort();
		cout << "Список маршрутов отсортирован:" << endl;
		list.print();
	}
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