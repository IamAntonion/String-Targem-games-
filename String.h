#ifndef String_H
#define String_H

#include <cstdint>
#include <ostream>

namespace custom_string
{

class String
{
public:
    explicit String();

    // Необходим для работы с традиционной С-строкой, оканчивающихся нулем
    String(const char *c_string);

    // Конструктор копирования
    String( const String& other );

    // Конструктор перемещения (move-семантика)
    String( String &&other ) noexcept;

    // В деструкторе освобождаем память для m_data
    ~String();

    // Возвращаем длину строки
    std::size_t     length() { return m_length; }

    // Возвращаем указатель на начало строки
    char *          front() { return m_data; }

    // Возвращаем указатель на конец строки
    char *          back() { return m_data + m_length; }

    // Переопределяем оператор присваивания
    String& operator=(const String& other );
    String& operator=(const char* other );
    String& operator=( String&& other );

    // Переопределяем оператор присвоения
    String& operator+=(const String& other);
    String& operator+=(const char* other);
    String& operator+=( String&& other);

    // Переопределяем операторы сравнения
    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;
    bool operator>(const String& other) const;
    bool operator>=(const String& other) const;
    bool operator<(const String& other) const;
    bool operator<=(const String& other) const;
    bool operator==(const char* other) const;
    bool operator!=(const char* other) const;
    bool operator>(const char* other) const;
    bool operator>=(const char* other) const;
    bool operator<(const char* other) const;
    bool operator<=(const char* other) const;

    // Переопределяем оператор сложения
    friend String operator+(const String& left , const String& right)
    {
        String *result = new String(left);

        // Вызываем оператор += чтобы добавить значения из right
        *result += right;

        return *result;
    }
    friend String operator+(const String& left , const char* right)
    {
        String *result = new String(left);

        // Вызываем оператор += чтобы добавить значения из right
        *result += right;

        return *result;
    }
    friend String operator+( const char* right , const String& left)
    {
        String *result = new String(right);

        // Вызываем оператор += чтобы добавить значения из right
        *result += left;

        return *result;
    }

    // Переопределяем оператор вывода
    friend std::ostream& operator<<(std::ostream &os, const String &other)
    {
        String str(other);
        return os << str.front();
    }

private:
    // Данные строки
    char            *m_data;
    // Размер массива
    std::size_t     m_length{0};

    void update_data( const char *data , std::size_t length );
    void reload_data( const char *data , std::size_t length );
    void create_data( const char *data , std::size_t length );

    static bool is_more(const String& left , const String& right);
    static bool is_equal(const String& left , const String& right);
};

}
#endif // String_H
