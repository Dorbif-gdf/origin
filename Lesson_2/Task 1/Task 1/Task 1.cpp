#include <iostream>
using namespace std;

class Calculator {
public:
    double num1;
    double num2;

public:
    bool set_num1(double n1) {
        if (n1 != 0) {
            num1 = n1;
            return true;
        }
        return false;
    }

    bool set_num2(double n2) {
        if (n2 != 0) {
            num2 = n2;
            return true;
        }
        return false;
    }

    double add() {
        return num1 + num2;
    }

    double multiply() {
        return num1 * num2;
    }

    double subtract_1_2() {
        return num1 - num2;
    }

    double subtract_2_1() {
        return num2 - num1;
    }

    double divide_1_2() {
        return num1 / num2;
    }

    double divide_2_1() {
        return num2 / num1;
    }
};


int main()
{
    setlocale(LC_ALL, "Russian");

    Calculator calc;
    double input;

    while (true) {
        cout << "Введите num1: ";
        cin >> input;

        if (!calc.set_num1(input)) {
            cout << "Неверный ввод!" << endl;
            continue;
        }

        cout << "Введите num2: ";
        cin >> input;

        if (!calc.set_num2(input)) {
            cout << "Неверный ввод!" << endl;
            continue;
        }

        cout << "num1 + num2 = " << calc.add() << endl;
        cout << "num1 - num2 = " << calc.subtract_1_2() << endl;
        cout << "num2 - num1 = " << calc.subtract_2_1() << endl;
        cout << "num1 * num2 = " << calc.multiply() << endl;
        cout << "num1 / num2 = " << calc.divide_1_2() << endl;
        cout << "num2 / num1 = " << calc.divide_2_1() << endl;
        cout << endl;
    }

}