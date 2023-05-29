﻿/*************************************************************************************************************************************************************
Пусть в некоей научной статье есть список литературы:
Литература:
1. Moore, J. L., Dickson-Deane, C., & Galyen, K. (2011). e-Learning, online learning, and distance learning environments: Are they the same?. The Internet and Higher Education, 14(2), 129-135.
2. Cinquin, P. A., Guitton, P., & Sauzéon, H. (2019). Online e-learning and cognitive disabilities: A systematic review. Computers & Education, 130, 152-167.
3. Maslow, A. H. (1966). The psychology of science a reconnaissance.
4. Harvey, O. J., Hunt, D. E., & Schroder, H. M. (1961). Conceptual systems and personality organization.
5. Wood, J., & BacKWell, J. (2012). harnessing hidden knowledge for paradigm change. Journal of Writing in Creative Practice, 5(3), 477-497.
6. García, M. L. (2008). Closed Groups, Hidden Knowledge. An Anthropological Perspective.
7. Madsen, E. S., Riis, J. O., & Waehrens, B. V. (2008). The knowledge dimension of manufacturing transfers. Strategic Outsourcing: An International Journal.
8. Fershtman, C., & Gandal, N. (2011). Direct and indirect knowledge spillovers: the “social network” of open‐source projects. The RAND Journal of Economics, 42(1), 70-91.
9. Маслоу А.Г. Мотивация и личность. М., 2000. 225 с.
10. Toivonen, S., Lenzini, G., & Uusitalo, I. (2006, November). Context-aware trustworthiness evaluation with indirect knowledge. In Proc. of the 2nd International Semantic Web Policy Workshop (SWPW).
11. Eraut, M. (2000). Non-formal learning and tacit knowledge in professional work. British journal of educational psychology, 70(1), 113-136.
12. Mortensen, M., & Neeley, T. B. (2012). Reflected knowledge and trust in global collaboration. Management Science, 58(12), 2207-2224.
13. Ушинский, К. Д. Педагогика. Избранные работы, М. Юрайт, 2017, 284 с.
14. Wright, J. C., & Mischel, W. (1988). Conditional hedges and the intuitive psychology of traits. Journal of personality and social psychology, 55(3), 454.
Однако при подаче этой статьи в журнал у редакторов этого журнала возникла претензия: ссылки на источники отсортированы не по алфавиту.
Задача: добиться, чтобы все источники были в отсортированном по алфавиту порядке, при этом сперва должны идти источники на русском языке, а затем — на английском.
Также должны быть две формы печати с числами и без них. Использовать лямбду или функтор.
*************************************************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

struct Structur {
    std::string author;
    std::string title;
    std::string year;
    std::string pages;
};

bool Rus(char ch) {

    if (ch >= 0 && ch <= 127) {
        return false;
    }
    return true;
}

void printStructur(const std::vector<Structur>& Structur, bool withNumbers) {
    for (size_t i = 0; i < Structur.size(); i++) {
        if (withNumbers) {
            std::cout << i + 1 << ". ";
        }
        std::cout << Structur[i].author << " " << Structur[i].year << ". " << Structur[i].title << " " << Structur[i].pages << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    std::vector <Structur> structur;
    std::ifstream file("bd.txt");
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string author, title, year, pages;
        std::istringstream iss(line);
        std::getline(iss, author, ',');
        std::getline(iss, year, ',');
        std::getline(iss, title, ',');
        iss >> pages;
        Structur ref = { author, title, year, pages };
        structur.push_back(ref);
    }
    file.close();


    sort(structur.begin(), structur.end(), [](const Structur& a, const Structur& b) {

        if (Rus(a.author[0]) && !Rus(b.author[0])) {
            return true;
        }
        else if (!Rus(a.author[0]) && Rus(b.author[0])) {
            return false;
        }
        else {
            return a.author < b.author;
        }
        });

    std::cout << "Пронумерованный список литературы:" << std::endl;
    printStructur(structur, true);

    std::cout << std::endl << "Непронумерованный список литературы:" << std::endl;
    printStructur(structur, false);
}