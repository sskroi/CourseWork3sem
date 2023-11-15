#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

class RouteList;

class Route {
private:
	int number;
	string start;
	string end;
	Route* next;
	Route* prev;
	friend RouteList;

public:
	Route(int number, const string& a, const string& b) :
		number(number), start(a), end(b), next(nullptr), prev(nullptr) {}

	Route(const Route& r) :
		number(r.number), start(r.start), end(r.end), next(nullptr), prev(nullptr) {}

	string str(int numberIndent = 0, bool endline = true) {
		stringstream s;

		s << setw(numberIndent) << this->number << " | " << this->start << " -> " << this->end;
		if (endline) s << endl;

		return s.str();
	}
};
ostream& operator<<(ostream& os, Route& route) {
	os << route.str();
	return os;
}

class RouteNotExistErr : public std::range_error {
public:
	RouteNotExistErr(const string& msg) : std::range_error(msg) {}
};

class RouteList {
private:
	Route* head = nullptr;
	size_t _size = 0;

public:
	RouteList() {}

	RouteList(const RouteList& other) {
		Route* cur = other.head;

		while (cur != nullptr) {
			this->append(*cur);

			cur = cur->next;
		}
	}

	RouteList operator=(const RouteList& other) {
		this->clear();

		Route* cur = other.head;
		while (cur != nullptr) {
			this->append(*cur);

			cur = cur->next;
		}

		return *this;
	}

	void append(const Route& route) {
		Route* newNode = new Route(route);
		this->_size++;

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
		if (!this->isRouteInList(numOfRoute)) {
			throw range_error("the route with this number is not in the list");
		} else {
			this->_size--;
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

	Route& findByNum(int numOfRoute) {
		Route* cur = this->head;

		while (cur != nullptr) {
			if (cur->number == numOfRoute) {
				return *cur;
			}
			cur = cur->next;
		}

		throw RouteNotExistErr("the route with this number is not in the list");
	}

	RouteList findByStart(const string start) {
		RouteList result;

		Route* cur = this->head;

		while (cur != nullptr) {
			if (cur->start == start) {
				result.append(*cur);
			}
			cur = cur->next;
		}

		return result;
	}

	RouteList findByEnd(const string end) {
		RouteList result;

		Route* cur = this->head;

		while (cur != nullptr) {
			if (cur->end == end) {
				result.append(*cur);
			}
			cur = cur->next;
		}

		return result;
	}

	void changeRouteNumber(int oldRouteNum, int newRouteNum) {
		try {
			this->findByNum(oldRouteNum).number = newRouteNum;
		} catch (RouteNotExistErr& ex) {}
	}

	void changeRouteStart(int routeNum, const string newRouteStart) {
		try {
			this->findByNum(routeNum).start = newRouteStart;
		} catch (RouteNotExistErr& ex) {}
	}

	void changeRouteEnd(int routeNum, const string newRouteEnd) {
		try {
			this->findByNum(routeNum).end = newRouteEnd;
		} catch (RouteNotExistErr& ex) {}
	}

	size_t size() { return this->_size; }

	void print(int numberIndent = 0) {
		Route* cur = this->head;
		while (cur != nullptr) {
			cout << cur->str(numberIndent);
			cur = cur->next;
		}
	}

	void sort() {
		if (_size < 2) { return; }
		Route* cur;

		for (size_t i = 0; i < (this->_size - 1); i++) {
			cur = this->head;

			for (size_t j = 0; j < (this->_size - i - 1); j++) {
				if (cur->number > cur->next->number) {
					swapRoutes(*cur, *(cur->next));
				}
				cur = cur->next;
			}
		}
	}

	int maxNumLen() {
		int maxNum = this->maxRouteNum();
		int len = 0;

		while (maxNum > 0) {
			maxNum /= 10;
			len++;
		}
		return len;
	}

	bool readFromFile(const string& name) {
		ifstream file(name, ios::in);

		if (!file.is_open()) {
			return false;
		}

		size_t listSize;

		int routeNum;
		string routeStart;
		string routeEnd;

		file >> ws >> listSize;
		for (size_t i = 0; i < listSize; i++) {
			file >> ws >> routeNum;
			getline(file >> ws, routeStart); // file >> ws обеспечивает удаление всех пробелов и символов новой строки из начала потока
			getline(file >> ws, routeEnd);
			this->append(Route(routeNum, routeStart, routeEnd));
		}
		file.close();

		return true;
	}

	void writeInFile(const string& name) {
		ofstream file(name, ios::out);

		file << this->_size << "\n";

		Route* cur = this->head;
		for (size_t i = 0; i < this->_size; i++) {
			file << cur->number << "\n";
			file << cur->start << "\n";
			file << cur->end << "\n";

			cur = cur->next;
		}
		file.close();
	}

	bool isEmpty() {
		return this->head == nullptr;
	}

	~RouteList() {
		this->clear();
	}

private:
	void clear() {
		if (this->head != nullptr) {
			Route* cur = this->head;
			Route* temp;

			while (cur != nullptr) {
				temp = cur;
				cur = cur->next;
				delete temp;
			}
			this->head = nullptr;
			this->_size = 0;
		}
	}

	int maxRouteNum() {
		Route* cur = this->head;
		int maxNum = 0;

		while (cur != nullptr) {
			if (cur->number > maxNum) {
				maxNum = cur->number;
			}
			cur = cur->next;
		}
		return maxNum;
	}

	static void swapRoutes(Route& a, Route& b) {
		int tempNum;
		string tempStart;
		string tempEnd;

		tempNum = a.number;
		tempStart = a.start;
		tempEnd = a.end;

		a.number = b.number;
		a.start = b.start;
		a.end = b.end;

		b.number = tempNum;
		b.start = tempStart;
		b.end = tempEnd;
	}
};