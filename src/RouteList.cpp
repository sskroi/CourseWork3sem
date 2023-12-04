#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdint>

#include "RouteList.h"


using namespace std;

RouteList::RouteNotExistErr::RouteNotExistErr(const string& msg)
	: std::range_error(msg) {}


RouteList::RouteList() {}

RouteList::RouteList(const RouteList& other) {
	Route* cur = other.head;

	while (cur != nullptr) {
		this->append(*cur);

		cur = cur->next;
	}
}

RouteList& RouteList::operator=(const RouteList& other) {
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

RouteList RouteList::findByStart(const string& searchStart) {
	RouteList result;

	Route* cur = this->head;

	while (cur != nullptr) {
		if (this->lowerEnRu(cur->start).find(this->lowerEnRu(searchStart)) != std::string::npos) {
			result.append(*cur);
		}
		cur = cur->next;
	}

	return result;
}

RouteList RouteList::findByEnd(const string& searchEnd) {
	RouteList result;

	Route* cur = this->head;

	while (cur != nullptr) {
		if (this->lowerEnRu(cur->end).find(this->lowerEnRu(searchEnd)) != std::string::npos) {
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
			} else {
				cur = cur->next;
			}
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

bool RouteList::readFromFile(const string& fileName) {
	ifstream ifile(fileName, ios::in | ios::binary);
	if (!ifile.is_open()) {
		return false;
	}

	enum class readState { num, start, end };
	readState curState = readState::num;

	int num;
	string start = "";
	string end = "";
	char temp;

	while (!ifile.eof()) {
		if (curState == readState::num) {
			ifile.read(reinterpret_cast<char*>(&num), sizeof(num));
			if (ifile.eof()) { break; }
			if (num < 1) {
				throw std::runtime_error("некорректные данные для номера маршрута (не положительное число)");
			}
			curState = readState::start;
		} else if (curState == readState::start) {
			ifile.read(&temp, sizeof(temp));
			if (ifile.eof()) { break; }
			if (temp == '\0') {
				curState = readState::end;
			} else if (temp >= 1 && temp <= 31) {
				throw std::runtime_error("некорректные данные строки (в строке содержится управляющий сивол)");
			} else {
				start += temp;
			}
		} else if (curState == readState::end) {
			ifile.read(&temp, sizeof(temp));
			if (ifile.eof()) { break; }
			if (temp == '\0') {
				this->append(Route(num, start, end));
				start.clear();
				end.clear();
				curState = readState::num;
			} else if (temp >= 1 && temp <= 31) {
				throw std::runtime_error("некорректные данные строки (в строке обнаружен управляющий сивол)");
			} else {
				end += temp;
			}
		}
	}
	ifile.close();
	if (curState != readState::num) {
		throw std::runtime_error("отсутствует часть данных, невозможно корректно прочитать файл");
	}
	return true;
}

void RouteList::writeInFile(const string& fileName) {
	ofstream oFile(fileName, ios::out | ios::binary);

	Route* cur = this->head;

	while (cur != nullptr) {
		oFile.write(reinterpret_cast<const char*>(&(cur->number)), sizeof(cur->number));

		oFile.write(cur->start.c_str(), cur->start.size() + 1);
		oFile.write(cur->end.c_str(), cur->end.size() + 1);

		cur = cur->next;
	}
	oFile.close();
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
	if (this->head == &a) {
		this->head = &b;
		b.prev = nullptr;
	} else {
		a.prev->next = &b;
		b.prev = a.prev;
	}

	if (b.next == nullptr) {
		a.next = nullptr;
	} else {
		b.next->prev = &a;
		a.next = b.next;
	}
	b.next = &a;
	a.prev = &b;
}

std::string RouteList::lowerEnRu(const std::string& str) {
	std::string res;
	size_t i = 0;
	uint8_t ch1;
	uint8_t ch2;

	while (i < str.size()) {
		ch1 = static_cast<uint8_t>(str[i]);
		if (i + 1 < str.size()) {
			ch2 = static_cast<uint8_t>(str[i + 1]);
		}

		if (ch1 >= 65 && ch1 <= 90) {
			res += static_cast<char>(ch1 + 32);
			++i;
		} else if (ch1 == 208 && ch2 >= 144 && ch2 <= 159) {
			res += static_cast<char>(208);
			res += static_cast<char>(ch2 + 32);
			i += 2;
		} else if (ch1 == 208 && ch2 >= 160 && ch2 <= 175) {
			res += static_cast<char>(209);
			res += static_cast<char>(ch2 - 32);
			i += 2;
		} else if (ch1 == 208 && ch2 == 129) {
			res += static_cast<char>(209);
			res += static_cast<char>(145);
			i += 2;
		} else {
			res += static_cast<char>(ch1);
			++i;
		}
	}
	return res;
}
