#include "RouteList.hpp"
#include "menu.hpp"
using namespace std;


int main() {
    // основной список, хранящий все маршруты
    RouteList list;

    // название файла с БД
    const string filename = "data.txt";

    // чтение БД
    list.readFromFile(filename);

    // переменная с выбором пользователя
    int choice;

    // основной цикл программы
    while (true) {

        choice = menu::mainMenuChoice();

        if (choice == 1) {
            menu::printRouteList(list);
        }

        else if (choice == 2) {
            menu::addInRouteListFromKeyBoard(list);
        }

        else if (choice == 3) {
            menu::changeRoute(list);
        }

        else if (choice == 4) {
            menu::deleteByNumberFromKeyboard(list);
        }

        else if (choice == 5) {
            menu::findRouteByNumberFromKeyboard(list);
        }

        else if (choice == 6) {
            menu::sortRouteList(list);
        }

        else if (choice == 7) {
            list.writeInFile("data.txt");
            system("cls");
            cout << "База данных сохранена" << endl;
            menu::backToMenu();
        }

        else if (choice == 0) {
            list.writeInFile(filename);
            system("cls");
            break;
        }
    }
}