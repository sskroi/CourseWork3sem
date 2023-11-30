#pragma once
#include <string>

using namespace std;

namespace menu {

const string INPUT_STR = "Выберите дейсвтие \x1B[38;5;216m>>\x1B[0m ";
const string INCORRECT_INPUT_STR = "\x1B[38;5;167mНекорректный ввод:\x1B[0m ";
const string BACK_TO_MENU_STR = "Нажмите \x1B[38;5;216mEnter\x1B[0m чтобы вернуться в меню . . . ";

const string MAIN_MENU_STR =
"««« \x1B[1m\x1B[38;5;209mГЛАВНОЕ МЕНЮ\x1B[0m »»»\n"
"\x1B[38;5;216m1\x1B[0m) Посмотреть список всех маршрутов\n"
"\x1B[38;5;216m2\x1B[0m) Найти маршрут\n"
"\x1B[38;5;216m3\x1B[0m) Добавить маршрут\n"
"\x1B[38;5;216m4\x1B[0m) Удалить маршрут\n"
"\x1B[38;5;216m5\x1B[0m) Изменить маршрут\n"
"\x1B[38;5;216m6\x1B[0m) Отсортировать маршруты по номеру\n"
"\x1B[38;5;216m0\x1B[0m) Выход\n\n" + INPUT_STR;
const int MAIN_MENU_ITEMS_COUNT = 6;

const string REPEAT_INPUT_STR = "Нажмите \x1B[38;5;216mEnter\x1B[0m для повторного ввода . . . ";

const string EMPTY_STRING_STR = "\n" + INCORRECT_INPUT_STR + "вы ввели пустую строку\n";

// adding
const string ADDING_ROUTE_NUM_STR = "Введите номер добавляемого маршрута: ";
const string ADDING_ALREADY_EXIST_STR = "\nОшибка: маршрут с таким номером уже существует\n";
const string ADDING_START_STR = "Введите начальный пункт маршрута: ";
const string ADDING_END_STR = "Введите конечный пункт маршрута: ";
const string ADDING_SUCCESS_STR = "Маршрут успешно добавлен:\n\n";

// deleting
const string DELETING_NUM_STR = "Введите номер маршрута, который хотите удалить: ";
const string DELETING_NOT_EXIST_STR = "\nМаршрута с таким номером не существует\n";
const string DELETING_SUCCESS = "\nМаршрут успешно удалён\n";

// finding
const string ROUTE_FIND_MENU_STR =
"«« Поиск »»\n"
"\x1B[38;5;216m1\x1B[0m) По номеру\n"
"\x1B[38;5;216m2\x1B[0m) По пункту отправления\n"
"\x1B[38;5;216m3\x1B[0m) По пункту прибытия\n"
"\x1B[38;5;216m0\x1B[0m) Вернуться в главное меню\n\n" + INPUT_STR;
const int ROUTE_FIND_MENU_ITEMS_COUNT_STR = 3;
const string FINDING_NUM_STR = "Введите номер маршрута, который хотите найти: ";
const string FINDING_START_STR = "Введите стартовый пункт маршрута, который хотите найти: ";
const string FINDING_END_STR = "Введите конечный пункт маршрута, который хотите найти: ";
const string FINDING_RESULT_STR = "-> Результаты поиска:\n";
const string FINDING_NO_RESULT_STR = "По вашему запросу ничего не найдено\n";

// change
const string CHANGE_HEADER_STR = "";
const string CHANGE_MENU_STR =
"\x1B[38;5;216m1\x1B[0m) Изменить номер\n"
"\x1B[38;5;216m2\x1B[0m) Изменить начальный пункт\n"
"\x1B[38;5;216m3\x1B[0m) Изменить конечный пункт\n"
"\x1B[38;5;216m0\x1B[0m) Вернуться в главное меню\n\n" + INPUT_STR;
const int CHANGE_MENU_ITEMS_COUNT = 3;
const string CHANGE_INPUT_NUM_STR = "Введите номер маршрута, который хотите изменить: ";
const string CHANGE_NOT_EXIST_STR = "\nМаршрута с таким номером не существует\n";
const string CHANGE_NEW_NUM_STR = "Введите новый номер маршрута: ";
const string CHANGE_ALREADY_EXIST_STR = "\nОшибка: маршрут с таким номером уже существует\n";
const string CHANGE_SUCCESS = "\nИзменения успешно внесены:\n";
const string CHANGE_INPUT_START_STR = "Введите новый начальный пункт: ";
const string CHANGE_INPUT_END_STR = "Введите новый конечный пункт: ";

const string SORT_PROCESSING = "Сортировка начата . . . \n";

}