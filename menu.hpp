#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#define byte win_byte_override // solving byte ambiguity
#include <Windows.h>
#include <conio.h>
#include "RouteList.hpp"
using namespace std;


const string INPUT_STR = "�������� ��������: ";
const string MENU_STR = "��� ������� ���� ���\n1) ���������� ������ ���� ���������\n2) �������� �������\n3) �������� �������\n4) ������� �������\n5) ����� �������\n6) ������������� �������� �� ������\n7) ��������� ��\n0) �����\n\n" + INPUT_STR;

const string ROUTE_CHANGE_MENU_STR = "1) �������� �����\n2) �������� ��������� �����\n3) �������� �������� �����\n4) ��������� � ������� ����\n\n" + INPUT_STR;

const string REPEAT_INPUT_STR = "������� ����� ������� ��� ���������� ����� . . . ";


int inputIntInRange(const string& text, int l = INT_MIN, int r = INT_MAX) { // ������� ��� ����� ������ ����� � ��������� [l;r]
	int number;
	string input;
	while (true) {
		system("cls");
		cout << text;
		getline(cin, input);
		stringstream stream(input);
		if ((stream >> number && stream.eof()) && (number >= l && number <= r)) { return number; } else {
			cout << "\n������������ ����. ������� ����� ����� � ��������� [" << l << "; " << r << "]" << endl;
			cout << REPEAT_INPUT_STR;
			system("pause > nul");
			cout << "\x1B[2A\r\x1B[0J";
		}
	}
}

int mainMenuChoice() {
	system("cls");
	int choice = inputIntInRange(MENU_STR, 0, 7);
	return choice;
}

string inputStr(const string& text, size_t maxLen = 100) {
	string s = "";
	while (true) {
		system("cls");
		cout << text;
		getline(cin, s);
		if (s.size() > 0 && s.size() <= maxLen) { return s; } else if (s.size() < 1) {
			cout << "������������ ����: �� ����� ������ ������\n\n" << REPEAT_INPUT_STR;
			system("pause > nul");
		} else {
			cout << "������������ ����: ������� ������� ������. ������������ ����� - " + to_string(maxLen) + " ��������\n\n"
				<< REPEAT_INPUT_STR;
			system("pause > nul");
		}
	}
	return s;
}

int changeMenuChoice(int numOfRoute, RouteList& list) {
	system("cls");
	string header = "��������� - " + list.findByNum(numOfRoute);
	cout << ROUTE_CHANGE_MENU_STR;
	int choice = inputIntInRange(header + ROUTE_CHANGE_MENU_STR, 1, 4);
	return choice;
}

void backToMenu() {
	cout << endl << "������� ����� ������� ����� ��������� � ���� . . . ";
	system("pause > nul");
}

void addInRouteListFromKeyBoard(RouteList& list) {
	int n;
	while (true) {
		n = inputIntInRange("������� ����� ������������ ��������", 1);
		if (!list.isRouteInList(n)) { break; } else {
			cout << "������: ������� � ����� ������� ��� ����������" << endl;
			cout << "������� ����� ������� ��� ���������� ����� ������ �������� . . . ";
			system("pause > nul");
		}
	}
	string start = inputStr("������� ��������� ����� ��������");
	string end = inputStr("������� �������� ����� ��������");
	list.append(Route(n, start, end));
	system("cls");
	cout << "������� ������� ��������: " << endl;
	list.findByNum(n);
	backToMenu();
}

void findRouteByNumberFromKeyboard(RouteList& list) {
	int n = inputIntInRange("������� ����� ��������, ������� ������ �����", 1);
	list.findByNum(n);
	backToMenu();
}

void deleteByNumberFromKeyboard(RouteList& list) {
	int n = inputIntInRange("������� ����� ��������, ������� ������ �������", 1);
	list.deleteByNum(n);
	backToMenu();
}

void printRouteList(RouteList& list) {
	system("cls");
	if (list.isEmpty()) { cout << "������ ��������� ����" << endl; } else {
		cout << "������ ���� ���������:" << endl;
		list.print();
	}
	backToMenu();
}

void changeRoute(RouteList& list) {
	int numOfRoute = inputIntInRange("������� ����� ��������, ������� ������ ��������: ", 1);

	if (!list.isRouteInList(numOfRoute)) {
		cout << "������� � ����� ������� �� ����������" << endl;
	} else {
		int choice;
		while (true) {
			choice = changeMenuChoice(numOfRoute, list);

			if (choice == 1) {
				int newNumOfRoute = inputIntInRange("������� ����� ����� ��������: ");

				if (list.isRouteInList(newNumOfRoute)) {
					cout << "������� � ����� ������� ��� ����������" << endl;
					backToMenu();
				} else {
					list.changeNumber(numOfRoute, newNumOfRoute);

					cout << "����� �������� ������ � " << numOfRoute << " �� " << newNumOfRoute << endl;
					cout << list.findByNum(newNumOfRoute);

					numOfRoute = newNumOfRoute;

					backToMenu();
				}
			} else if (choice == 2) {
				string new_start = inputStr("������� ����� ��������� �����: ");

				list.changeStart(numOfRoute, new_start);

				cout << "��������� �������:" << endl;
				cout << list.findByNum(numOfRoute);

				backToMenu();
			} else if (choice == 3) {
				string new_end = inputStr("������� ����� �������� �����: ");

				list.changeEnd(numOfRoute, new_end);

				cout << "��������� �������:" << endl;
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
	if (list.isEmpty()) { cout << "������ ��������� ����" << endl; } else {
		if (list.getLen() > 5000) {
			cout << "����� ������ ������� �������. ���������� ����� ������ ���������� �����." << endl;
			cout << "�� ������������� ������ ���������� � ����� ������� ������." << endl;
			cout << "���� �� ������� ���������� ������� 0\n\n����� ������ ������� ������� �������� . . . ";
			char ch = _getch();
			if (ch != '0') { return; }
			system("cls");
			cout << "����� ������� ����������. ��������." << endl;
		}
		list.sort();
		cout << "������ ��������� ������������:" << endl;
		list.print();
	}
	backToMenu();
}
