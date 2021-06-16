#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ostream>
#include <cstdlib>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <iomanip>
#include <ctime>
#include "tabulate/table.hpp"

using namespace std;
using std::string;
using namespace tabulate;
#if __cplusplus >= 201703L
#include <variant>
using std::variant;
#else
#include "tabulate/variant_lite.hpp"
using nonstd::variant;
#endif
using Row_t = std::vector<variant<std::string, const char*, Table>>;


                    //структуры программы 

// данные о пользователе
struct Profile
{
    string name;
    string pass;
    int level;
};

// данные о бытовой технике
struct AppliancesData
{
    string type;
    string name;
    string model;
    string color;
};

// общие сведения о бытовой технике
struct Appliances
{
    int id;
    AppliancesData Appliancesequipment;
    int cost;
    string receipt_date;
    string buyer;
    string buyerEmail;
    string departure_date;
};

                            //глобальные переменные

bool choiceCreateFD = false;
bool fileCreate;
bool fileAdminCreate;
bool availabilityAppliances;
vector<Appliances> allAppliances;
int varSort = 1;
string userNameInProgramm;

                            // объявление всех функций
                            
// проеверка файла админа
bool CreateOrDeleteAdminFile();
// запись данных в файла профиля
string WorkProfileFD(Profile user, bool rePass, bool del);
// сбор данных для пользователя
Profile GetNewProfileData(bool ifUser);
// Функции выбора в меню
void GetChoiceMenuAdmin();
void GetChoiceMenuManager();
void GetChoiceMenuUser();
// функции вывода меню
void PrintMenuAdmin();
void PrintMenuManager();
void PrintMenuUser();
// функции получения значения с клавиатуры
// получения значения int
int getValueInt(string mess);
// получения значения string
string getValueStr(string mess);
// проверка на наличие файла данных
bool SearchDataFile();
// создание и затирание файла данных
bool CreateOrDeleteFD(bool createOrDelete);
// сбор сведений по бытовой технике
Appliances aggregationAppliancesData();
// запись данных нового бытовой технике в файл данных (перезапись файла)
bool creatRecordInFD(bool atMemory);
// принт таблицы файла данных
void printTable(bool managerOrAdmin, vector<Appliances> data, bool search);
// поиск бытовой технике и принт таблицы
void searchAndPrintTable(int change, bool managerOrAdmin);
// функция поиска в строке
bool search(string query, string fundStr);
// получение данных бытовой технике в память
void getAllAppliancesFD();
// удаление данных бытовой технике в памяти и перезапись в файл
bool deleteAppliancesInMemory();
// изменение данных бытовой технике в памяти и перезапись в файл
bool changeAppliancesInMemory(bool userShop);
                            //сортировка
// компаратор по модели
bool comparareName(const Appliances lhs, const Appliances rhs);
// компаратор по цвету
bool comparareType(const Appliances lhs, const Appliances rhs);
// компаратор по стоимости
bool comparareCost(const Appliances lhs, const Appliances rhs);
// компаратор по id
bool comparareId(const Appliances lhs, const Appliances rhs);
// функции сортировки
// сортировка по производиителю
void sortName();
// сортировка по типу
void sortType();
// сортировка по id
void sortId();
// сортировка по стоимости
void sortCost();

                            //функции вывода меню

void PrintMenuMain()
{
    cout << "          Меню входа\n";
    cout << "\n";
    cout << "Пожалуйста укажите пункт\n";
    cout << "1 - Вход администора\n";
    cout << "2 - Вход менеджера\n";
    cout << "3 - Вход пользователя\n";
    cout << "4 - Выход\n";
    cout << "Ваш выбор: ";
}

void PrintMenuAdmin()
{
    cout << "=================================================\n";
    cout << "              Меню администратора\n";
    cout << "=================================================\n";
    cout << "\n";
    cout << "    Пожалуйста укажите пункт\n";
    cout << "\n";
    cout << "-------------  Работа с файлом данных товаров  -------------\n";
    cout << "    1 - Создать базу данных бытовой техникемобилей\n";
    cout << "    2 - Удалить базу данных бытовой техникемобилей\n";
    cout << "\n";
    cout << "-------------  Работа с записями товаров       -------------\n";
    cout << "    3 - Добавление записи о технике в базу\n";
    cout << "    4 - Редактирование записи\n";
    cout << "    5 - Удаление записи\n";
    cout << "    6 - Просмотр всей техники магазина\n";
    cout << "    7 - Поиск техники в каталоге\n";
    cout << "\n";
    cout << "-------------  Работа с учетными записями      -------------\n";
    cout << "    8 - Добавление учетной записи\n";
    cout << "    9 - Редактирование учетной записи\n";
    cout << "    10 - Удаление учетной записи\n";
    cout << "\n";
    cout << "    11 - Выход\n";
    cout << "\n";
    cout << "    Ваш выбор: ";
}

void PrintMenuManager()
{
    cout << "          Меню менеджера\n";
    cout << "\n";
    cout << "Пожалуйста укажите пункт\n";
    cout << "1 - Добавление записи о технике в базу\n";
    cout << "2 - Редактирование записи\n";
    cout << "3 - Удаление записи\n";
    cout << "4 - Просмотр всей техники магазина\n";
    cout << "5 - Поиск техники в каталоге\n";
    cout << "6 - Выход\n";
    cout << "Ваш выбор: ";
}

void PrintMenuUser()
{
    cout << "          Меню пользователя\n";
    cout << "\n";
    cout << "Пожалуйста укажите пункт\n";
    cout << "1 - Просмотр всей техники магазина\n";
    cout << "2 - Поиск техники в каталоге\n";
    cout << "3 - Оформление покупки\n";
    cout << "4 - Выход\n";
    cout << "Ваш выбор: ";
}

                            // функции работы c пользователями
                            
// запись данных в файла профиля
string WorkProfileFD(Profile user, bool rePass, bool del)
{
    ofstream fout;
    if (del)
    {
        string out;
        char* char_arr;
        string delUserName = user.name + ".txt";
        char_arr = &delUserName[0];
        if (remove(char_arr) != 0)
        {
            out = "    Ошибка удаления. Попробуйте вручную.\n";
        }
        else
        {
            if (user.level == 1) { out = "    Удален администратор " + user.name + "\n"; }
            if (user.level == 2) { out = "    Удален менеджер " + user.name + "\n"; }
            if (user.level == 3) { out = "    Удален пользователь " + user.name + "\n"; }
        }
        return out;
    }
    else
    {
        string reUserName = user.name + ".txt";
        if (rePass) { fout.open(reUserName, ios_base::trunc); }
        else { fout.open(reUserName, ios_base::app); }
        fout << user.name + "\n";
        fout << user.pass + "\n";
        fout << user.level;
        fout.close();
        string out;
        if (rePass)
        {
            if (user.level == 2) { out = "    Изменен пароль администратора " + user.name + "\n"; }
            if (user.level == 2) { out = "    Изменен пароль менеджера " + user.name + "\n"; }
            if (user.level == 3) { out = "    Изменен пароль пользователя " + user.name + "\n"; }
        }
        else
        {
            if (user.level == 2) { out = "    Создан администратор " + user.name + "\n"; }
            if (user.level == 2) { out = "    Создан менеджер " + user.name + "\n"; }
            if (user.level == 3) { out = "    Создан пользователь " + user.name + "\n"; }
        }
        return out;
    }

}

// сбор данных для пользователя
Profile GetNewProfileData(bool ifUser)
{
    bool ok = false;
    Profile fileUser;
    fileUser.name = getValueStr("    Введите имя объекта");
    fileUser.pass = getValueStr("    Введите пароль");
    if (!ifUser) {
        int i;
        while (ok == false)
        {
           i = getValueInt("    Введите уровень доступа:\n1 - Администратор\n2 - Менеджер\n3 - Пользователь\nВаш выбор: ");
           if (i == 1 || i == 2 || i == 3) { ok = true; }
           else { cout << "Введите одно из указанных значений" << endl; }
        }
        fileUser.level = i;
    }
    else { fileUser.level = 3; }
    return fileUser;
}

                            // функции получения значения с клавиатуры


int getValueInt(string mess)
{
    while (true)
    {
        cout << mess + "\n";
        int a;
        std::cin >> a;

        if (std::cin.fail())
        {
            std::cin.clear(); 
            std::cin.ignore(32767, '\n');
        }
        else 
            return a;
    }
}

string getValueStr(string mess)
{
    while (true) 
    {
        cout << mess << endl;
        std::string userStr;
        std::getline(std::cin >> std::ws, userStr);
        return userStr;
    }
}

                            // функции работы с файлом базы данных

// сортировка
// компараторы
bool comparareName(const Appliances lhs, const Appliances rhs) {
    if (varSort == 1) { return lhs.Appliancesequipment.name > rhs.Appliancesequipment.name; }
    else { return lhs.Appliancesequipment.name < rhs.Appliancesequipment.name; }
}
bool comparareType(const Appliances lhs, const Appliances rhs) {
    if (varSort == 1) {  return lhs.Appliancesequipment.type > rhs.Appliancesequipment.type; }
    else { return lhs.Appliancesequipment.type < rhs.Appliancesequipment.type; }
}
bool comparareCost(const Appliances lhs, const Appliances rhs) {
    if (varSort == 1) { return lhs.cost > rhs.cost; }
    else { return lhs.cost < rhs.cost; }
}
bool comparareId(const Appliances lhs, const Appliances rhs) {
    return lhs.id < rhs.id;
}
// сортировка по модели
void sortName() {
    sort( allAppliances.begin(),  allAppliances.end(), comparareName);
    if (varSort == 1) { varSort = 2; }
    else { varSort = 1; }
}
// сортировка по цвету
void sortType() {
    sort( allAppliances.begin(),  allAppliances.end(), comparareType);
    if (varSort == 1) { varSort = 2; }
    else { varSort = 1; }
}
// сортировка по стоимости
void sortCost() {
    sort( allAppliances.begin(),  allAppliances.end(), comparareCost);
    if (varSort == 1) { varSort = 2; }
    else { varSort = 1; }
}
// сортировка по id для упорядоченной записи в файл, а так же для автоматической нумерации id
void sortId() {
    sort( allAppliances.begin(),  allAppliances.end(), comparareId);
}

// делитель строки
vector<string> split(const string& s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) { result.push_back(item); }
    return result;
}

// запись данных нового бытовой технике в файл данных (перезапись файла)
bool creatRecordInFD(bool atMemory)
{
    if (atMemory)
    {
        vector<string> allString;
        sortId();
        for (Appliances wk :  allAppliances)
        {
            string outStrInterim = "";
            outStrInterim = outStrInterim + "#" + to_string(wk.id)
                + "#" + wk.Appliancesequipment.type
                + "#" + wk.Appliancesequipment.name
                + "#" + wk.Appliancesequipment.model
                + "#" + wk.Appliancesequipment.color
                + "#" + to_string(wk.cost)
                + "#" + wk.receipt_date
                + "#" + wk.buyer
                + "#" + wk.buyerEmail
                + "#" + wk.departure_date;
            allString.push_back(outStrInterim);
        }
        std::ofstream out("dataFile.txt", std::ios::trunc);
        if (out.is_open())
        {
            for (string strInFile : allString) { out << strInFile << std::endl; }
        }
        out.close();
        return true;
    }
    else
    {
        Appliances newAppliances = aggregationAppliancesData();
        string outStr = "";
        outStr = outStr + "#" + to_string(newAppliances.id)
            + "#" + newAppliances.Appliancesequipment.type
            + "#" + newAppliances.Appliancesequipment.name
            + "#" + newAppliances.Appliancesequipment.model
            + "#" + newAppliances.Appliancesequipment.color
            + "#" + to_string(newAppliances.cost)
            + "#" + newAppliances.receipt_date
            + "#" + newAppliances.buyer
            + "#" + newAppliances.buyerEmail
            + "#" + newAppliances.departure_date;
        std::ofstream out("dataFile.txt", std::ios::app);
        if (out.is_open()) {  out << outStr << std::endl; }
        out.close();
        return true;
    }

}

// принт таблицы файла данных
void printTable(bool managerOrAdmin, vector<Appliances> data, bool search)
{
    if (data.size() > 0)
    {
        Table AppliancessAll;
        if (managerOrAdmin) {
            AppliancessAll.add_row(Row_t{ "№ в базе", "Тип техники", "Производитель", "Модель", "Цвет корпуса",
                "Стоимость", "Дата поступления", "Имя покупателя", "Имейл покупателя", "Дата продажи" });
        }
        else
        {
            AppliancessAll.add_row(Row_t{ "№ в базе", "Тип техники", "Производитель", "Модель", "Цвет корпуса", "Стоимость" });
        }
        // добавление строк в таблицу
        int a = 0; // переменная для количества строк в таблице (если у пользователя был пропуск строк с проданным товаром)
        for (size_t i = 0; i < data.size(); i++)
        {
            // для админа и менеджера
            if (managerOrAdmin) {
                AppliancessAll.add_row(Row_t{
                    to_string(data[i].id),
                    data[i].Appliancesequipment.type,
                    data[i].Appliancesequipment.name,
                    data[i].Appliancesequipment.model,
                    data[i].Appliancesequipment.color,
                    to_string(data[i].cost),
                    data[i].receipt_date,
                    data[i].buyer,
                    data[i].buyerEmail,
                    data[i].departure_date
                    });
                ++a;
            }
            else
            {
                // для пользователя, если поле buyer пустое, то строку добавляем, иначе нет (имитация вида, что товар куплен)
                if (data[i].buyer == "") {
                    AppliancessAll.add_row(Row_t{
                        to_string(data[i].id),
                        data[i].Appliancesequipment.type,
                        data[i].Appliancesequipment.name,
                        data[i].Appliancesequipment.model,
                        data[i].Appliancesequipment.color,
                        to_string(data[i].cost)
                        });
                    
                }

            }
        }
        if (search)
        {
            // фраза ИТОГО для поиска
            if (managerOrAdmin) { AppliancessAll.add_row(Row_t{ "Найдено бытовой техники: ", to_string(data.size()), "", "", "", "", "", "", "", "" }); } // у админиа или менеджера
            else { AppliancessAll.add_row(Row_t{ "Найдено бытовой техники: ", to_string(data.size()), "", "", "", "" }); } // у пользователя
        }
        else 
        {
            // фраза ИТОГО для обычного вывода таблицы
            if (managerOrAdmin) { AppliancessAll.add_row(Row_t{ "Итого бытовой техники: ", to_string(data.size()), "", "", "", "", "", "", "", "" }); } // у админиа или менеджера
            else { AppliancessAll.add_row(Row_t{ "Итого бытовой техники: ", to_string(data.size()), "", "", "", "" }); } // у пользователя
            
        }

        AppliancessAll.column(0).format().font_align(FontAlign::center);
        AppliancessAll.column(1).format().font_align(FontAlign::center);
        AppliancessAll.column(2).format().font_align(FontAlign::center);
        AppliancessAll.column(3).format().font_align(FontAlign::center);
        AppliancessAll.column(4).format().font_align(FontAlign::center);
        AppliancessAll.column(5).format().font_align(FontAlign::center);
        if (managerOrAdmin) {
            AppliancessAll.column(6).format().font_align(FontAlign::center);
            AppliancessAll.column(7).format().font_align(FontAlign::center);
            AppliancessAll.column(8).format().font_align(FontAlign::center);
            AppliancessAll.column(9).format().font_align(FontAlign::center);
        }
        ++a; // всего строк посчитано было при добавлении, а выделить зеленым нужно дополнительную, поэтому инкрементируем на единицу
        if (managerOrAdmin) {
            for (size_t i = 0; i < 10; ++i) {
                AppliancessAll[0][i].format().font_color(Color::yellow).font_style({ FontStyle::bold });
                AppliancessAll[a][i].format().font_color(Color::green).font_style({ FontStyle::bold });
            }
        }
        else
        {
            for (size_t i = 0; i < 6; ++i) {
                AppliancessAll[0][i].format().font_color(Color::yellow).font_style({ FontStyle::bold });
                AppliancessAll[a][i].format().font_color(Color::green).font_style({ FontStyle::bold });
            }
        }
        std::cout << AppliancessAll << "\n\n";
    }
    else
    {
        cout << "                                               " << endl;
        cout << "          Записей не обнаружено.               " << endl;
        cout << "                                               " << endl;
    }
}

// функция поиска в строке
bool search(string query, string fundStr) {
    string queryDest;
    queryDest.resize(query.size());
    string fundStrDest;
    fundStrDest.resize(fundStr.size());
    transform(query.begin(), query.end(), queryDest.begin(), ::tolower);
    transform(fundStr.begin(), fundStr.end(), fundStrDest.begin(), ::tolower);
    size_t pos = fundStrDest.find(queryDest);
    if (pos != string::npos)
        return true;
    else
        return false;
}

// поиск бытовой технике и принт таблицы
void searchAndPrintTable(int change, bool managerOrAdmin)
{
    if ( allAppliances.size() > 0)
    {
        bool ok = false;
        string query;
        vector<Appliances> searchAppliancess;
        switch (change)
        {
        case 1:
            query = getValueStr("Введите тип бытовой технике");
            break;
        case 2:
            query = getValueStr("Введите производителя бытовой технике");
            break;
        }
        for (size_t i = 0; i <  allAppliances.size(); i++)
        {
            if (change == 1 && search(query,  allAppliances[i].Appliancesequipment.type)) { searchAppliancess.push_back( allAppliances[i]); }
            if (change == 2 && search(query,  allAppliances[i].Appliancesequipment.name)) { searchAppliancess.push_back( allAppliances[i]); }
        }
        if (searchAppliancess.size() > 0)
        {
            if (managerOrAdmin) { printTable(true, searchAppliancess, true); }
            else { printTable(false, searchAppliancess, true); }
        }
        else
        {
            cout << "                                               " << endl;
            cout << "          Записей не обнаружено.               " << endl;
            cout << "                                               " << endl;
        }
    }
    else
    {
        cout << "                                               " << endl;
        cout << "          Записей не обнаружено.               " << endl;
        cout << "                                               " << endl;
    }
}

// получение данных бытовой технике в память
void getAllAppliancesFD()
{
    int amountOfAppliances = 0;
    ifstream fin("dataFile.txt", ios_base::in);
    string line;
    vector<string> strs;
    if (!fin.is_open())
    {
        cout << "not" << endl;
        availabilityAppliances = false;
    }
    else
    {
        allAppliances.clear();
        while (getline(fin, line))
        {
            amountOfAppliances++;
            strs.push_back(line);
        }
        for (string u : strs)
        {
            vector<string> AppliancesVect = split(u, '#');
            Appliances interimAppliances;
            for (size_t i = 0; i < AppliancesVect.size(); i++)
            {
                switch (i)
                {
                case 1:
                    interimAppliances.id = stoi(AppliancesVect[i]);
                    break;
                case 2:
                    interimAppliances.Appliancesequipment.type = AppliancesVect[i];
                    break;
                case 3:
                    interimAppliances.Appliancesequipment.name = AppliancesVect[i];
                    break;
                case 4:
                    interimAppliances.Appliancesequipment.model = AppliancesVect[i];
                    break;
                case 5:
                    interimAppliances.Appliancesequipment.color = AppliancesVect[i];
                    break;
                case 6:
                    interimAppliances.cost = stoi(AppliancesVect[i]);
                    break;
                case 7:
                    interimAppliances.receipt_date = AppliancesVect[i];
                    break;
                case 8:
                    interimAppliances.buyer = AppliancesVect[i];
                    break;
                case 9:
                    interimAppliances.buyerEmail = AppliancesVect[i];
                    break;
                case 10:
                    interimAppliances.departure_date = AppliancesVect[i];
                    break;
                }
            }
             allAppliances.push_back(interimAppliances);
            if ( allAppliances.size() > 0) { availabilityAppliances = true; }
            else { availabilityAppliances = false; }
        }
    }
}

// изменение данных бытовой технике в памяти и перезапись в файл
bool changeAppliancesInMemory(bool userShop)
{
    int searchAppliancesLN = getValueInt("Введите номер бытовой технике в базе");
    int indexAppliances = -1;
    for (size_t i = 0; i <  allAppliances.size(); i++)
    {
        if ( allAppliances[i].id == searchAppliancesLN) { indexAppliances = i; } 
    }
    if (indexAppliances < 0) { return false; }
    if (userShop)
    {
        allAppliances[indexAppliances].buyer = userNameInProgramm;
        allAppliances[indexAppliances].buyerEmail = getValueStr("Укажите свой имейл");
        const time_t tm = time(NULL);
        char buf[64];
        strftime(buf, 64, "%d.%m.%Y", localtime(&tm));
        string todayDate = string(buf);
        allAppliances[indexAppliances].departure_date = todayDate;
    }
    else
    {
        Appliances newAppliances = aggregationAppliancesData();
        newAppliances.id = allAppliances[indexAppliances].id;
        allAppliances[indexAppliances] = newAppliances;
    }

    if (creatRecordInFD(true)) { return true; }
    else { return false; }
}

// удаление данных бытовой технике в памяти и перезапись в файл
bool deleteAppliancesInMemory()
{
    int searchAppliancesLN = getValueInt("Введите номер бытовой технике в базе");
    int indexAppliances = -1;
    auto iter =  allAppliances.cbegin();
    for (size_t i = 0; i <  allAppliances.size(); i++)
    {
        if ( allAppliances[i].id == searchAppliancesLN) { indexAppliances = i; } 
    }
    if (indexAppliances < 0) { return false; }
    allAppliances.erase(iter + indexAppliances);
    if (creatRecordInFD(true)) { return true; }
    else { return false; }
}

// сбор сведений по бытовой технике
Appliances aggregationAppliancesData() {
    Appliances newAppliances;
    sortId();
    if (allAppliances.size() == 0) { newAppliances.id = 1; }
    else { newAppliances.id = allAppliances[allAppliances.size() - 1].id + 1; }
    newAppliances.Appliancesequipment.type = getValueStr("Укажите тип бытовой технике");
    newAppliances.Appliancesequipment.name = getValueStr("Укажите производителя бытовой технике");
    newAppliances.Appliancesequipment.model = getValueStr("Укажите модель бытовой технике");
    newAppliances.Appliancesequipment.color = getValueStr("Укажите цвет бытовой технике");
    newAppliances.cost = getValueInt("Укажите стоимость бытовой технике");
    newAppliances.receipt_date = getValueStr("Укажите дату поступления");
    return newAppliances;
}

// проверка на наличие файла данных
bool SearchDataFile()
{
    ifstream fin("dataFile.txt", ios_base::in);
    if (!fin.is_open()) { return false; }
    else
    {
        fin.close();
        if (!availabilityAppliances) { getAllAppliancesFD(); }
        return true;
    }
}

// создание и удаление файла данных
bool CreateOrDeleteFD(bool createOrDelete)
{
    if (createOrDelete)
    {
        ofstream fout("dataFile.txt", ios_base::app);
        fout.close();
        return true;
    }
    else
    {
        if (remove("dataFile.txt") != 0) { return false; }
        else 
        { 
            allAppliances.clear();
            return true;
        }
    }
}

// провеерка файла админа
bool CreateOrDeleteAdminFile()
{
    ifstream fin("admin.txt", ios_base::in);
    if (!fin.is_open()) { return false; }
    else 
    { 
        fin.close();
        return true; 
    }
}

                                    // функции работы меню

void GetChoiceMenuAdmin()
{
    system("cls");
    if (!fileCreate) { cout << "Базы бытовой техники не существует" << endl; }
    bool file = SearchDataFile();
    bool ok = false;
    if (!SearchDataFile() && !choiceCreateFD)
    {
        bool ok = false;
        while (ok == false)
        {
            int continueAnsw = getValueInt("Создать файл данных? \n1 - Да\n2 - нет\n");
            if (continueAnsw == 1 || continueAnsw == 2)
            {
                if (continueAnsw == 1)
                {
                    if (CreateOrDeleteFD(true))
                    {
                        cout << "База бытовой техники успешно создана" << endl;
                        fileCreate = true;
                        system("pause");
                        GetChoiceMenuAdmin();
                    }
                    else
                    {
                        cout << "Ошибка при создании. Повторите попытку позже." << endl;
                        fileCreate = false;
                        system("pause");
                        GetChoiceMenuAdmin();
                    }
                    ok = true;
                }
                if (continueAnsw == 2)
                {
                    cout << "База бытовой техники не будет создана." << endl;
                    choiceCreateFD = true;
                    fileCreate = false;
                    system("pause");
                    GetChoiceMenuAdmin();
                }
            }
            else
            {
                cout << "Введите одно из указанных чисел.\n << endl";
            }
        }
    }
    else
    {
        PrintMenuAdmin();
        Profile newUser;
        Profile interimProfile;
        Profile fileUser;
        string out;
        string oldUserName;
        string varUser;
        int continueAnsw;
        bool ok = false;
        ifstream fin;
        int choice = getValueInt("Ваш выбор:");
        if ((choice == 3 && !fileCreate) || (choice == 4 && !fileCreate) || (choice == 5 && !fileCreate) || (choice == 6 && !fileCreate) || (choice == 7 && !fileCreate)) {
            cout << "Базы бытовой техники не существует" << endl;
            system("pause");
            GetChoiceMenuAdmin();
        }
        else
        {
            switch (choice)
            {
            case 1:
                system("cls");
                cout << "Создать базу бытовой техники" << endl;
                if (fileCreate)
                {
                    cout << "База данных существует" << endl;
                    system("pause");
                    GetChoiceMenuAdmin();
                }
                if (CreateOrDeleteFD(true))
                {
                    cout << "База данных успешно создана" << endl;
                    fileCreate = true;
                    system("pause");
                    GetChoiceMenuAdmin();
                }
                else
                {
                    cout << "Ошибка при создании. Повторите попытку позже." << endl;
                    fileCreate = false;
                    system("pause");
                    GetChoiceMenuAdmin();
                }
                break;
            case 2:
                system("cls");
                cout << "Удалить базу данных бытовой техники" << endl;
                if (CreateOrDeleteFD(false))
                {
                    cout << "База данных успешно удален" << endl;
                    choiceCreateFD = true;
                    fileCreate = false;
                    system("pause");
                    GetChoiceMenuAdmin();
                }
                else
                {
                    cout << "Ошибка при удалении. Повторите попытку позже." << endl;
                    if (SearchDataFile()) { fileCreate = true; }
                    else { fileCreate = false; }
                    system("pause");
                    GetChoiceMenuAdmin();
                }
                break;
            case 3:
                system("cls");
                cout << "Добавление записи о технике в базу" << endl;
                if (creatRecordInFD(false))
                {
                    getAllAppliancesFD();
                    cout << "Запись успешно добавлена" << endl;
                    getAllAppliancesFD();
                    system("pause");
                    GetChoiceMenuAdmin();
                }
                else
                {
                    cout << "Запись успешно добавлена" << endl;
                    system("pause");
                    GetChoiceMenuAdmin();
                }
                break;
            case 4:
                system("cls");
                cout << "Редактирование записи" << endl;
                sortId();
                printTable(true, allAppliances, false);
                if (changeAppliancesInMemory(false))
                {
                    cout << "Данные бытовой техники изменены" << endl;
                    system("pause");
                    GetChoiceMenuAdmin();
                }
                else
                {
                    cout << "Ошибка. Данные не изменены." << endl;
                    system("pause");
                    GetChoiceMenuAdmin();
                }
                break;
            case 5:
                system("cls");
                cout << "Удаление записи" << endl;
                sortId();
                printTable(true, allAppliances, false);
                if (deleteAppliancesInMemory())
                {
                    cout << "Запись о бытовой техники удалена." << endl;
                    system("pause");
                    GetChoiceMenuAdmin();
                }
                else
                {
                    cout << "Ошибка. Данные не изменены." << endl;
                    system("pause");
                    GetChoiceMenuAdmin();
                }
                break;
            case 6:
                system("cls");
                cout << "Просмотр всей техники магазина" << endl;
                sortId();
                printTable(true, allAppliances, false);
                if (availabilityAppliances) {
                    while (ok == false)
                    {
                        continueAnsw = getValueInt("Ваш действия?\n1 - Сортировка по производителю\n2 - Сортировка по типу\n3 - Сортировка по стоимости\n4 - Назад\n");
                        if (continueAnsw == 1 || continueAnsw == 2 || continueAnsw == 3 || continueAnsw == 4)
                        {
                            switch (continueAnsw)
                            {
                            case 1:
                                system("cls");
                                cout << "Сортировка по производителю\n" << endl;
                                sortName();
                                printTable(true, allAppliances, false);
                                continue;
                            case 2:
                                system("cls");
                                cout << "Сортировка по типу\n" << endl;
                                sortType();
                                printTable(true, allAppliances, false);
                                continue;
                            case 3:
                                system("cls");
                                cout << "Сортировка по стоимости\n" << endl;
                                sortCost();
                                printTable(true, allAppliances, false);
                                continue;
                            case 4:
                                GetChoiceMenuAdmin();
                                break;
                            default:
                                GetChoiceMenuAdmin();
                                break;
                            }
                        }
                        else { cout << "Введите одно из указанных чисел.\n" << endl; }
                    }
                }
                else
                {
                    system("pause");
                    GetChoiceMenuAdmin();
                }
                break;
            case 7:
                system("cls");
                cout << "  Поиск техники в каталоге" << endl;
                sortId();
                while (ok == false)
                {
                    continueAnsw = getValueInt("\nВарианты поиска?\n1 - По типу\n2 - По производителю\n3 - Назад\n4 - Выход\n");
                    if (continueAnsw == 1 || continueAnsw == 2 || continueAnsw == 3 || continueAnsw == 4) { ok = true; } 
                    else { cout << "Введите одно из указанных чисел.\n"; }
                }
                if (continueAnsw == 3) { GetChoiceMenuAdmin(); }
                if (continueAnsw == 4)
                {
                    cout << "Выход!";
                    exit(0);
                }
                searchAndPrintTable(continueAnsw, true);
                system("pause");
                GetChoiceMenuAdmin();
                break;
            case 8:
                system("cls");
                cout << "Добавление новой учетной записи" << endl;
                newUser = GetNewProfileData(false);
                fin.open(newUser.name, ios_base::in | std::ios::binary);
                if (!fin.is_open())
                {
                    while (ok == false)
                    {
                        continueAnsw = getValueInt("Продолжаем?\n1 - Да\n2 - нет\n");
                        if (continueAnsw == 1 || continueAnsw == 2) { ok = true; }
                        else  { cout << "Введите одно из указанных чисел.\n" << endl; }
                    }
                    if (continueAnsw == 1)
                    {
                        out = WorkProfileFD(newUser, false, false);
                        cout << out;
                        system("pause");
                        GetChoiceMenuAdmin();
                    }
                    if (continueAnsw == 2)
                    {
                        cout << "Операция прервана\n" << endl;
                        GetChoiceMenuAdmin();
                    }
                    ok = false;
                    break;
                }
                else
                {
                    fin.close();
                    cout << "Пользователь с таким логином существует.\n";
                    system("pause");
                    GetChoiceMenuAdmin();
                    ok = false;
                    break;
                }

            case 9:
                system("cls");
                cout << "Редактирование учетной записи" << endl;
                cout << "\n";
                oldUserName = getValueStr("    Введите имя учетной записи, которую желаете изменить");
                newUser.name = oldUserName;
                varUser = oldUserName + ".txt";
                fin.open(varUser, ios_base::in);
                if (!fin.is_open())
                {
                    cout << "    Пользователь с таким логином не найден.\n";
                    system("pause");
                    GetChoiceMenuAdmin();
                    ok = false;
                    break;
                }
                else
                {
                    fin.close();
                    ok = false;
                    while (ok == false)
                    {
                        continueAnsw = getValueInt("    Продолжаем?\n1 - Да\n2 - нет\n");
                        if (continueAnsw == 1 || continueAnsw == 2) { ok = true; }
                        else { cout << "    Введите одно из указанных чисел.\n"; }
                    }
                    if (continueAnsw == 1)
                    {
                        cout << "    Введите новые данные учетной записи\n";
                        interimProfile = GetNewProfileData(false);
                        out = WorkProfileFD(interimProfile, true, false);
                        cout << "    Учетная запись изменена\n";
                        if (varUser != interimProfile.name)
                        {
                            WorkProfileFD(newUser, false, true);
                        }
                        system("pause");
                        GetChoiceMenuAdmin();
                    }
                    if (continueAnsw == 2)
                    {
                        cout << "    Операция прервана\n";
                        GetChoiceMenuAdmin();
                    }
                    ok = false;
                    break;
                }
            case 10:
                system("cls");
                cout << "Удаление учетной записи" << endl;
                ok = false;
                while (ok == false)
                {
                    system("pause");
                    oldUserName = getValueStr("    Введите логин удаляемого объекта");
                    string interimFN = oldUserName + ".txt";
                    ifstream finn(interimFN, ios_base::in);
                    if (!finn.is_open()) { cout << "    Пользователь с таким логином не найден!\n"; }
                    else
                    {
                        finn.close();
                        ok = true;
                    }
                }
                ok = false;
                while (ok == false)
                {
                    continueAnsw = getValueInt("\nПродолжаем?\n1 - Да\n2 - нет\n");
                    if (continueAnsw == 1 || continueAnsw == 2) { ok = true; }
                    else { cout << "Введите одно из указанных чисел.\n"; }
                }
                if (continueAnsw == 1)
                {
                    newUser.name = oldUserName;
                    out = WorkProfileFD(newUser, false, true);
                    cout << out;
                    system("pause");
                    GetChoiceMenuAdmin();
                }
                if (continueAnsw == 2)
                {
                    cout << "    Операция прервана\n";
                    GetChoiceMenuAdmin();
                }

                break;
            case 11:
                cout << "Выход!";
                exit(0);
            default:
                GetChoiceMenuAdmin();
                break;
            }
        }
            
    }
   
}

void GetChoiceMenuManager()
{
    system("cls");
    if (!fileCreate)
    {
        cout << "Базы бытовой технике не существует" << endl;
        system("pause");
        cout << "Выход!\n";
        exit(0);
    }
    PrintMenuManager();
    int choice = getValueInt("Ваш выбор:");
    bool ok = false;
    int continueAnsw;
    switch (choice)
    {
    case 1:
        system("cls");
        cout << "Добавление записи о технике в базу" << endl;
        if (creatRecordInFD(false))
        {
            getAllAppliancesFD();
            cout << "Запись успешно добавлена" << endl;
            getAllAppliancesFD();
            system("pause");
            GetChoiceMenuManager();
        }
        else
        {
            cout << "Запись успешно добавлена" << endl;
            system("pause");
            GetChoiceMenuManager();
        }
        break;
    case 2:
        system("cls");
        cout << "Редактирование записи" << endl;
        sortId();
        printTable(true, allAppliances, false);
        if (changeAppliancesInMemory(false))
        {
            cout << "Данные бытовой технике изменены" << endl;
            system("pause");
            GetChoiceMenuManager();
        }
        else
        {
            cout << "Ошибка. Данные не изменены." << endl;
            system("pause");
            GetChoiceMenuManager();
        }
        break;
    case 3:
        system("cls");
        cout << "Удаление записи" << endl;
        sortId();
        printTable(true, allAppliances, false);
        if (deleteAppliancesInMemory())
        {
            cout << "бытовой технике удалено." << endl;
            system("pause");
            GetChoiceMenuManager();
        }
        else
        {
            cout << "Ошибка. Данные не изменены." << endl;
            system("pause");
            GetChoiceMenuManager();
        }
        break;
    case 4:
        system("cls");
        cout << "Просмотр всей техники магазина" << endl;
        sortId();
        printTable(true, allAppliances, false);
        if (availabilityAppliances) {
            while (ok == false)
            {
                continueAnsw = getValueInt("Ваш действия?\n1 - Сортировка по производителю\n2 - Сортировка по типу\n3 - Сортировка по стоимости\n4 - Назад\n");
                if (continueAnsw == 1 || continueAnsw == 2 || continueAnsw == 3 || continueAnsw == 4)
                {
                    switch (continueAnsw)
                    {
                    case 1:
                        system("cls");
                        cout << "Сортировка по производителю\n" << endl;
                        sortName();
                        printTable(true, allAppliances, false);
                        continue;
                    case 2:
                        system("cls");
                        cout << "Сортировка по типу\n" << endl;
                        sortType();
                        printTable(true, allAppliances, false);
                        continue;
                    case 3:
                        system("cls");
                        cout << "Сортировка по стоимости\n" << endl;
                        sortCost();
                        printTable(true, allAppliances, false);
                        continue;
                    case 4:
                        GetChoiceMenuManager();
                        break;
                    default:
                        GetChoiceMenuManager();
                        break;
                    }
                }
                else { cout << "Введите одно из указанных чисел.\n" << endl; }
            }
        }
        else
        {
            system("pause");
            GetChoiceMenuManager();
        }
        break;
    case 5:
        system("cls");
        cout << "  Поиск техники в каталоге" << endl;
        sortId();
        while (ok == false)
        {
            continueAnsw = getValueInt("\nВарианты поиска?\n1 - По типу\n2 - По производителю\n3 - Назад\n4 - Выход\n");
            if (continueAnsw == 1 || continueAnsw == 2 || continueAnsw == 3 || continueAnsw == 4) { ok = true; }
            else { cout << "Введите одно из указанных чисел.\n"; }
        }
        if (continueAnsw == 3) { GetChoiceMenuManager(); }
        if (continueAnsw == 4)
        {
            cout << "Выход!";
            exit(0);
        }
        searchAndPrintTable(continueAnsw, true);
        system("pause");
        GetChoiceMenuManager();
        break;
    case 6:
        cout << "Выход!";
        exit(0);
    default:
        GetChoiceMenuManager();
        break;
    }
}

void GetChoiceMenuUser()
{
    system("cls");    
    if (!fileCreate || !availabilityAppliances)
    {
        cout << "     Базы бытовой техники не существует" << endl;
        cout << "       или записей не обнаружено" << endl;
        system("pause");
        cout << "Выход!\n";
        exit(0);
    }
    PrintMenuUser();
    int choice = getValueInt("Ваш выбор:");
    bool ok = false;
    int continueAnsw;
    switch (choice)
    {
    case 1:
        system("cls");
        cout << "Просмотр всей техники магазина" << endl;
        sortId();
        printTable(false, allAppliances, false);
        if (availabilityAppliances) {
            while (ok == false)
            {
                continueAnsw = getValueInt("Ваш действия?\n1 - Сортировка по производителю\n2 - Сортировка по типу\n3 - Сортировка по стоимости\n4 - Назад\n");
                if (continueAnsw == 1 || continueAnsw == 2 || continueAnsw == 3 || continueAnsw == 4)
                {
                    switch (continueAnsw)
                    {
                    case 1:
                        system("cls");
                        cout << "Сортировка по производителю\n" << endl;
                        sortName();
                        printTable(false, allAppliances, false);
                        continue;
                    case 2:
                        system("cls");
                        cout << "Сортировка по типу\n" << endl;
                        sortType();
                        printTable(false, allAppliances, false);
                        continue;
                    case 3:
                        system("cls");
                        cout << "Сортировка по стоимости\n" << endl;
                        sortCost();
                        printTable(false, allAppliances, false);
                        continue;
                    case 4:
                        GetChoiceMenuUser();
                        break;
                    default:
                        GetChoiceMenuUser();
                        break;
                    }
                }
                else { cout << "Введите одно из указанных чисел.\n" << endl; }
            }
        }
        else
        {
            system("pause");
            GetChoiceMenuUser();
        }
        break;
    case 2:
        system("cls");
        cout << "  Поиск техники в каталоге" << endl;
        sortId();
        while (ok == false)
        {
            continueAnsw = getValueInt("\nВарианты поиска?\n1 - По типу\n2 - По производителю\n3 - Назад\n4 - Выход\n");
            if (continueAnsw == 1 || continueAnsw == 2 || continueAnsw == 3 || continueAnsw == 4) { ok = true; }
            else { cout << "Введите одно из указанных чисел.\n"; }
        }
        if (continueAnsw == 3) { GetChoiceMenuUser(); }
        if (continueAnsw == 4)
        {
            cout << "Выход!";
            exit(0);
        }
        searchAndPrintTable(continueAnsw, false);
        system("pause");
        GetChoiceMenuUser();
        break;
    case 3:
        system("cls");
        cout << "Оформление покупки" << endl;
        sortId();
        printTable(false, allAppliances, false);
        if (changeAppliancesInMemory(true))
        {
            cout << "Покупка успешна. Заказ оформлен на пользователя  " << userNameInProgramm << endl;
            system("pause");
            GetChoiceMenuUser();
        }
        else
        {
            cout << "Ошибка. Покупка не возможна. Обратитесь к  администратору." << endl;
            system("pause");
            GetChoiceMenuUser();
        }
        break;
    case 4:
        cout << "Выход!";
        exit(0);
    default:
        GetChoiceMenuUser();
        break;
    }

}

int main(int argc, char* argv[])
{
    // установка локали
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    fileCreate = SearchDataFile();
    // проверка фала админа
    if (!CreateOrDeleteAdminFile())
    {
        int continueAnsw;
        bool ok = false;
        Profile admin;
        string out;
        while (ok == false)
        {
            system("cls");
            cout << " ===================================================" << endl;
            cout << "              Администратор не обнаружен            " << endl;
            cout << "===================================================" << endl;
            continueAnsw = getValueInt("    Создать админа?\n1 - Да\n2 - нет\n");
            if (continueAnsw == 1 || continueAnsw == 2)
            {
                switch (continueAnsw)
                {
                case 1:
                    admin.name = "admin";
                    admin.pass = "pass";
                    admin.level = 1;
                    out = WorkProfileFD(admin, false, false);
                    cout << out;
                    cout << "\n    Логин для входа: admin\n";
                    cout << "\n    Пароль для входа: pass\n";
                    system("pause");
                    ok = true;
                    break;
                case 2:
                    cout << "    Выход!\n";
                    exit(0);
                default:
                    cout << "    Выход!\n";
                    exit(0);
                }
            }
            else { cout << "    Введите одно из указанных чисел.\n" << endl; }
        }
    }
    // отображение меню выбора пользователя
    PrintMenuMain();
    // нужные переменные
    int continueAnsw;
    bool ok = false;
    string out;
    bool okTwo = false;
    string fileLogin;
    string filePass;
    int profile = 0;
    int i = 1;
    while (ok == false)
    {
        continueAnsw = getValueInt("Ваш выбор:\n");
        if (continueAnsw == 1 || continueAnsw == 2 || continueAnsw == 3)
        { 
            while (okTwo == false)
            {
                if (i == 1)
                {
                    system("cls");
                    string name = getValueStr("Введите логин:");
                    std::ifstream openFile(name + ".txt", std::ios::in);
                    if (!openFile.is_open())
                    {
                        cout << "Пользователь с таким логином не найден!\n";
                        int continueAnswInterim;
                        bool okContin = false;
                        if (continueAnsw == 2 || continueAnsw == 1)
                        {
                            bool choiceLoginStep = false;
                            while (choiceLoginStep == false)
                            {
                                continueAnsw = getValueInt("Ваш выбор:\n1 - Повторить ввод логина\n2 - Выход\n");
                                if (continueAnsw == 1 || continueAnsw == 2) { choiceLoginStep = true; }
                                else { cout << "Введите одно из указанных чисел.\n" << endl; }
                            }
                            if (continueAnsw == 2)
                            {
                                cout << "Выход\n" << endl;
                                system("pause");
                                exit(0);
                            }
                        }
                        if (continueAnsw == 3)
                        {
                            while (okContin == false)
                            {
                                continueAnswInterim = getValueInt("1 - Зарегистрировать пользователя\n2 - Ввести другой логин\n3 - Выйти\n");
                                if (continueAnswInterim == 1 || continueAnswInterim == 2 || continueAnswInterim == 3) { okContin = true; }
                                else { cout << "Введите одно из указанных чисел.\n" << endl; }
                            }

                            if (continueAnswInterim == 1) {
                                Profile newUser;
                                string out;
                                int continueAnsw;
                                bool okCreatProf = false;
                                ifstream fin;
                                cout << "Добавление новой пользователя" << endl;
                                newUser = GetNewProfileData(true);
                                fin.open(newUser.name + ".txt", ios_base::in);
                                if (!fin.is_open())
                                {
                                    while (okCreatProf == false)
                                    {
                                        continueAnsw = getValueInt("Продолжаем?\n1 - Да\n2 - нет\n");
                                        if (continueAnsw == 1 || continueAnsw == 2) { okCreatProf = true; }
                                        else { cout << "Введите одно из указанных чисел.\n" << endl; }
                                    }
                                    if (continueAnsw == 1)
                                    {
                                        out = WorkProfileFD(newUser, false, false);
                                        profile = newUser.level;
                                        cout << out;
                                        system("pause");
                                        okTwo = true;
                                    }
                                    if (continueAnsw == 2)
                                    {
                                        cout << "Операция прервана\n" << endl;
                                        system("pause");
                                    }
                                }
                                else
                                {
                                    fin.close();
                                    cout << "Пользователь с таким логином существует.\n";
                                    system("pause");
                                }
                            }
                            if (continueAnswInterim == 3)
                            {
                                cout << "Операция прервана\n" << endl;
                                system("pause");
                                exit(0);
                            }
                        }
                        
                    }
                    else
                    {
                        string line;
                        int j = 1;
                        while (getline(openFile, line))
                        {
                            if (j == 1) { fileLogin = line; }
                            if (j == 2) { filePass = line; }
                            if (j == 3) { profile = stoi(line); }
                            j++;
                        }
                        openFile.close();
                        i = 2;
                    }
                }
                if (i == 2)
                {
                    system("cls");
                    string pass = getValueStr("Введите пароль:");
                    if (pass == filePass) { okTwo = true; }
                    else
                    {
                        cout << "Ошибка пароля. Повторите ввод.\n";
                        int continueAnsw;
                        bool okContin = false;
                        while (okContin == false)
                        {
                            continueAnsw = getValueInt("Продолжаем?\n1 - Да\n2 - нет\n");
                            if (continueAnsw == 1 || continueAnsw == 2) { okContin = true; }
                            else { cout << "Введите одно из указанных чисел.\n" << endl; }
                        }
                        if (continueAnsw == 2)
                        {
                            cout << "Операция прервана\n" << endl;
                            system("pause");
                            exit(0);
                        }
                    }
                }
            }
            if (profile == 1) { GetChoiceMenuAdmin(); }
            if (profile == 2) { GetChoiceMenuManager(); }
            if (profile == 3) 
            { 
                userNameInProgramm = fileLogin; 
                GetChoiceMenuUser(); 
            }
        }
        else if (continueAnsw == 4)
        {
            cout << "Выход!\n";
            system("pause");
            exit(0);
        }
        else { cout << "Введите одно из указанных чисел.\n" << endl; }
    }
}