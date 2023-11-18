#pragma once
#include <string>
#include <stdexcept>
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
	Route(int number, const string& start, const string& end);

	Route(const Route& r);

	string str(int numberIndent = 0, bool endline = true);
};
ostream& operator<<(ostream& os, Route& route);


class RouteNotExistErr : public std::range_error {
public:
	RouteNotExistErr(const string& msg);
};


class RouteList {
private:
	Route* head = nullptr;
	size_t _size = 0;

public:
	RouteList();

	RouteList(const RouteList& other);

	RouteList operator=(const RouteList& other);

	void append(const Route& route);

	void deleteByNum(int numOfRoute);

	bool isRouteInList(int numOfRoute);

	Route& findByNum(int numOfRoute);

	RouteList findByStart(const string searchStart);

	RouteList findByEnd(const string searchEnd);

	void changeRouteNumber(int oldRouteNum, int newRouteNum);

	void changeRouteStart(int routeNum, const string newRouteStart);

	void changeRouteEnd(int routeNum, const string newRouteEnd);

	size_t size();

	void print(int numberIndent = 0);

	void sort();

	int maxNumLen();

	bool readFromFile(const string& name);

	void writeInFile(const string& name);

	bool isEmpty();

	~RouteList();

private:
	void clear();

	int maxRouteNum();

	static void swapRoutes(Route& a, Route& b);
};