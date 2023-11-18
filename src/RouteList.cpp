#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "RouteList.h"
#include "menu.h"
using namespace std;

Route::Route(int number, const string& start, const string& end) :
	number(number), start(start), end(end), next(nullptr), prev(nullptr) {}

Route::Route(const Route& r) :
	number(r.number), start(r.start), end(r.end), next(nullptr), prev(nullptr) {}

string Route::str(int numberIndent, bool endline) {
	stringstream s;

	s << setw(numberIndent) << this->number << " | " << this->start << " -> " << this->end;
	if (endline) s << endl;

	return s.str();
}

ostream& operator<<(ostream& os, Route& route) {
	os << route.str();
	return os;
}


RouteNotExistErr::RouteNotExistErr(const string& msg) : std::range_error(msg) {}


RouteList::RouteList() {}

RouteList::RouteList(const RouteList& other) {
	Route* cur = other.head;

	while (cur != nullptr) {
		this->append(*cur);

		cur = cur->next;
	}
}

RouteList RouteList::operator=(const RouteList& other) {
	this->clear();

	Route* cur = other.head;
	while (cur != nullptr) {
		this->append(*cur);

		cur = cur->next;
	}

	return *this;
}

void RouteList::append(const Route& route) {
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

void RouteList::deleteByNum(int numOfRoute) {
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

bool RouteList::isRouteInList(int numOfRoute) {
	Route* cur = this->head;
	while (cur != nullptr) {
		if (cur->number == numOfRoute) { return true; }
		cur = cur->next;
	}
	return false;
}

Route& RouteList::findByNum(int numOfRoute) {
	Route* cur = this->head;

	while (cur != nullptr) {
		if (cur->number == numOfRoute) {
			return *cur;
		}
		cur = cur->next;
	}

	throw RouteNotExistErr("the route with this number is not in the list");
}

RouteList RouteList::findByStart(const string searchStart) {
	RouteList result;

	Route* cur = this->head;

	while (cur != nullptr) {
		if (cur->start.find(searchStart) != std::string::npos) {
			result.append(*cur);
		}
		cur = cur->next;
	}

	return result;
}

RouteList RouteList::findByEnd(const string searchEnd) {
	RouteList result;

	Route* cur = this->head;

	while (cur != nullptr) {
		if (cur->end.find(searchEnd) != std::string::npos) {
			result.append(*cur);
		}
		cur = cur->next;
	}

	return result;
}

void RouteList::changeRouteNumber(int oldRouteNum, int newRouteNum) {
	try {
		this->findByNum(oldRouteNum).number = newRouteNum;
	} catch (RouteNotExistErr& ex) {}
}

void RouteList::changeRouteStart(int routeNum, const string newRouteStart) {
	try {
		this->findByNum(routeNum).start = newRouteStart;
	} catch (RouteNotExistErr& ex) {}
}

void RouteList::changeRouteEnd(int routeNum, const string newRouteEnd) {
	try {
		this->findByNum(routeNum).end = newRouteEnd;
	} catch (RouteNotExistErr& ex) {}
}

size_t RouteList::size() { return this->_size; }

void RouteList::print(int numberIndent) {
	Route* cur = this->head;
	while (cur != nullptr) {
		cout << cur->str(numberIndent);
		cur = cur->next;
	}
}

void RouteList::sort() {
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

int RouteList::maxNumLen() {
	int maxNum = this->maxRouteNum();
	int len = 0;

	while (maxNum > 0) {
		maxNum /= 10;
		len++;
	}
	return len;
}

bool RouteList::readFromFile(const string& name) {
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

void RouteList::writeInFile(const string& name) {
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

bool RouteList::isEmpty() {
	return this->head == nullptr;
}

RouteList::~RouteList() {
	this->clear();
}


void RouteList::clear() {
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

int RouteList::maxRouteNum() {
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

void RouteList::swapRoutes(Route& a, Route& b) {
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
