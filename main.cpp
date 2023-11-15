#include <string>
#include "RouteList.hpp"
#include "menu.hpp"
using namespace std;

// название файла с БД
const string DB_FILENAME = "route_list_data.txt";

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


int main() {
    // основной список, хранящий все маршруты
    RouteList list;

    // чтение БД
    if (!list.readFromFile(DB_FILENAME)) {
        cout << "!!! Файл с базой данных - \"" << DB_FILENAME << "\"\n";
        cout << "НЕ обнаружен в директории программы\n";
        cout << "Будет создан пустой файл с БД\n\n";
        cout << "Нажмите любую клавишу чтобы перейти в главное меню . . . ";
        system("pause > nul");
        list.writeInFile(DB_FILENAME);
    };

    // запуска основного цикла программы
    mainLoop(list);

    // сохранение в базу данных перед завершение программы
    list.writeInFile(DB_FILENAME);
}