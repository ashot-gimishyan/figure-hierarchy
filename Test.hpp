#pragma once
using namespace std;
const float PI = 3.14159265;

Point::Point()
{
    x = 0;
    y = 0;
    z = 0;
}

Point::Point(double _x, double _y, double _z)
{
    try {
        x = _x;
        y = _y;
        z = _z;
    }
    catch (...) {
    }
}

Point& Point::operator=(const Point& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}

void Segment::SegLength()
{
    this->length = sqrt(Sqr(B.GetX() - A.GetX()) + Sqr(B.GetY() - A.GetY()) + Sqr(B.GetZ() - A.GetZ()));
}

Segment::Segment()
{
    A = Point(0, 0, 0);
    B = Point(0, 0, 0);
    SegLength();
}

Segment::Segment(Point& a, Point& b)
{
    try {
        A = a;
        B = b;
        SegLength();
    }
    catch (...) {
    }
}

void Segment::Print()
{
    cout << "\n\nЯ сегмент (Segment). Информация обо мне:" << endl;
    cout << "Точка A: "
         << "(" << A.GetX() << "," << A.GetY() << "," << A.GetZ() << ")" << endl;
    cout << "Точка B: "
         << "(" << B.GetX() << "," << B.GetY() << "," << B.GetZ() << ")" << endl;
}

string Segment::DefType()
{
    return typeid(decltype(*this)).name();
}

Segment::Segment(Segment& rhs)
{
    A = rhs.A;
    B = rhs.B;
    SegLength();
}

AcuteTriangle::AcuteTriangle()
{
    alpha = 0;
    A = 0;
    B = 0;
    Square();
    Perimeter();
}

void AcuteTriangle::Vvod()
{
    setlocale(LC_ALL, "Russian");

    cout << "Введите длину A: ";
    cin >> A;

    cout << "Введите длину B: ";
    cin >> B;

    cout << "Введите угол между сторонами A и B: ";
    cin >> alpha;

    if (alpha >= 90) {
        cout << "Треугольник не остроугольный";
        return;
    }
}

void AcuteTriangle::Print()
{
    cout << "\n\nЯ остроугольный треугольник (AcuteTriangle). Информация обо мне:" << endl;
    cout << "Длины сторон a, b, c: " << A << ' ' << B << ' ' << C() << endl;
    cout << "Угол: " << alpha << ' ' << beta() << ' ' << gamma() << endl;
    cout << "Площадь: " << S << endl;
    cout << "Периметр: " << P << endl;
}

string AcuteTriangle::DefType()
{
    return typeid(decltype(*this)).name();
}

void AcuteTriangle::Square()
{
    S = 0.5 * A * B * sin(alpha * PI / 180); // вычисляем синус угла, переведённого в радианы
}

AcuteTriangle::AcuteTriangle(double ug1, double a, double b)
{
    try {
        if (a < 0 || b < 0) {
            throw std::invalid_argument("Длина положительная величина!!!");
        }
    }
    catch (std::invalid_argument&) {
        cout << "Введите корректные данные (длина положительная величина)" << endl;
        exit(1);
    }
    // если все хорошо
    alpha = ug1;

    A = a;
    B = b;
    Perimeter();
    Square();
}

double AcuteTriangle::GetSquare()
{
    return S;
}
void AcuteTriangle::Perimeter()
{
    P = A + B + C();
}

double AcuteTriangle::C()
{
    // по теореме косинусов найдем сторону C, если известны A, B и alpha
    return sqrt(A * A + B * B - 2 * A * B * cos(alpha * PI / 180));
}

// углы. acos это арккосинус, вернет радианы. (...) *180 / PI преобразует в градусы
double AcuteTriangle::gamma()
{
    // по теореме косинусов
    return acos((A * A + C() * C() - B * B) / (2 * A * C())) * 180 / PI;
}

double AcuteTriangle::beta()
{
    // по теореме косинусов
    return acos((B * B + C() * C() - A * A) / (2 * B * C())) * 180 / PI;
}

bool AcuteTriangle::CheckIfAcute()
{
    if (alpha >= 90 || beta() >= 90 || gamma() >= 90) {
        return false; // не остроугольный
    }

    if (A != B) {
        return false; // не равнобедренный
    }

    return true; // ok это остроугольный равнобедренный треугольник
}

double Pyramid::SurfaceArea()
{
    // площадь поверхности
    // Площадь поверхности пирамиды равна сумме площадей боковой поверхности и основания:
    return 4 * sqrt(P * (P - A) * (P - B) * (P - C())) + A * A;
    // где sqrt(P*(P-A)*(P-B)*(P-C)) площадь одного бокового треугольника по формуле Герона
}

double Pyramid::Volume()
{
    // объем
    // Объем пирамиды равен одной трети произведения площади основания на высоту
    return A * A * h / 3;
}

void Pyramid::Print()
{
    cout << "\n\nЯ Пирамида (Pyramid). Информация обо мне:" << endl;
    cout << "Высота: " << h << endl;
    cout << "Площадь поверхности: " << SurfaceArea() << endl;
    cout << "Объем: " << Volume() << endl;
}

string Pyramid::DefType()
{
    return typeid(decltype(*this)).name();
}
