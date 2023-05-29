﻿/**************************************************************************************************************************************************************
Вам принесли файл со сторонней информацией. В этом файле следующий построчный текст (ФИО, год рождения, должность, структурная единица):
Иванов Н.М. 1998, инженер, группа 1
Петров П.И. 1999, инженер, группа 2
Плетнев И.С. 2001, лаборант, группа 4
Гаврилов Т.Г. 1976, техник, группа 1
Бойко А.Л. 1969, председатель, группа 1
Медведев Д.С. 2000, лаборант, группа 3
Анисин Н.М. 1966, председатель, группа 2
Петров П.П. 1971, председатель, группа 3
Андрианов М.С. 1999, лаборант, группа 1
Бердыев А.Г. 1955, председатель, группа 4
Нефедов А.Л. 1992, техник, группа 4
Чугунин И.У. 2001, лаборант, группа 2
Семенов Е.С. 1994, техник, группа 2
Панин Р.Г. 1995, техник, группа 3
Парфенов А.Л. 1998, инженер, группа 4
Буч Г.Г. 1996, инженер, группа 3
Загрузить файл, наполняя созданную БД (в стиле ООП) элементами из файла.
Вывести на консоль данные о всех инженерах, а затем в порядке возрастания года рождения данные о всех не председателях. Использовать лямбду.
Не забывать освобождать ресурсы.
*************************************************************************************************************************************************************/

#include <crtdbg.h>
#include <iostream>  
#include <fstream>  
#include <string>  
#include <vector>  
#include <sstream>  
#include <algorithm>

using namespace std;

struct Leaks {
    ~Leaks() { _CrtDumpMemoryLeaks(); }
}_l;

class Employee {
private:
    const string _name;
    const int _yearOfBirth;
    const string _position;
    int _groupNumber;
public:
    Employee(const string& n, const int& y, const string& p, const int& g) : _name(n), _yearOfBirth(y), _position(p), _groupNumber(g) {}

    int getBirthYear() const {
        return _yearOfBirth;
    }
    string getPosition() const {
        return _position;
    }
    void printInfo() const {
        cout << _name << ", " << _yearOfBirth << ", " << _position << ", " << "группа " << _groupNumber << endl;

    }
};

class Database {
private:
    vector<Employee*> employees;
public:
    void addEmployee(Employee* e) {
        employees.push_back(e);
    }

    void printAllEmployees() const {
        for (const auto& employee : employees) {
            employee->printInfo();
        }
    }

    void printAllEngineers() const {
        for_each(employees.begin(), employees.end(), [](const Employee* e) {
            if (e->getPosition() == "инженер") {
                e->printInfo();
            }
            });
    }
    void printAllNonPresidents() const {
        vector<Employee*> nonPresidents;
        for (const auto& employee : employees) {
            if (employee->getPosition() != "председатель") {
                nonPresidents.push_back(employee);
            }
        }
        sort(nonPresidents.begin(), nonPresidents.end(), [](const Employee* a, const Employee* b) {
            return a->getBirthYear() < b->getBirthYear();
            });

        for (const auto& employee : nonPresidents) {
            employee->printInfo();
        }
    }
    ~Database() {
        for (const auto& employee : employees) {
            delete employee;
        }
    }
};
int main() {
    setlocale(LC_ALL, "RUS");
    Database db;
    string _name, _position, _group;
    int _yearOfBirth, _groupNumber;
    string path = "bd.txt";
    ifstream file;
    file.open(path);
    if (!file.is_open()) {
        cout << "Ошибка" << endl;
    }
    else
    {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, _name, ',');
            ss >> _yearOfBirth >> ws;
            getline(ss, _position, ',');
            ss >> _group >> ws;
            ss >> _groupNumber;
            Employee* e = new Employee(_name, _yearOfBirth, _position, _groupNumber);
            db.addEmployee(e);
        }
        file.close();
    }
    cout << "Общая база данных:" << endl;
    cout << endl;
    db.printAllEmployees();
    cout << "*******************************************************************************************" << endl;
    cout << "Информация об инженерах:" << endl;
    cout << endl;
    db.printAllEngineers();
    cout << "*******************************************************************************************" << endl;
    cout << "Информация о всех не председателях:" << endl;
    cout << endl;
    db.printAllNonPresidents();
}