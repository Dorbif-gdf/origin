#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

struct Address {
    string city;
    string street;
    int houseNumber;
    int apartmentNumber;
    int index;
};

void printAddress(const Address& addr) {
    cout << "Город: " << addr.city << endl;
    cout << "Улица: " << addr.street << endl;
    cout << "Номер дома: " << addr.houseNumber << endl;
    cout << "Номер квартиры: " << addr.apartmentNumber << endl;
    cout << "Индекс: " << addr.index << endl;
    cout << endl;
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Address address1 = { "Москва", "Арбат", 12, 8, 123456 };
    Address address2 = { "Ижевск", "Пушкина", 59, 143, 953769 };

    printAddress(address1);
    printAddress(address2);

}