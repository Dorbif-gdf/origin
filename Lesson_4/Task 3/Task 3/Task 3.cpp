#include <iostream>
#include <string>

using namespace std;


class Figure {
protected:
    int sides_count;
    string name;

public:
    Figure(string name, int sides)
        : name(name), sides_count(sides) {
    }

    virtual bool check() {
        return sides_count == 0;
    }

    virtual void print_info() {
        cout << name << ":" << endl;
        cout << (check() ? "Правильная" : "Неправильная") << endl;
        cout << "Количество сторон: " << sides_count << endl;
    }

    virtual ~Figure() {}
};


class Triangle : public Figure {
protected:
    int a, b, c;
    int A, B, C;

public:
    Triangle(string name,
        int a, int b, int c,
        int A, int B, int C)
        : Figure(name, 3),
        a(a), b(b), c(c),
        A(A), B(B), C(C) {
    }

    bool check() override {
        return (A + B + C == 180);
    }

    void print_info() override {
        cout << name << ":" << endl;
        cout << (check() ? "Правильная" : "Неправильная") << endl;
        cout << "Количество сторон: " << sides_count << endl;
        cout << "Стороны: a=" << a << " b=" << b << " c=" << c << endl;
        cout << "Углы: A=" << A << " B=" << B << " C=" << C << endl;
    }
};


class RightTriangle : public Triangle {
public:
    RightTriangle(int a, int b, int c,
        int A, int B)
        : Triangle("Прямоугольный треугольник",
            a, b, c,
            A, B, 90) {
    }

    bool check() override {
        return Triangle::check() && C == 90;
    }
};


class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(int a, int b,
        int A, int B)
        : Triangle("Равнобедренный треугольник",
            a, b, a,
            A, B, A) {
    }

    bool check() override {
        return Triangle::check()
            && a == c
            && A == C;
    }
};


class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(int a)
        : Triangle("Равносторонний треугольник",
            a, a, a,
            60, 60, 60) {
    }

    bool check() override {
        return Triangle::check()
            && a == b && b == c
            && A == 60 && B == 60 && C == 60;
    }
};


class Quadrangle : public Figure {
protected:
    int a, b, c, d;
    int A, B, C, D;

public:
    Quadrangle(string name,
        int a, int b, int c, int d,
        int A, int B, int C, int D)
        : Figure(name, 4),
        a(a), b(b), c(c), d(d),
        A(A), B(B), C(C), D(D) {
    }

    bool check() override {
        return (A + B + C + D == 360);
    }

    void print_info() override {
        cout << name << ":" << endl;
        cout << (check() ? "Правильная" : "Неправильная") << endl;
        cout << "Количество сторон: " << sides_count << endl;
        cout << "Стороны: a=" << a << " b=" << b
            << " c=" << c << " d=" << d << endl;
        cout << "Углы: A=" << A << " B=" << B
            << " C=" << C << " D=" << D << endl;
    }
};


class Rectangle : public Quadrangle {
public:
    Rectangle(int a, int b)
        : Quadrangle("Прямоугольник",
            a, b, a, b,
            90, 90, 90, 90) {
    }

    bool check() override {
        return Quadrangle::check()
            && a == c && b == d
            && A == 90 && B == 90
            && C == 90 && D == 90;
    }
};


class Square : public Rectangle {
public:
    Square(int a)
        : Rectangle(a, a) {
    }

    bool check() override {
        return Rectangle::check() && a == b;
    }
};


class Parallelogram : public Quadrangle {
public:
    Parallelogram(int a, int b,
        int A, int B)
        : Quadrangle("Параллелограмм",
            a, b, a, b,
            A, B, A, B) {
    }

    bool check() override {
        return Quadrangle::check()
            && a == c && b == d
            && A == C && B == D;
    }
};


class Rhombus : public Parallelogram {
public:
    Rhombus(int a,
        int A, int B)
        : Parallelogram(a, a, A, B) {
    }

    bool check() override {
        return Parallelogram::check()
            && a == b && b == c && c == d;
    }
};


int main() {
    setlocale(LC_ALL, "Russian");

    Figure* figures[] = {
        new Figure("Фигура", 0),
        new Triangle("Треугольник", 10, 20, 30, 50, 60, 70),
        new RightTriangle(10, 20, 30, 50, 60),
        new RightTriangle(10, 20, 30, 50, 40),
        new IsoscelesTriangle(10, 20, 50, 60),
        new EquilateralTriangle(30),
        new Quadrangle("Четырёхугольник", 10, 20, 30, 40, 50, 60, 70, 80),
        new Rectangle(10, 20),
        new Square(20),
        new Parallelogram(20, 30, 30, 40),
        new Rhombus(30, 30, 40)
    };

    for (Figure* f : figures) {
        f->print_info();
        cout << endl;
    }

    for (Figure* f : figures) {
        delete f;
    }

}