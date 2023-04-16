/*
* ---------------------------------------------------------------------------------------------------------------------------- *
    Библиотека, в ней хранятся два вида книг. Художественные и технические. Создать программу, в которой:
    А) Наполнить библиотеку несколькими разными книгами
        Примечание 1: у пользовательского конструктора класса дложно быть 3 параметра - для указания автора, названия, типа
        Примечание 2: в библиотеке не должно быть книг без автора и названия
    Б) В отдельной процедуре вывести на консоль, использую switch, кол-во художественной литературы и технической
    В) В дополнительной процедуре сделать тоже самое, на без switch
    Следить за утечками.
* ---------------------------------------------------------------------------------------------------------------------------- *
*/


#include <iostream>
#include <vector>

// Перечисление для определения типа книги
enum class Type
{
    Art, Tech
};

// Класс книга
class Book
{
public:
    // Конструктор для инициализации
    Book(const std::string& author, const std::string& bookName, Type bookType) :
        author_{ author }, bookName_{ bookName }, bookType_{ bookType } {}


    // Метод для взятия типа книги
    const Type getType() const
    {
        return bookType_;
    }

private:
    const std::string author_;
    const std::string bookName_;
    const Type bookType_;
};

class Library {
public:
    void AddBook(std::string author, std::string bookName, Type bookType)
    {
        if (author.empty() || bookName.empty())
        {
            std::cout << "Ошибка! Книга не имеет автора или названия\n";
        }
        else
        {
            _library.emplace_back(author, bookName, bookType);
        }


    }
    void countSwitch()
    {
        short countArt = 0;
        short countTech = 0;

        for (const Book& book : _library)
        {
            const Type bookType = book.getType();

            switch (bookType)
            {
            case Type::Art:
                countArt += 1;
                break;

            case Type::Tech:
                countTech += 1;
                break;
            }
        }
        std::cout << "------------------------------------------------------\n";
        std::cout << "Количество художественных книг (switch):\t" << countArt << "\n";
        std::cout << "Количество технических книг (switch):\t\t" << countTech << "\n";
    }

    void countIf()
    {
        short countArt = 0;
        short countTech = 0;

        for (const Book& book : _library)
        {
            const Type bookType = book.getType();

            if (bookType == Type::Art)
            {
                countArt += 1;
            }
            if (bookType == Type::Tech)
            {
                countTech += 1;
            }
        }
        std::cout << "------------------------------------------------------\n";
        std::cout << "Количество художественных книг (if):\t\t" << countArt << "\n";
        std::cout << "Количество технических книг (if):\t\t" << countTech << "\n";
    }
private:
    std::vector<Book> _library;
};


int main()
{
    setlocale(LC_ALL, "ru");

    Library library;

    //добавление книг
    library.AddBook("Джек Лондон", "Мартин Иден", Type::Art);
    library.AddBook("А. С. Пушкин", "Капитанская дочка", Type::Art);
    library.AddBook("Д. А. Глуховский", "метро 2033", Type::Art);
    library.AddBook("Бьёрн Страуструп", "Язык программирования С++", Type::Tech);
    library.AddBook("Н. Б. Культин", "C/C++ в задачах и примерах ", Type::Tech);

    library.AddBook("", "D", Type::Art);
    library.AddBook("D", "", Type::Art);

    library.countSwitch();
    library.countIf();
    std::cout << "------------------------------------------------------\n";
}
