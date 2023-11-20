#pragma once
#include <string>
#include <stdexcept>

class Route;

class RouteList {
public:
	RouteList();

	RouteList(const RouteList& other);

	RouteList operator=(const RouteList& other);

	void append(const Route& route);

	void deleteByNum(int numOfRoute);

	bool isRouteInList(int numOfRoute);

	Route& findByNum(int numOfRoute);

	RouteList findByStart(const std::string searchStart);

	RouteList findByEnd(const std::string searchEnd);

	void changeRouteNumber(int oldRouteNum, int newRouteNum);

	void changeRouteStart(int routeNum, const std::string newRouteStart);

	void changeRouteEnd(int routeNum, const std::string newRouteEnd);

	size_t size();

	void print(int numberIndent = 0);

	void sort();

	int maxNumLen();

	bool readFromFile(const std::string& name);

	void writeInFile(const std::string& name);

	bool isEmpty();

	class RouteNotExistErr : public std::range_error {
	public:
		RouteNotExistErr(const std::string& msg);
	};

	~RouteList();

private:
	Route* head = nullptr;
	size_t _size = 0;

	void clear();

	int maxRouteNum();

	static void swapRoutes(Route& a, Route& b);
};