#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <format>
using namespace std;

class Route {
private:
	int number;
	string start;
	string end;
	Route* next;
	Route* prev;

public:
	Route(int number, const string& a, const string& b) :
		number(number), start(a), end(b), next(nullptr), prev(nullptr) {
	}

	Route(const Route& r) :
		number(r.number), start(r.start), end(r.end), next(r.next), prev(r.prev) {
	}

	string str() {
		return format("Номер маршрута: {:<3} | {} -> {}\n", this->number, this->start, this->end);
	}

	friend RouteList;
};


class RouteList {
private:
	Route* head;
	size_t len;

public:
	RouteList() : head(nullptr), len(0) {}

	void append(const Route& route) {
		Route* newNode = new Route(route);
		this->len++;

		if (this->head == nullptr) {
			this->head = newNode;
		} else {
			Route* cur = this->head;

			while (cur->next != nullptr) {
				cur = cur->next;
			}

			cur->next = newNode;
			newNode->prev = cur;
		}
	}

	void deleteByNum(int numOfRoute) {
		if (!this->isRouteInList(numOfRoute) || this->head == nullptr) {
			throw range_error("the route with this number is not in the list");
		} else {
			this->len--;
			Route* cur = this->head;

			while (cur->number != numOfRoute) {
				cur = cur->next;
			}
			Route* toDel = cur;

			if (toDel == this->head) {
				if (this->head->next == nullptr) {
					this->head = nullptr;
				} else {
					this->head = this->head->next;
					this->head->prev = nullptr;
				}
			} else if (toDel->next == nullptr) {
				toDel->prev->next = nullptr;
			} else {
				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;
			}

			delete toDel;
		}
	}

	bool isRouteInList(int numOfRoute) {
		Route* cur = this->head;
		while (cur != nullptr) {
			if (cur->number == numOfRoute) { return true; }
			cur = cur->next;
		}
		return false;
	}

	bool isEmpty() {
		if (this->head == nullptr) {
			return true;
		} else {
			return false;
		}
	}

	string findByNum(int numOfRoute) {
		Route* cur = this->head;

		while (cur != nullptr) {
			if (cur->number == numOfRoute) {
				return cur->str();
			}
			cur = cur->next;
		}

		throw range_error("the route with this number is not in the list");
	}

	void readFromFile(const string name) {
		ifstream file(name, ios::in);
		if (!file.is_open()) {
			ofstream new_file(name, ios::out);
			new_file << 0 << endl;
			new_file.close();
			return;
		}
		int length = 0;
		int number;
		string start;
		string end;
		file >> length;
		for (int i = 0; i < length; i++) {
			file >> number;
			getline(file >> ws, start); // file >> ws обеспечивает удаление всех пробелов и символов новой строки из начала потока
			getline(file >> ws, end);
			this->append(Route(number, start, end));
		}
		file.close();
	}

	void writeInFile(const string& name) {
		ofstream file(name, ios::out);
		file << this->len << endl;
		Route* cur = this->head;
		for (int i = 0; i < this->len; i++) {
			file << cur->number << endl;
			file << cur->start << endl;
			file << cur->end << endl;
			cur = cur->next;
		}
		file.close();
	}

	void changeNumber(int old_num, int new_num) {
		Route* cur = this->head;
		while (cur->number != old_num) {
			cur = cur->next;
		}
		cur->number = new_num;
	}

	void changeStart(int num, const string& new_start) {
		Route* cur = this->head;
		while (cur->number != num) {
			cur = cur->next;
		}
		cur->start = new_start;
	}

	void changeEnd(int num, const string& new_end) {
		Route* cur = this->head;
		while (cur->number != num) {
			cur = cur->next;
		}
		cur->end = new_end;
	}

	size_t getLen() {
		return this->len;
	}

	void print() {
		Route* cur = this->head;
		while (cur != nullptr) {
			cout << cur->str();
			cur = cur->next;
		}
	}

	void sort() {
		if (len < 2) { return; }
		Route* cur;
		Route* next;
		int tempN;
		string tempStart;
		string tempEnd;
		for (int i = 0; i < (this->len - 1); i++) {
			cur = this->head;
			for (int j = 0; j < (this->len - i - 1); j++) {
				if (cur->number > cur->next->number) {
					next = cur->next;
					tempN = cur->number;
					tempStart = cur->start;
					tempEnd = cur->end;
					cur->number = next->number;
					cur->start = next->start;
					cur->end = next->end;
					next->number = tempN;
					next->start = tempStart;
					next->end = tempEnd;
				}
				cur = cur->next;
			}
		}
	}

	~RouteList() {
		if (this->head != nullptr) {
			Route* cur = this->head;
			Route* temp;
			while (cur != nullptr) {
				temp = cur;
				cur = cur->next;
				delete temp;
			}
			this->head = nullptr;
		}
	}
};