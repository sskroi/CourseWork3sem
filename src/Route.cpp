#include <iostream>
#include <sstream>
#include <iomanip>

#include "Route.h"

using namespace std;

Route::Route(int number, const string& start, const string& end)
    : number(number), start(start), end(end), next(nullptr), prev(nullptr) {}

Route::Route(const Route& r)
    : number(r.number), start(r.start), end(r.end), next(nullptr), prev(nullptr) {}

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
