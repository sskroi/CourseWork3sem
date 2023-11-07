#include "RouteList.hpp"
#include "menu.hpp"
using namespace std;


int main() {
    {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);

        // �������� ������, �������� ��� ��������
        RouteList list;

        // �������� ����� � ��
        const string filename = "data.txt";

        // ������ ��
        list.readFromFile(filename);

        // ���������� � ������� ������������
        int choice;

        // �������� ���� ���������
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
                cout << "���� ������ ���������" << endl;
                menu::backToMenu();
            }

            else if (choice == 0) {
                list.writeInFile(filename);
                system("cls");
                break;
            }
        }
    }
}