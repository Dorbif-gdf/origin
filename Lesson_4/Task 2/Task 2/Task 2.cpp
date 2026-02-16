#include <iostream>
#include <string>

using namespace std;

class Figure {
protected:
    string name;
public:
    Figure(string name) : name(name) {}
    virtual void print_info() const = 0;
    virtual ~Figure() {}
};


class Triangle : public Figure {
protected:
    int a, b, c;
    int A, B, C;
public:
    Triangle(int a, int b, int c,
        int A, int B, int C)
        : Figure("Треугольник"),
        a(a), b(b), c(c),
        A(A), B(B), C(C) {
    }

    void print_info() const override {
        cout << name << ":\n";
        cout << "Стороны: a=" << a
            << " b=" << b
            << " c=" << c << endl;
        cout << "Углы: A=" << A
            << " B=" << B
            << " C=" << C << "\n\n";
    }
};

class RightTriangle : public Triangle {
public:
    RightTriangle(int a, int b, int c,
        int A, int B)
        : Triangle(a, b, c, A, B, 90) {
        name = "Прямоугольный треугольник";
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(int a, int b,
        int A, int B)
        : Triangle(a, b, a, A, B, A) {
        name = "Равнобедренный треугольник";
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(int a)
        : Triangle(a, a, a, 60, 60, 60) {
        name = "Равносторонний треугольник";
    }
};
 

class Quadrilateral : public Figure {
protected:
    int a, b, c, d;
    int A, B, C, D;
public:
    Quadrilateral(int a, int b, int c, int d,
        int A, int B, int C, int D)
        : Figure("Четырёхугольник"),
        a(a), b(b), c(c), d(d),
        A(A), B(B), C(C), D(D) {
    }

    void print_info() const override {
        cout << name << ":\n";
        cout << "Стороны: a=" << a
            << " b=" << b
            << " c=" << c
            << " d=" << d << endl;
        cout << "Углы: A=" << A
            << " B=" << B
            << " C=" << C
            << " D=" << D << "\n\n";
    }
};

class Rectangle : public Quadrilateral {
public:
    Rectangle(int a, int b)
        : Quadrilateral(a, b, a, b,
            90, 90, 90, 90) {
        name = "Прямоугольник";
    }
};

class Square : public Quadrilateral {
public:
    Square(int a)
        : Quadrilateral(a, a, a, a,
            90, 90, 90, 90) {
        name = "Квадрат";
    }
};

class Parallelogram : public Quadrilateral {
public:
    Parallelogram(int a, int b,
        int A, int B)
        : Quadrilateral(a, b, a, b,
            A, B, A, B) {
        name = "Параллелограмм";
    }
};

// Ромб
class Rhombus : public Quadrilateral {
public:
    Rhombus(int a,
        int A, int B)
        : Quadrilateral(a, a, a, a,
            A, B, A, B) {
        name = "Ромб";
    }
};
 

void print_info(const Figure* figure) {
    figure->print_info();
}


int main() {
    setlocale(LC_ALL, "Russian");

    Triangle t(10, 20, 30, 50, 60, 70);
    RightTriangle rt(10, 20, 30, 50, 60);
    IsoscelesTriangle it(10, 20, 50, 60);
    EquilateralTriangle et(30);

    Quadrilateral q(10, 20, 30, 40, 50, 60, 70, 80);
    Rectangle r(10, 20);
    Square s(20);
    Parallelogram p(20, 30, 30, 40);
    Rhombus rh(30, 30, 40);

    print_info(&t);
    print_info(&rt);
    print_info(&it);
    print_info(&et);

    print_info(&q);
    print_info(&r);
    print_info(&s);
    print_info(&p);
    print_info(&rh);

}