#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <conio.h>
#include "RouteList.hpp"
using namespace std;

namespace menu {

const string INPUT_STR = "Выберите дейсвтие: ";
const string MENU_STR = "««« ГЛАВНОЕ МЕНЮ »»»\n1) Посмотреть список всех маршрутов\n2) Добавить маршрут\n3) Изменить маршрут\n4) Удалить маршрут\n5) Найти маршрут\n6) Отсортировать маршруты по номеру\n7) Сохранить БД\n0) Выход\n\n" + INPUT_STR;

const string ROUTE_CHANGE_MENU_STR = "1) Изменить номер\n2) Изменить начальный пункт\n3) Изменить конечный пункт\n4) Вернуться в главное меню\n\n" + INPUT_STR;

const string REPEAT_INPUT_STR = "Нажмите любую клавишу для повторного ввода . . . ";

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
			cout << "\nНекорректный ввод. Введите целое число в диапазоне [" << l << "; " << r << "]" << endl;
			cout << REPEAT_INPUT_STR;
			system("pause > nul");
		}
	}
}

// функция для ввода строки с ограничением максимальной длины
string inputString(const string& text, size_t maxLen = 100) {
	string input = "";

	while (true) {
		system("cls");
		cout << text;

		getline(cin, input);

		if (input.size() > 0 && input.size() <= maxLen) {
			return input;
		} else if (input.size() < 1) {
			cout << "\nНекорректный ввод: вы ввели пустую строку" << endl;
		} else {
			cout << "\nНекорректный ввод: максимальная длина строки - " + to_string(maxLen) + " символов" << endl;
		}
		cout << REPEAT_INPUT_STR;
		system("pause > nul");
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
	int n;
	while (true) {
		n = inputInt("Введите номер добавляемого маршрута: ", 1);
		if (!list.isRouteInList(n)) {
			break;
		} else {
			cout << "Ошибка: маршрут с таким номером уже существует" << endl;
			cout << REPEAT_INPUT_STR;
			system("pause > nul");
		}
	}
	string start = inputString("Введите начальный пункт маршрута: ");
	string end = inputString("Введите конечный пункт маршрута: ");

	list.append(Route(n, start, end));

	system("cls");
	cout << "Маршрут успешно добавлен:\n\n" << list.findByNum(n);
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

}