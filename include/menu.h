#pragma once
#include <string>

class RouteList;

namespace menu {

// inputInt запрашивает у пользователя ввод целого числа в диапазоне [l;r]
int inputInt(const std::string& text, int l = -1'000'000, int r = 1'000'000);

// inputString запрашивает у пользователя ввод строки с ограничением максимальной длины
std::string inputString(const std::string& text, size_t maxLen = 100ULL);

int mainMenuChoice();

void backToMenu();

void findRoute(RouteList& list);

void addRoute(RouteList& list);

void deleteRoute(RouteList& list);

void printRouteList(RouteList& list);

void changeRoute(RouteList& list);

void sortRouteList(RouteList& list);

// stripString удаляет пробел в начале и концы строке
void stripString(std::string& s);

// countUTF8Chars подсчитывает количество utf-8 символов в строке
size_t countUTF8Chars(const std::string& str);

}