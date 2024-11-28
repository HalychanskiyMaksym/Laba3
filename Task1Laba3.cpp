#include <iostream>
#include <stdexcept> // Для виключень
#include <string>
#include <iomanip> // Для форматованого виводу
using namespace std;

// Оголошення класу Date
class Date {
private:
    int day;    // День (1-31)
    int month;  // Місяць (1-12)
    int year;   // Рік (ціле число)

    // Перевірка коректності дати
    bool isValidDate(int d, int m, int y) {
        // Перевіряємо, чи місяць у допустимих межах
        if (m < 1 || m > 12) return false;

        // Перевіряємо, чи день у межах кількості днів для даного місяця
        if (d < 1 || d > daysInMonth(m, y)) return false;

        return true; // Якщо всі перевірки пройшли, дата коректна
    }

    // Повертає кількість днів у конкретному місяці та році
    int daysInMonth(int m, int y) {
        switch (m) {
            case 4: case 6: case 9: case 11: // Місяці з 30 днями
                return 30;
            case 2: // Лютий
                return (isLeapYear(y) ? 29 : 28); // Враховуємо високосний рік
            default: // Усі інші місяці мають 31 день
                return 31;
        }
    }

    // Перевірка, чи є рік високосним
    bool isLeapYear(int y) {
        // Рік є високосним, якщо ділиться на 4, але не ділиться на 100, 
        // або ділиться на 400
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

public:
    // Конструктор за замовчуванням (дата 1 січня 2000 року)
    Date() : day(1), month(1), year(2000) {}

    // Конструктор з параметрами
    Date(int d, int m, int y) {
        if (!isValidDate(d, m, y)) {
            throw invalid_argument("Некоректна дата!");
        }
        day = d;
        month = m;
        year = y;
    }

    // Функції встановлення дня, місяця та року
    void setDay(int d) {
        if (!isValidDate(d, month, year)) {
            throw invalid_argument("Некоректний день!");
        }
        day = d;
    }

    void setMonth(int m) {
        if (!isValidDate(day, m, year)) {
            throw invalid_argument("Некоректний місяць!");
        }
        month = m;
    }

    void setYear(int y) {
        if (!isValidDate(day, month, y)) {
            throw invalid_argument("Некоректний рік!");
        }
        year = y;
    }

    // Функції отримання дня, місяця та року
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    // Функція друку: формат "5 січня 2019 року"
    void printLongFormat() const {
        const string months[] = { "січня", "лютого", "березня", "квітня", "травня", "червня",
                                  "липня", "серпня", "вересня", "жовтня", "листопада", "грудня" };
        cout << day << " " << months[month - 1] << " " << year << " року" << endl;
    }

    // Функція друку: формат "05.01.2019"
    void printShortFormat() const {
        cout << setw(2) << setfill('0') << day << "."
             << setw(2) << setfill('0') << month << "."
             << year << endl;
    }
};

// Тестова програма
int main() {
    
    try {
        // Створення дати за замовчуванням
        Date date1;
        date1.printLongFormat();
        date1.printShortFormat();

        // Створення дати з параметрами
        Date date2(5, 1, 2019);
        date2.printLongFormat();
        date2.printShortFormat();

        // Зміна полів дати
        date2.setDay(15);
        date2.setMonth(12);
        date2.setYear(2022);
        date2.printLongFormat();
        date2.printShortFormat();

        // Перевірка некоректних значень
        // Date invalidDate(31, 2, 2023); // Викине виключення
    } catch (const exception& e) {
        cerr << "Помилка: " << e.what() << endl;
    }

    return 0;
}
