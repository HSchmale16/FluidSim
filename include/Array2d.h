#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <cassert>
#include <cstdint>

template<typename T>
class Array2d {
public:
    Array2d(uint64_t w, uint64_t h);
    ~Array2d();

    uint64_t getHeight() {
        return _height;
    }
    uint64_t getWidth() {
        return _width;
    }
    uint64_t getSize() {
        return _size;
    }

    T& operator()(uint64_t x, uint64_t y);

private:
    T*       _data;
    uint64_t _height;
    uint64_t _width;
    uint64_t _size;
};

template<typename T>
Array2d<T>::Array2d(uint64_t w, uint64_t h) {
    //ctor
}

template<typename T>
Array2d<T>::~Array2d() {
    //dtor
}

template<typename T>
T& Array2d<T>::operator()(uint64_t x, uint64_t y){
    assert(_data);
    return _data[y * _width + x];
}


#endif // ARRAY2D_H
