#include "String.h"
#include <cstring>

namespace custom_string
{

String::String()
    : m_data(new char[1])
{
    m_data[0] = '\0';
}

String::String(const char *c_string)
{
    if (c_string)
    {
        create_data(c_string , strlen(c_string));
        return;
    }
    m_data = new char[1];
    m_data[0] = '\0';
    m_length = 0;
}

String::String( const String& other )
{
    create_data(other.m_data , other.m_length);
}

void String::create_data( const char *data , std::size_t length )
{
    // Узнаем длины строки
    this->m_length = length;

    // Мы знаем размер копируемого объекта, значит можем заранее зарезервировать необходимый размер
    // Добавляем +1, т.к. необходимо избежать автоматического расширения массива
    this->m_data = new char[this->m_length + 1];
    std::memcpy(m_data , data , length + 1);
}

// Берем туже ячейку что и перемещаемый объект
String::String( String &&other ) noexcept
    : m_data{other.m_data}
    , m_length{other.m_length}
{
    // Очищаем other от данных
    other.m_data = nullptr;
    other.m_length = 0;
}

String::~String()
{
    // Очищаем указатель
    delete[] m_data;
}

String& String::operator=(const String& other )
{
    // Проверка на себя
    if (&other != this)
    {
        reload_data(other.m_data , other.m_length);
    }

    return *this;
}

String& String::operator=(const char* other )
{
    reload_data(other , strlen(other));

    return *this;
}

String& String::operator=( String&& other )
{
    // Проверка на себя
    if (&other != this)
    {
        reload_data(other.m_data , other.m_length);
        // Очищаем other от данных
        other.m_data = nullptr;
        other.m_length = 0;
    }

    return *this;
}

void String::reload_data( const char *data , std::size_t length )
{
    this->m_length = length;

    char * new_data = new char[this->m_length];
    new_data[this->m_length] = '\0';

    std::memcpy(new_data , data , this->m_length);
    delete[] this->m_data;

    this->m_data = new_data;
}

String& String::operator+=(const String& other)
{
    update_data(other.m_data , other.m_length);

    return *this;
}

String& String::operator+=(const char* other)
{
    update_data(other , strlen(other));

    return *this;
}

String& String::operator+=( String&& other)
{
    update_data(other.m_data , other.m_length);

    // Очищаем other от данных
    other.m_data = nullptr;
    other.m_length = 0;

    return *this;
}

void String::update_data( const char *data , std::size_t length )
{
    // Создаем новый указатель и резервируем память
    char * new_data = new char[this->m_length + length];

    // Избавляемся от мусора после элемента this->m_length + length
    new_data[this->m_length + length] = '\0';

    // Сохраняем данные прошлого указателя и полученные данные
    std::memcpy(new_data , this->m_data , this->m_length);
    std::memcpy(new_data + this->m_length , data , length);

    delete[] this->m_data;

    this->m_data = new_data;
    this->m_length += length;
}


bool String::is_more(const String& left , const String& right)
{
    std::size_t pos = 0;

    const std::size_t left_length = left.m_length;
    const std::size_t right_length = right.m_length;

    const char* left_data = left.m_data;
    const char* right_data = right.m_data;

    while ( pos < left_length && pos < right_length)
    {
        // Приводим к unsigned char, чтобы избежать неопределенного поведения
        const unsigned char c_left = std::tolower(static_cast<unsigned char>(left_data[pos]));
        const unsigned char c_right = std::tolower(static_cast<unsigned char>(right_data[pos]));

        if ( c_left > c_right) return true;
        if ( c_left < c_right) return false;
        ++pos;
    }
    return left_length > right_length;
}

bool String::is_equal(const String& left , const String& right)
{
    std::size_t pos = 0;

    const std::size_t left_length = left.m_length;
    const std::size_t right_length = right.m_length;

    const char* left_data = left.m_data;
    const char* right_data = right.m_data;

    while ( pos < left_length && pos < right_length)
    {
        // Приводим к unsigned char, чтобы избежать неопределенного поведения
        const unsigned char c_left = std::tolower(static_cast<unsigned char>(left_data[pos]));
        const unsigned char c_right = std::tolower(static_cast<unsigned char>(right_data[pos]));
        if (c_left != c_right) return false;

        ++pos;
    }

    return true;
}

bool String::operator==(const String& other) const
{
    // return comparison_no_reg(*this , other) == 2;
    return is_equal(*this , other);
}
bool String::operator!=(const String& other) const
{
    // != обратно ==, поэтому ставим отрицание
    return !(*this == other);
}
bool String::operator>(const String& other) const
{
    // return comparison_no_reg(*this , other) != 0;
    return is_more(*this , other);
}
bool String::operator>=(const String& other) const
{
    // >= обратно <, поэтому ставим отрицание
    return (*this > other) || (*this == other);
}
bool String::operator<(const String& other) const
{
    // return comparison_no_reg(*this , other) == 0;
    return !(*this >= other);
}
bool String::operator<=(const String& other) const
{
    // <= обратно >, поэтому ставим отрицание
    return !(*this > other);
}
bool String::operator==(const char* other) const
{
    // return comparison_no_reg(*this , String(other)) == 2;
    return is_equal(*this , String(other));
}
bool String::operator!=(const char* other) const
{
    // != обратно ==, поэтому ставим отрицание
    return !(*this == String(other));
}
bool String::operator>(const char* other) const
{
    // return comparison_no_reg(*this , String(other)) != 0;
    return is_more(*this , String(other));
}
bool String::operator>=(const char* other) const
{
    // >= обратно <, поэтому ставим отрицание
    // return !(*this < String(other));
    return (*this > String(other)) || (*this == String(other));
}
bool String::operator<(const char* other) const
{
    // return comparison_no_reg(*this , String(other)) == 0;
    return !(*this >= String(other));
}
bool String::operator<=(const char* other) const
{
    // <= обратно >, поэтому ставим отрицание
    return !(*this > String(other));
}

}
