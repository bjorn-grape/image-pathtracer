#pragma once

#include "vector3D.hh"

template<typename T>
vector3D<T>::vector3D()
        : x_(0), y_(0), z_(0) {}

template<typename T>
vector3D<T>::vector3D(T x, T y, T z)
        : x_(x), y_(y), z_(z) {}

template<typename T>
T vector3D<T>::get_X() {
    return x_;
}

template<typename T>
T vector3D<T>::get_Y() {
    return y_;
}

template<typename T>
T vector3D<T>::get_Z() {
    return z_;
}

template<typename T>
void vector3D<T>::set_X(T x) {
    x_ = x;
}

template<typename T>
void vector3D<T>::set_Y(T y) {
    y_ = y
}

template<typename T>
void vector3D<T>::set_Z(T z) {
    z_ = z;
}
