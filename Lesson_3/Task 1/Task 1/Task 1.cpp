#include <iostream>
#include <fstream>
#include <string>


class Address {
private:
    std::string city;
    std::string street;
    int house;
    int apartment;

public:
    Address(std::string city, std::string street, int house, int apartment) {
        this->city = city;
        this->street = street;
        this->house = house;
        this->apartment = apartment;
    }

    std::string get_output_address() const {
        return city + ", " + street + ", " +
            std::to_string(house) + ", " +
            std::to_string(apartment);
    }
};

int main() {

    std::ifstream in("in.txt");
    std::ofstream out("out.txt");

    if (!in.is_open() || !out.is_open()) {
        std::cout << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    int N;
    in >> N;
    in.ignore(); 

    Address** addresses = new Address * [N];

    for (int i = 0; i < N; i++) {
        std::string city;
        std::string street;
        int house;
        int apartment;

        std::getline(in, city);
        std::getline(in, street);
        in >> house;
        in >> apartment;
        in.ignore();

        addresses[i] = new Address(city, street, house, apartment);
    }

    out << N << std::endl;

    for (int i = N - 1; i >= 0; i--) {
        out << addresses[i]->get_output_address() << std::endl;
    }

    in.close();
    out.close();
}