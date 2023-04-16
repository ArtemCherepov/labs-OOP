/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- *
Вручную создать текстовый файл со следующей информацией: в две колонки, разделяя их пробелом, марка машины — модель. Например: Мерседес 320. (всего примерно 10 строк в
файле, марка и модель могут повторяться). В программе загрузить файл, распределяя данные по объектам, тип которых соответствует марке автомобиля, а модель — член данных
в базовом классе. Храниться объекты должны совместно, используя контейнер vector. Вывести данные о модели и марке каждого автомобиля при выходе из программы.
(Подсказка: в деструкторах).
* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#include <iostream>
#include <fstream>
#include <vector>

// Иерархия наследования
class Car
{
protected:
    std::string model_;

public:
    Car() {}
    virtual ~Car() {}
};

class Lamborgini : public Car
{
public:
    Lamborgini(const std::string& model)
    {
        model_ = model;
    }
    virtual ~Lamborgini()
    {
        std::cout << "Lamborgini " << model_ << std::endl;
    }
};

class Porche : public Car
{
public:
    Porche(const std::string& model)
    {
        model_ = model;
    }
    virtual ~Porche()
    {
        std::cout << "Porche " << model_ << std::endl;
    }
};


class BMW : public Car
{
public:
    BMW(const std::string& model)
    {
        model_ = model;
    }
    virtual ~BMW()
    {
        std::cout << "BMW " << model_ << std::endl;
    }
};

class Mercedes : public Car
{
public:
    Mercedes(const std::string& model)
    {
        model_ = model;
    }
    virtual ~Mercedes()
    {
        std::cout << "Mercedes " << model_ << std::endl;
    }
};

class Ferrari : public Car
{
public:
    Ferrari(const std::string& model)
    {
        model_ = model;
    }
    virtual ~Ferrari()
    {
        std::cout << "Ferrari " << model_ << std::endl;
    }
};

int main()
{
    std::ifstream file;
    file.open("C:\\Users\\artem\\OneDrive\\Рабочий стол\\Станкин\\2 СЕМЕСТР\\1 модуль\\ООП\\лабы\\laba1\\cars.txt");

    std::string Brand;
    std::string Model;

    std::vector<Car*> storage;

    while (!file.eof())
    {
        file >> Brand;
        if ((Brand == "\n") || (Brand == " ")) {
            Brand = {};
            continue;
        }
        else if (Brand == "Porche")
        {
            file >> Model;
            storage.push_back(new Porche(Model));
        }
        else if (Brand == "Lamborgini")
        {
            file >> Model;
            storage.push_back(new Lamborgini(Model));
        }
        else if (Brand == "BMW")
        {
            file >> Model;
            storage.push_back(new BMW(Model));
        }
        else if (Brand == "Mercedes")
        {
            file >> Model;
            storage.push_back(new Mercedes(Model));
        }
        else if (Brand == "Ferrari")
        {
            file >> Model;
            storage.push_back(new Ferrari(Model));
        }
    }

    file.close();

    for (int i = 0; i < storage.size(); ++i)
    {
        delete storage[i];
    }
}