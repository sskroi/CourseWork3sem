#include <string>
#include <sstream>
using namespace std;
namespace menu {

const string INPUT_STR = "Выберите дейсвтие: ";
const string INCORRECT_INPUT_STR = "Некорректный ввод: ";

const string MENU_STR =
"««« ГЛАВНОЕ МЕНЮ »»»\n"
"1) Посмотреть список всех маршрутов\n"
"2) Добавить маршрут\n"
"3) Изменить маршрут\n"
"4) Удалить маршрут\n"
"5) Найти маршрут\n"
"6) Отсортировать маршруты по номеру\n"
"7) Сохранить БД\n"
"0) Выход\n\n" + INPUT_STR;

const string ROUTE_CHANGE_MENU_STR =
"1) Изменить номер\n"
"2) Изменить начальный пункт\n"
"3) Изменить конечный пункт\n"
"4) Вернуться в главное меню\n\n" + INPUT_STR;

const string REPEAT_INPUT_STR = "Нажмите любую клавишу для повторного ввода . . . ";

const string EMPTY_STRING_STR = "\n" + INCORRECT_INPUT_STR + "вы ввели пустую строку\n";

// adding
const string ADDING_ROUTE_NUM_STR = "Введите номер добавляемого маршрута: ";
const string ADDING_ALREADY_EXIST_STR = "Ошибка: маршрут с таким номером уже существует\n";
const string ADDING_START_STR = "Введите начальный пункт маршрута: ";
const string ADDING_END_STR = "Введите конечный пункт маршрута: ";
const string ADDING_SUCCESS_STR = "Маршрут успешно добавлен:\n\n";


string incorrectIntInputStr(int l, int r) {
    stringstream stream;

    stream << endl << INCORRECT_INPUT_STR;
    stream << "введите целое число в диапазоне [" << l << "; " << r << "]" << endl;

    return stream.str();
}

string incorrectInputStringLenStr(size_t maxLen) {
    stringstream stream;

    stream << endl << INCORRECT_INPUT_STR;
    stream << "максимальная длина строки = " << maxLen << endl;

    return stream.str();
}
}