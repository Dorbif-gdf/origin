#include <iostream>
using namespace std;

enum Month {
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};

int main() 
{
    setlocale(LC_ALL, "Russian");

    int number;

    while (true) {
        cout << "Введите номер месяца: ";
        cin >> number;

        if (number == 0) {
            cout << "До свидания";
            break;
        }

        Month month = (Month)number;

        switch (month) {
        case JANUARY:   cout << "Январь\n"; break;
        case FEBRUARY:  cout << "Февраль\n"; break;
        case MARCH:     cout << "Март\n"; break;
        case APRIL:     cout << "Апрель\n"; break;
        case MAY:       cout << "Май\n"; break;
        case JUNE:      cout << "Июнь\n"; break;
        case JULY:      cout << "Июль\n"; break;
        case AUGUST:    cout << "Август\n"; break;
        case SEPTEMBER: cout << "Сентябрь\n"; break;
        case OCTOBER:   cout << "Октябрь\n"; break;
        case NOVEMBER:  cout << "Ноябрь\n"; break;
        case DECEMBER:  cout << "Декабрь\n"; break;
        default:
            cout << "Неправильный номер!\n";
        }
    }

}