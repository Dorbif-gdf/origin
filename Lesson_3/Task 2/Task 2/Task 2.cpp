#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Address {
private:
    string city;
    string street;
    int house;
    int apartment;

public:
    Address(string city, string street, int house, int apartment) {
        this->city = city;
        this->street = street;
        this->house = house;
        this->apartment = apartment;
    }

    string get_output_address() const {
        return city + ", " + street + ", " +
            to_string(house) + ", " +
            to_string(apartment);
    }

    string get_city() const {
        return city;
    }
};

void sort(Address** addresses, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (addresses[j]->get_city() > addresses[j + 1]->get_city()) {
                Address* temp = addresses[j];
                addresses[j] = addresses[j + 1];
                addresses[j + 1] = temp;
            }
        }
    }
}

int main() {

    ifstream fin("in.txt");
    ofstream fout("out.txt");

    int N;
    fin >> N;
    fin.ignore();

    // Массив указателей
    Address** addresses = new Address * [N];

    string city, street;
    int house, apartment;

    for (int i = 0; i < N; i++) {
        getline(fin, city);
        getline(fin, street);
        fin >> house;
        fin >> apartment;
        fin.ignore();

        addresses[i] = new Address(city, street, house, apartment);
    }

    sort(addresses, N);

    fout << N << endl;
    for (int i = 0; i < N; i++) {
        fout << addresses[i]->get_output_address() << endl;
    }

    fin.close();
    fout.close();

}