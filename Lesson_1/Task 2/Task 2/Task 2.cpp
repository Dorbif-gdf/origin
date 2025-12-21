#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

struct BankAccount {
    int accountNumber;     
    string ownerName;      
    double balance;        
};

void changeBalance(BankAccount& account, double newBalance) {
    account.balance = newBalance;
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    BankAccount account;

    cout << "Введите номер счёта: ";
    cin >> account.accountNumber;

    cout << "Введите имя владельца: ";
    cin >> account.ownerName;

    cout << "Введите баланс: ";
    cin >> account.balance;

    double newBalance;
    cout << "Введите новый баланс: ";
    cin >> newBalance;

    changeBalance(account, newBalance);

    cout << "Ваш счёт: "
        << account.ownerName << ", "
        << account.accountNumber << ", "
        << account.balance << endl;
}