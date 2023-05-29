/*****************************************************************************
Дан следующий код.
#include <string>
#include <iostream>
#include <vector>
 
 
class A{
public:
string s;
A() {
cout << "Конструктор по умолчанию класса А" << endl;
}
 
A(const char*a) {
s=a;
cout << "Пользовательский Конструктор класса A" << endl;
cout << s << endl;
}
virtual ~A() {
cout << "Деструктор класса A" << endl;
cout<<typeid(*this).name()<<endl;
}
};
 
class B : public A{
public:
B() {
cout << "Конструктор  класса B" << endl;
}
B(const char* a):A(a) {
cout << "Пользовательский Конструктор класса B" << endl;
cout << a << endl;
}
~B() {
cout << "Деструктор класса B" << endl;
cout<<typeid(*this).name()<<endl;
}
};
 
void del(vector<A*> v){
for (int i = 0; i < v.size(); i++)
delete v[i];
}
 
vector<A*>v;
list <A*> l
 
int main(){
l.push_back(new A("first"));
l.push_back(new B("second"));
// скопировать из списка в вектор
 del(v);
return 0;
}
Добавить копирование из списка в вектор. Исправить, если есть, ошибки. Определить, есть ли утечки памяти. И если есть, исправить программу, чтобы их не было.
*************************************************************************************************************************************************************/

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class A {
public:
	const string s;
	A() {
		cout << "Конструктор по умолчанию класса А" << endl;
	}

	A(const char* a) : s(a) {
		cout << "Пользовательский Конструктор класса A" << endl;
		cout << s << endl;
	}

	A(const A& obj) : s(obj.s) {}
	virtual A* clone() {
		return new A(*this);
	}
	virtual ~A() {
		cout << "Деструктор класса A" << endl;
		cout << typeid(*this).name() << endl;
	}
};

class B final : public A {
public:
	B() {
		cout << "Конструктор класса B" << endl;
	}
	B(const char* a) :A(a) {
	}
	B(const B& obj) : A(obj) {};
	B* clone() override {
		return new B(*this);
	}
	~B() {
	}
};

template<class T>
void del(const T& v) {
	for (auto& i : v)
		delete i;
}

int main() {
	setlocale(LC_ALL, "ru");
	list <A*> l;
	vector<A*> v;
	l.push_back(new A("first"));
	l.push_back(new B("second"));
	for (auto i : l) {
		v.push_back(i->clone());
	}

	{
		for (auto& i : l)
			cout << i << " ";
		cout << '\n';
		for (auto& i : v)
			cout << i << " ";
		cout << '\n';
	}

	del(v);
	del(l);

	l.clear();
	v.clear();
}