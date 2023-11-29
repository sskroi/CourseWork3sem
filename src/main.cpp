#include <string>
#include <iostream>

#include "RouteList.h"
#include "menu.h"

// название файла с БД
const std::string DB_FILENAME = "../db/routes.bin";

void mainLoop(RouteList& list) {
    // переменная с выбором пользователя
    int choice;

    // основной цикл программы
    while (true) {

        choice = menu::mainMenuChoice();

        if (choice == 1) {
            menu::printRouteList(list);
        }

        else if (choice == 2) {
            menu::findRoute(list);
        }

        else if (choice == 3) {
            menu::addRoute(list);
        }

        else if (choice == 4) {
            menu::deleteRoute(list);
        }

        else if (choice == 5) {
            menu::changeRoute(list);
        }

        else if (choice == 6) {
            menu::sortRouteList(list);
        }

        else if (choice == 0) {
            return;
        }

        list.writeInFile(DB_FILENAME);
    }
}

void initDatabase(RouteList& list) {
    RouteList fromDb;
    try {
        if (!fromDb.readFromFile(DB_FILENAME)) {
            std::cout << "!!! Файл с базой данных - \"" << DB_FILENAME << "\"\n";
            std::cout << "НЕ обнаружен в директории программы\n";
            std::cout << "Будет создан пустой файл с БД\n\n";
            std::cout << "Нажмите Enter чтобы перейти в главное меню . . . ";
            menu::waitEnter();
            fromDb.writeInFile(DB_FILENAME);
        }
        list = fromDb;
    } catch (...) {
        std::cout << "!!! Файл с базой данных - \"" << DB_FILENAME << "\" повреждён. \n";
        std::cout << "Он будет перезаписан новым пустым файлом\n";
        std::cout << "Нажмите Enter чтобы перейти в главное меню . . . ";
        menu::waitEnter();
        list.clear();
        list.writeInFile(DB_FILENAME);
    }
}

int main() {
    // основной список, хранящий все маршруты
    RouteList list;

    // инициализация базы данных
    initDatabase(list);

    // запуска основного цикла программы
    mainLoop(list);

    // сохранение в базу данных перед завершение программы
    list.writeInFile(DB_FILENAME);

    return 0;
}