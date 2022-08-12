#pragma once
template <typename T>
class Vector {
    int size;
    int capacity;
    T* array;

public:
    Vector();
    Vector&& operator=(const Vector&&);
    Vector(const Vector&&);
    Vector(int initSize);
    ~Vector(); // деструктор
    Vector& operator=(const Vector&);
    Vector(const Vector&);
    T& operator[](int i) const
    {
        return array[i];
    }

    T* Pop();
    void Push(T);
    void Resize(int);
    void Print();
    int Size();
    void Clear();
    T* Back();
    T* Begin();
    T* End();
    bool Empty();
};

template <typename T>
Vector<T>::Vector(int initSize)
{
    size = 0;
    capacity = initSize;
    array = new T[capacity];
}

template <typename T>
Vector<T>::Vector()
{
    size = 0;
    capacity = 0;
    array = nullptr;
}

template <typename T>
Vector<T>::~Vector()
{
    if (array != nullptr) {
        delete[] array;
    }
    size = 0;
    capacity = 0;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
    this->size = rhs.size;
    this->capacity = rhs.capacity;
    delete[] array;
    array = new T[this->capacity];
    for (int i = 0; i < rhs.size; i++)
        this->array[i] = rhs.array[i];

    return *this;
}

template <typename T>
Vector<T>::Vector(const Vector& rhs)
{
    *this = rhs;
}

template <typename T>
Vector<T>::Vector(const Vector&& rhs)
{
    *this = rhs;
}

template <typename T>
int Vector<T>::Size()
{
    return this->size;
}

template <typename T>
T* Vector<T>::Begin()
{
    return this->array;
}

template <typename T>
T* Vector<T>::End()
{
    return &array[size];
}

template <typename T>
bool Vector<T>::Empty()
{
    return (size == 0);
}

template <typename T>
void Vector<T>::Clear()
{
    this->size = 0;
    this->capacity = 0;
    delete[] this->array;
}

template <typename T>
T* Vector<T>::Back()
{
    return &array[size - 1];
}

template <typename T>
void Vector<T>::Resize(int new_capacity)
{
    T* old_array = this->array;
    array = new T[new_capacity];

    for (int j = 0; j < size; j++)
        array[j] = *(old_array + j);

    this->capacity = new_capacity;

    delete[] old_array;
}

template <typename T>
void Vector<T>::Push(T elem)
{
    if (size == capacity)
        Resize(size + capacity);

    array[size] = elem;
    size++;
}

template <typename T>
T* Vector<T>::Pop()
{
    size--;
    return &array[size];
}

template <typename T>
void Vector<T>::Print()
{
    cout << "Размер = " << size << "  вместимость = " << capacity << endl;
    cout << "Вывод элементов" << endl;
    for (int k = 0; k < size; ++k)
        cout << array[k] << "  ";
    cout << endl;
}
