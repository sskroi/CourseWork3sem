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

        try {
            choice = menu::mainMenuChoice();

            if (choice == 1) {
                menu::printRouteList(list);
            } else if (choice == 2) {
                menu::findRoute(list);
            } else if (choice == 3) {
                menu::addRoute(list);
            } else if (choice == 4) {
                menu::deleteRoute(list);
            } else if (choice == 5) {
                menu::changeRoute(list);
            } else if (choice == 6) {
                menu::sortRouteList(list);
            } else if (choice == 0) {
                return;
            }

            list.writeInFile(DB_FILENAME);

        } catch (...) {
            std::cout << "Произошла ошибка" << std::endl;
            std::cout << "Нажмите \x1B[38;5;216mEnter\x1B[0m чтобы перейти в главное меню . . . ";
            menu::waitEnter();
        }
    }
}

void initDatabase(RouteList& list) {
    try {
        RouteList fromDb;
        if (!fromDb.readFromFile(DB_FILENAME)) {
            std::cout << "\x1B[38;5;197mФайл с базой данных \"\x1B[38;5;122m" << DB_FILENAME << "\x1B[38;5;197m\"\n";
            std::cout << "НЕ обнаружен в директории программы\x1B[0m\n";
            std::cout << "Будет создан \x1B[38;5;105mпустой\x1B[0m файл с БД\n\n";
            std::cout << "Нажмите \x1B[38;5;216mEnter\x1B[0m чтобы перейти в главное меню . . . ";
            menu::waitEnter();
            fromDb.writeInFile(DB_FILENAME);
        }
        list = fromDb;
    } catch (const std::exception& ex) {
        std::cout << "\x1B[38;5;197mФайл с базой данных \"\x1B[38;5;122m" << DB_FILENAME << "\x1B[38;5;197m\" повреждён.\x1B[0m\n";
        std::cout << "Ошибка: " << ex.what() << std::endl;
        std::cout << "Файл будет перезаписан \x1B[38;5;105mновым пустым\x1B[0m файлом\n";
        std::cout << "Нажмите \x1B[38;5;216mEnter\x1B[0m чтобы перейти в главное меню . . . ";
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