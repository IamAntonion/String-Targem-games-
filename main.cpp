/*

# Реализовать класс динамических строк `String`

1. Написан на C++11 без использования сторонних библиотек. Не использует в своей основе
какую-либо другую реализацию динамических строк, контейнеров или умных указателей STL.
Можно использовать стандартную библиотеку C.

2. Класс не шаблонный. Поддерживает строки произвольного размера, используя базовые
операции работы с динамическим хипом (функции `malloc()/free()` или операторы `new/delete`)
для манипуляции последовательностями символов типа `char`.

3. Интерфейс класса:
- Есть конструктор копирования.                 +
- Есть оператор присваивания.                   +
- Поддерживается move-сематника.                +
- Есть оператор `+=`.                           +
- Есть внешний оператор сложения двух строк.    +
- Операции поддерживаются не только для         +
параметров типа `String`, но и для традиционных
С-строк, оканчивающихся нулем.

Нет необходимости использовать какие-то изощренные методы оптимизации (типа SSO, COW и многопоточной поддержки).

Написать пример с использованием этого класса строк и какого-либо контейнера STL.
Программа должна принимать список строк, затем выдавать его в порядке, обратном
лексикографическому без учета регистра. Поддержки кодировки ASCII будет достаточно.

Программа-пример работает из командной строки.

example command:
-   custom_string.exe qWerty AsdfgH zXCvbn
return:
zXCvbn
qWerty
AsdfgH
-   custom_string.exe qWertty Qqqrty qwwrtyyyy
return:
qwwrtyyyy
qWertty
Qqqrty
*/

#include <iostream>
#include <algorithm>
#include <vector>

#include "String.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Use next command: " << argv[0] << " example1 example2 etc" << std::endl;

        return 0;
    }

    std::vector<custom_string::String> vec_strs;
    {
        // //Проверяем конструктор работы с си строками и операции
        // {
        //     std::cout << "String(const char *c_string)" << std::endl;
        //     custom_string::String str("123");
        //     std::cout << str << std::endl;

        //     str += "456";
        //     std::cout << str << std::endl;

        //     str = str + "789";
        //     std::cout << str << std::endl;

        //     str = "789" + str;
        //     std::cout << str << std::endl;

        //     str = custom_string::String("456") + str;
        //     std::cout << str << std::endl;

        //     str = "123";
        //     std::cout << str << std::endl;

        //     vec_strs.push(str);
        // }

        // //Проверяем конструктор копирования и операции
        // {
        //     std::cout << "String( const String& other )" << std::endl;
        //     custom_string::String str_1("123");
        //     custom_string::String str(str_1);
        //     std::cout << str << std::endl;

        //     custom_string::String str_2("456");
        //     str += str_2;
        //     std::cout << str << std::endl;

        //     custom_string::String str_3("789");
        //     str += str_3;
        //     std::cout << str << std::endl;

        //     str = str_1;
        //     std::cout << str << std::endl;

        //     vec_strs.push(str);
        // }

        // //Проверяем конструктор перемещения
        // {
        //     std::cout << "String( String &&other )" << std::endl;
        //     custom_string::String str_1("123");
        //     custom_string::String str(std::move(str_1));

        //     if (str_1.front() == nullptr && str_1.length() == 0) std::cout << "str_1 empty" << std::endl;

        //     std::cout << str << std::endl;

        //     custom_string::String str_2("456");
        //     str += std::move(str_2);

        //     if (str_2.front() == nullptr && str_2.length() == 0) std::cout << "str_2 empty" << std::endl;
        //     std::cout << str << std::endl;

        //     custom_string::String str_3("789");
        //     str += std::move(str_3);

        //     if (str_3.front() == nullptr && str_3.length() == 0) std::cout << "str_3 empty" << std::endl;
        //     std::cout << str << std::endl;

        //     str = std::move(str_1);
        //     if (str_1.front() == nullptr && str_1.length() == 0) std::cout << "str_1 empty" << std::endl;
        //     std::cout << str << std::endl;
        // }
    }

    for (auto pos = 1 ; pos < argc ; ++pos)
    {
        vec_strs.push_back(argv[pos]);
    }

    std::sort(vec_strs.begin() , vec_strs.end() ,
              [](const custom_string::String& left , const custom_string::String& right)
              {
        return left > right;
    });

    for (auto str : vec_strs)
    {
        std::cout << str << std::endl;
    }

    return 0;
}
