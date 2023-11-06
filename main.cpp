#include "RouteList.h"
#include "menu.h"
using namespace std;


int main() {
    {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);

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

            choice = mainMenuChoice();

            if (choice == 1) {
                printRouteList(list);
            }

            else if (choice == 2) {
                addInRouteListFromKeyBoard(list);
            }

            else if (choice == 3) {
                changeRoute(list);
            }

            else if (choice == 4) {
                deleteByNumberFromKeyboard(list);
            }

            else if (choice == 5) {
                findRouteByNumberFromKeyboard(list);
            }

            else if (choice == 6) {
                sortRouteList(list);
            }

            else if (choice == 7) {
                list.writeInFile("data.txt");
                system("cls");
                cout << "База данных сохранена" << endl;
                backToMenu();
            }

            else if (choice == 0) {
                list.writeInFile(filename);
                system("cls");
                break;
            }
        }
    }
}