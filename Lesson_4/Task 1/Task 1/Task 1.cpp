#include <iostream>
#include <string>

class Figure {
private:
    int sides_count;   

protected:
    std::string name;  

    Figure(int sides) : sides_count(sides) {}

public:
    Figure() : Figure(0) {
        name = "Фигура";
    }

    int get_sides_count() const {
        return sides_count;
    }

    std::string get_name() const {
        return name;
    }
};

class Triangle : public Figure {
public:
    Triangle() : Figure(3) {
        name = "Треугольник";
    }
};

class Quadrangle : public Figure {
public:
    Quadrangle() : Figure(4) {
        name = "Четырёхугольник";
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Figure figure;
    Triangle triangle;
    Quadrangle quadrangle;

    std::cout << "Количество сторон:\n";
    std::cout << figure.get_name() << ": " << figure.get_sides_count() << std::endl;
    std::cout << triangle.get_name() << ": " << triangle.get_sides_count() << std::endl;
    std::cout << quadrangle.get_name() << ": " << quadrangle.get_sides_count() << std::endl;

}