#include <iostream>
#include <Windows.h>
using namespace std;


class Counter {
private:
    int value;  

public:
    Counter() {
        value = 1;
    }

    Counter(int startValue) {
        value = startValue;
    }

    void increment() {
        value++;
    }

    void decrement() {
        value--;
    }

    int getValue() const {
        return value;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string answer;
    cout << "Вы хотите указать начальное значение счётчика? Введите да или нет: ";
    cin >> answer;

    Counter counter; 

    if (answer == "да") {
        int startValue;
        cout << "Введите начальное значение счётчика: ";
        cin >> startValue;
        counter = Counter(startValue); 
    }

    char command;

    do {
        cout << "Введите команду ('+', '-', '=' или 'x'): ";
        cin >> command;

        switch (command) {
        case '+':
            counter.increment();
            break;
        case '-':
            counter.decrement();
            break;
        case '=':
            cout << counter.getValue() << endl;
            break;
        case 'x':
            cout << "До свидания!" << endl;
            break;
        default:
            cout << "Неизвестная команда!" << endl;
        }

    } while (command != 'x');

}