#pragma once
using namespace std;

class Point {
private:
    double x, y, z;

public:
    Point();
    Point(double, double, double);
    Point& operator=(const Point&);

    double GetX()
    {
        return x;
    }
    double GetY()
    {
        return y;
    }
    double GetZ()
    {
        return z;
    }

    void SetX(double _x)
    {
        x = _x;
    }
    void SetY(double _y)
    {
        y = _y;
    }
    void SetZ(double _z)
    {
        z = _z;
    }
};

// базовый абстрактный класс Figure
class Figure {
public:
    // чисто виртуальная функция
    // Print для вывода в дальнейшем полной информации об объекте
    virtual void Print() = 0;
    virtual string DefType() = 0;
};

class Segment : public Figure {
    // числовой код 1 = Segment
private:
    Point A, B;
    double length;

    void SegLength();
    double Sqr(double a)
    {
        return a * a;
    }

public:
    Segment();
    Segment(Segment&);
    Segment(Point&, Point&);
    // переопределение чисто виртуального метода базового класса
    void Print() override;

    ~Segment(){}; // деструктор

    string DefType() override;

    double GetLen()
    {
        return length;
    }
    Point& GetA()
    {
        return A;
    }
    Point& GetB()
    {
        return B;
    }
};

// Производный от Figure класс остроугольного треугольника.
class AcuteTriangle : public Figure {
    // числовой код 2 = AcuteTriangle
protected:
    double alpha; // угол между A и B
    double A, B; // две стороны
    double S, P;

public:
    AcuteTriangle();
    AcuteTriangle(double, double, double);
    void Vvod();
    void Print() override;
    string DefType() override;
    void Perimeter();
    void Square();
    ~AcuteTriangle(){}; // деструктор
    double GetSquare();
    double C();
    // углы. acos это арккосинус, вернет радианы. (...) *180 / PI преобразует в градусы
    double gamma();
    double beta();

    double Geta()
    {
        return A;
    };

    double Getb()
    {
        return B;
    }

    bool CheckIfAcute();
};

// Производный от класса остроугольного треугольника класс пирамиды
class Pyramid : public AcuteTriangle {
private:
    double h; // с дополнительным полем высоты (основание высоты — центр вписанной окружности)
public:
    double SurfaceArea();
    double Volume();
    void Print() override;
    string DefType() override;
    void SetH(double h_)
    {
        h = h_;
    }

    Pyramid(double alp, double a, double b, double h)
    {
        alpha = alp;
        A = a;
        B = b;
        SetH(h);
    }

    Pyramid()
    {
        alpha = 0;
        A = 0;
        B = 0;
        SetH(0);
    }

    ~Pyramid()
    {
    }
};
