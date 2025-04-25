#include "Vector.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstring>
#include <utility>  
#include <type_traits>


Vector::Vector(const ValueType* rawArray, const size_t size, float coef) : 
	_size(size), 
	_capacity(size), 
	_multiplicativeCoef(coef), 
	_data(nullptr) 
{
    if (coef <= 1.0f) throw std::invalid_argument("Coef must be > 1.0");
    if (size > 0) {
        _data = new ValueType[_capacity];
        std::copy(rawArray, rawArray + size, _data);
    }
}

Vector::Vector(const Vector& other) : 

	_size(other._size), 
	_capacity(other._size),
    _multiplicativeCoef(other._multiplicativeCoef),
    _data(other._size ? new ValueType[other._size] : nullptr) 
{
    if (other._size) {
        if constexpr (std::is_trivially_copyable_v<ValueType>) {std::memcpy(_data, other._data, _size * sizeof(ValueType));} 
		else {
            std::copy(other._data, other._data + _size, _data);
        }
    }
}

Vector::Vector(Vector&& other) noexcept : _data(other._data), _size(other._size), _capacity(other._capacity)
{
	other._data = nullptr;
	other._size = 0;
	other._capacity = 0;
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        Vector tmp(other);
        std::swap(_data, tmp._data);
        std::swap(_size, tmp._size);
        std::swap(_capacity, tmp._capacity);
        std::swap(_multiplicativeCoef, tmp._multiplicativeCoef);
    }
    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] _data;
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }
    return *this;
}

Vector::~Vector() {
    delete[] _data;
}

void Vector::reserve(size_t capacity) {
    if (capacity > _capacity) {
        ValueType* newData = new ValueType[capacity];
        if (_data) {
            std::copy(_data, _data + _size, newData);
            delete[] _data;
        }
        _data = newData;
        _capacity = capacity;
    }
}

void Vector::shrinkToFit() {
    if (_size < _capacity) {
        _capacity = _size;
        ValueType* newData = _size ? new ValueType[_size] : nullptr;
        if (_data) {
            std::copy(_data, _data + _size, newData);
            delete[] _data;
        }
        _data = newData;
    }
}

void Vector::pushBack(const ValueType& value) {
    if (_size == _capacity) {
        if (_capacity == 0) { _capacity = 1; }
        _capacity *= _multiplicativeCoef;
        ValueType *temp = new ValueType[_capacity];
        for (size_t i = 0; i < _size; i++) {
            temp[i] = _data[i];
        }
        delete[] _data;
        _data = temp;
    }
    _data[_size] = value;
    _size++;
}

void Vector::pushFront(const ValueType& value) {
    if (_capacity == 0) {
	_capacity = _multiplicativeCoef;
	_data = new ValueType[_capacity];
    }
    if (_capacity == _size) {
	_capacity *= _multiplicativeCoef;
	ValueType *temp = new ValueType[_capacity];
        for (size_t i = 1; i < _size + 1; i++)
        {
            temp[i] = _data[i - 1];
        }
        delete[] _data;
        _data = temp;
    }
    else
    {
        for (size_t i = _size; i > 0; i--)
        {
            _data[i] = _data[i - 1];
        }
    }
    _data[0] = value;
    _size++;
}


void Vector::insert(const ValueType& value, size_t pos) {
    if (pos >= 0 && pos < _size + 1) {
        if (_size == _capacity) { _capacity *= _multiplicativeCoef; }
        ValueType *temp = new ValueType[_capacity];
        for (size_t i = 0; i < _size + 1; i++) {
            if (i < pos) { temp[i] = _data[i]; }
            if (i == pos) { temp[i] = value; }
            if (i > pos) { temp[i] = _data[i - 1]; }
        }
        delete[] _data;
        _data = temp;
        _size++;
    }
}
void Vector::insert(const ValueType* values, size_t size, size_t pos) {
    if (pos >= 0 && pos < _size + 1) {
        _size += size;
        while (_size >= _capacity) { _capacity *= _multiplicativeCoef; }
        ValueType *temp = new ValueType[_capacity];
        for (size_t i = 0; i < _size; i++) {
            if (i < pos) { temp[i] = _data[i]; }
            if (i >= pos && i < pos + size) { temp[i] = values[i - pos]; }
            if (i >= pos + size) { temp[i] = _data[i - size]; }
        }
        delete[] _data;
        _data = temp;
    }
}
void Vector::insert(const Vector& vector, size_t pos) {
    if (pos >= 0 && pos < _size + 1) {
        _size += vector._size;
        while (_size >= _capacity) { _capacity *= _multiplicativeCoef; }
        ValueType *temp = new ValueType[_capacity];
        for (size_t i = 0; i < _size; i++) {
            if (i < pos) { temp[i] = _data[i]; }
            if (i >= pos && i < pos + vector._size) { temp[i] = vector[i - pos]; }
            if (i >= pos + vector._size) { temp[i] = _data[i - vector._size]; }
        }
        delete[] _data;
        _data = temp;
    }
}

void Vector::popBack() {
    if (_size > 0) { _size--; }
    else { throw std::length_error("No elements, no radix sort"); }
}

void Vector::popFront() {
    if (_size > 0) {
	for (size_t i = 1; i < _size; i++) {
	     _data[i - 1] = _data[i];
	}
	_size--; 
    }
    else { throw std::length_error("No elements, no delete, nety ruchek, net konfetki"); }
}

void Vector::erase(size_t pos, size_t count) {
    if (pos >= _size) return;
    count = std::min(count, _size - pos);
    std::move(_data + pos + count, _data + _size, _data + pos);
    _size -= count;
}

void Vector::eraseBetween(size_t beginPos, size_t endPos) {
    erase(beginPos, endPos - beginPos);
}

ValueType& Vector::operator[](size_t idx) {
    return _data[idx];
}

const ValueType& Vector::operator[](size_t idx) const {
    return _data[idx];
}

size_t Vector::size() const { return _size; }
size_t Vector::capacity() const { return _capacity; }
double Vector::loadFactor() const { 
    return _capacity > 0 ? static_cast<double>(_size) / _capacity : 0.0; 
}

Vector::Iterator Vector::begin() { return Iterator(_data); }
Vector::Iterator Vector::end() { return Iterator(_data + _size); }

Vector::Iterator::Iterator(ValueType* ptr) : _ptr(ptr) {}
ValueType& Vector::Iterator::operator*() { return *_ptr; }
const ValueType& Vector::Iterator::operator*() const { return *_ptr; }
ValueType* Vector::Iterator::operator->() { return _ptr; }
const ValueType* Vector::Iterator::operator->() const { return _ptr; }
Vector::Iterator Vector::Iterator::operator++() { ++_ptr; return *this; }
Vector::Iterator Vector::Iterator::operator++(int) { 
    Iterator tmp = *this; 
    ++_ptr; 
    return tmp; 
}
bool Vector::Iterator::operator==(const Iterator& other) const { 
    return _ptr == other._ptr; 
}
bool Vector::Iterator::operator!=(const Iterator& other) const { 
    return _ptr != other._ptr;
}
