/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- *
Открыть консольное приложение.
Задать два не абстрактных класса, связанных в полиморфную иерархию : Class1(базовый) и Class2.В главной функции программы создать несколько автоматических объектов этих типов.
Затем посредством вызова функции my_copy скопировать эти объекты в базу данных(использовать vector), т.е.в базе данных должны оказаться копии созданных автоматических объектов.
Далее, вывести на консоль информацию о типах хранимых в БД объектах, используя typeid.
Исключить утечку памяти.
* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <vector>
#include <typeinfo>
#include <crtdbg.h>


//првоерка утечки данных
struct Leaks {
	~Leaks() {
		_CrtDumpMemoryLeaks();
	}
}_leaks;

class Class1
{
public:
	Class1() {}
	virtual ~Class1() {}
	virtual void print() {
		std::cout << "Class1" << std::endl;
	}
};

class Class2 : public Class1
{
public:
	Class2() {}
	virtual ~Class2() {}
	virtual void print() {
		std::cout << "Class2" << std::endl;
	}
};


//Функия копирования
void my_copy(Class1* obj, std::vector<Class1*>& DB)
{
	Class1* copy = 0;
	if (dynamic_cast<Class2*>(obj)) {
		copy = new Class2(*dynamic_cast<Class2*>(obj));
	}
	else {
		copy = new Class1(*dynamic_cast<Class1*>(obj));
	}
	DB.push_back(copy);
}


int main()
{

	// Создание автоматических объектов классов
	Class1* obj_1 = new Class1();
	Class1* obj_2 = new Class1();
	Class1* obj_3 = new Class2();
	Class1* obj_4 = new Class2();

	std::vector<Class1*> DB;	// База данных

	// Копирование в базу данных
	my_copy(obj_1, DB);
	my_copy(obj_2, DB);
	my_copy(obj_3, DB);
	my_copy(obj_4, DB);

	// Вывод информации из DB и одновременная очистка памяти
	for (int i = 0; i < DB.size(); i++)
	{
		std::cout << typeid(*DB[i]).name() << std::endl;
		delete DB[i];
	}
}