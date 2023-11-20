#pragma once
#include <string>
#include <iostream>

class RouteList;

class Route {
private:
    int number;
    std::string start;
    std::string end;
    Route* next;
    Route* prev;
    friend class RouteList;

public:
    Route(int number, const std::string& start, const std::string& end);

    Route(const Route& r);

    std::string str(int numberIndent = 0, bool endline = true);
};

std::ostream& operator<<(std::ostream& os, Route& route);