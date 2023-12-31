#pragma once
#include <string>
#include <stdexcept>

#include "Route.h"

class RouteList {
public:
	RouteList();

	RouteList(const RouteList& other);

	RouteList(RouteList&& other);

	RouteList& operator=(const RouteList& other);

	RouteList& operator=(RouteList&& other);

	void append(const Route& route);

	void deleteByNum(int numOfRoute);

	bool isRouteInList(int numOfRoute);

	Route& findByNum(int numOfRoute);

	RouteList findByStart(const std::string& searchStart);

	RouteList findByEnd(const std::string& searchEnd);

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

	void clear();

	~RouteList();

private:
	Route* head = nullptr;
	size_t _size = 0;

	int maxRouteNum();

	void swapRoutes(Route& a, Route& b);

	static std::string lowerEnRu(const std::string& str);
};