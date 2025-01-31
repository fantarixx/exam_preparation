#ifndef TEMPLATE_VECTOR_H
#define TEMPLATE_VECTOR_H

#include <ostream>
#include <stdexcept>

template <typename T>
class Template_Vector {
private:
    T* data;

    long amount;
    long capacity;

    void resize();

public:
    Template_Vector(const long start_size = 0);
    Template_Vector(const Template_Vector<T>& vec);

    long size() const;


    T operator[](const long index) const;
    T& operator[](const long index);
    Template_Vector<T>& operator=(const Template_Vector<T>& vec);
    
    void push_back(const T& elem); 
    void pop();
};

template <typename T>
void Template_Vector<T>::resize() {
    capacity *= 2;
    T* ptr = new T[capacity];

    for (long i = 0; i < amount; ++i) {
        ptr[i] = data[i];
    }

    delete[] data;
    data = ptr;
    delete[] ptr;
}

template <typename T>
Template_Vector<T>::Template_Vector(long start_size) : amount(start_size), capacity(2 * (start_size + static_cast<long>(start_size == 0))) {
    data = new T[capacity];
}

template <typename T>
Template_Vector<T>::Template_Vector(const Template_Vector<T>& vec) {
    amount = vec.amount;
    capacity = vec.capacity;

    for (long i = 0; i < amount; ++i) {
        data[i] = vec.data[i];
    }
}

template <typename T>
long Template_Vector<T>::size() const {
    return amount;
}

template <typename T>
T Template_Vector<T>::operator[](const long index) const {
    if (index >= amount || index < 0) {
        throw std::runtime_error("Get out of vector range");
    }
    
    return data[index];
}

template <typename T>
T& Template_Vector<T>::operator[](const long index) {
    if (index >= amount || index < 0) {
        throw std::runtime_error("Get out of vector range");
    }

    return &data[index];
}

template <typename T>
Template_Vector<T>& Template_Vector<T>::operator=(const Template_Vector<T>& vec) {
    capacity = vec.capacity;
    amount = vec.capacity;

    Template_Vector<T> tmp(vec);
    std::swap(amount, tmp.amount);
    std::swap(data, tmp.data);
    
    return *this;
}

template <typename T>
void Template_Vector<T>::push_back(const T& elem) {
    if (amount == capacity) {
        resize();
    }

    data[amount++] = elem;
}

template <typename T>
void Template_Vector<T>::pop() {
    if (amount > 0) {
        --amount;
    }     
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Template_Vector<T>& vec) {
    long size = vec.size();
    
    for (long i = 0; i < size - 1; ++i) {
        stream << vec[i] << " ";
    }     
    if (size > 0) {
        stream << vec[size - 1] << std::endl;
    }

    return stream;
}


    
#endif // TEMPLATE_VECTOR_H
