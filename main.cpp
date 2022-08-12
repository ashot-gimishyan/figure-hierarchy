#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <algorithm>

#include "Header.hpp"
#include "Vector.hpp"
#include "Test.hpp"

using namespace std;

// функция No1
void Function1(Vector<Figure*>& myvector)
{
    ifstream fin("data.txt");
    if (!fin.is_open()) {
        perror("error:");
    }

    while (!fin.eof()) {
        int tmp;
        fin >> tmp;

        if (tmp == 1) {
            Point a, b;
            fin >> tmp;
            a.SetX(tmp);
            fin >> tmp;
            a.SetY(tmp);
            fin >> tmp;
            a.SetZ(tmp);
            fin >> tmp;
            b.SetX(tmp);
            fin >> tmp;
            b.SetY(tmp);
            fin >> tmp;
            b.SetZ(tmp);
            Segment* S = new Segment(a, b);
            myvector.Push(S);
        }
        else if (tmp == 2) {
            double ugol;
            fin >> ugol;

            double a, b;
            fin >> a;
            fin >> b;

            AcuteTriangle* T = new AcuteTriangle(ugol, a, b);

            if (T->CheckIfAcute() == true) {
                myvector.Push(T);
            }
            else {
                cout << "Обман! Это не равнобедренный остроугольный треугольник!" << endl;
            }
        }
        else if (tmp == 3) {
            // ооооо пирамида!
            double ugol;
            fin >> ugol;

            double a, b;
            fin >> a;
            fin >> b;

            double high;
            fin >> high;

            Pyramid* P = new Pyramid(ugol, a, b, high);
            //AcuteTriangle *T = P;
            myvector.Push(P);

            /*     // так как пирамида наследник треугольника
			// боковой треугольник пирамиды также можно проверить через CheckIfAcute()
			if (P -> CheckIfAcute() == true) {
					myvector.Push(P);
			}
			else {
				cout << "Обман! Это не равнобедренный остроугольный треугольник!" << endl;
			} */ // в этом слаучае следует удалить строке 283 myvector.Push(P);
            // и раскомментировать строки от 285 до 292
        }
        else {
            cout << "Неправильный числовой код класса!" << endl;
            break;
        }
    }
    fin.close();
}

void Function2(Vector<Figure*>& v)
{
    for (int i = 0; i < v.Size() - 1; ++i) {
        v[i]->Print();
    }
}

void Function3(Vector<Figure*>& v)
{
    Segment max_segment; // максимум по длине
    double max_triangle_st = 0;
    AcuteTriangle max_triangle; // треугольник с максимальной стороной
    double max_area_pye;
    Pyramid max_pyramid; // пирамида с максимальным объемом

    for (int i = 0; i < v.Size() - 1; i++) {
        string FigureName = v[i]->DefType();

        if (FigureName == typeid(Segment).name()) {
            // дополнительно найдем самый длинный сегмент
            Segment* S = dynamic_cast<Segment*>(v[i]);
            if (S->GetLen() > max_segment.GetLen()) {
                max_segment = *S;
            }
        }
        else if (FigureName == typeid(AcuteTriangle).name()) {
            AcuteTriangle* T = dynamic_cast<AcuteTriangle*>(v[i]);

            // найдем макс. сторону текущего треугольника через функция std::max() библиотеки<algorithm>
            int local_max = max(max(T->Geta(), T->Getb()), T->C());

            // если максимальная сторона (local_max) текущего треугольника (T)
            // больше максимальной стороны (max_triangle_st) текущего максимального треугольника (max_triangle)
            if (max_triangle_st < local_max) {
                max_triangle = *T;
                max_triangle_st = local_max;
            } // тогда найден новый максимальный треугольник (с максимальной стороной)
        }
        else if (FigureName == typeid(Pyramid).name()) {
            // найдем пирамиду с максимальным объемом
            Pyramid* P = dynamic_cast<Pyramid*>(v[i]);
            if (P->Volume() > max_pyramid.Volume()) {
                max_pyramid = *P;
            }
        }
    }

    /*
		max_segment.Print();
		max_triangle.Print();
		max_pyramid.Print(); */
}

int main()
{
    Vector<Figure*> myvector(16);
    Function1(myvector);
    Function2(myvector);
    Function3(myvector);
    cout << "OK" << endl;
    return 0;
}
