/*************************************************************************************************************************************************************
Задать два иерархически связанных полиморфных класса: деталь и сборка (один из них базовый). Все конструкторы находятся в зоне protected (чтобы запретить явное 
создание). В main() следует создать несколько экземпляров указанных типов, помещая их в хранилище (vector), используя шаблонную дружественную функцию. 
Дополнить программу всем необходимым для ее правильной работы.
*************************************************************************************************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Detail {
protected:
    Detail() {}
public:
    virtual ~Detail() {}
    template<typename T>
    friend void add_object(vector<Detail*>& object);
};

class Build : public Detail {
protected:
    Build() = default;
public:
    virtual ~Build() {}
    template<typename T>
    friend void add_object(vector<Detail*>& object);
};

template<typename T>
void add_object(vector<Detail*>& object) {
    object.push_back(new T());
}

int main() {
    vector<Detail*> storage;
    add_object<Detail>(storage);
    add_object<Build>(storage);
    add_object<Detail>(storage);
    add_object<Build>(storage);

    for (auto i : storage) {
        delete i;
    }
    storage.clear();
}