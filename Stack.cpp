#include "Stack.h"
#include "StackImplementation.h"
#include "Vector.h"
#include "ForwardList.h"
#include <stdexcept>
#include "comp.h"

Stack::Stack(StackContainer container) : _containerType(container) {
    switch (_containerType) {
        case StackContainer::Vector:
            _pimpl = new VectorStack();
            break;
        case StackContainer::List:
            _pimpl = new ListStack();
            break;
        default:
            throw std::invalid_argument("Unknown container type");
    }
}

Stack::Stack(const ValueType* valueArray, size_t arraySize, StackContainer container)
    : Stack(container) {
    for (size_t i = 0; i < arraySize; ++i) {
        push(valueArray[i]);
    }
}

Stack::Stack(const Stack& other) : _containerType(other._containerType) {
    *this = other;
}

Stack& Stack::operator=(const Stack& other) {
    if (this != &other) {
        IStackImplementation* temp = nullptr;
        switch (other._containerType) {
            case StackContainer::Vector:
                temp = new VectorStack(*dynamic_cast<const VectorStack*>(other._pimpl));
                break;
            case StackContainer::List:
                temp = new ListStack(*dynamic_cast<const ListStack*>(other._pimpl));
                break;
        }
        
        delete _pimpl;
        _pimpl = temp;
        _containerType = other._containerType;
    }
    return *this;
}

Stack::Stack(Stack&& other) noexcept {
    *this = std::move(other);
}

Stack& Stack::operator=(Stack&& other) noexcept {
    if (this != &other) {
        delete _pimpl;
        _pimpl = other._pimpl;
        _containerType = other._containerType;
        other._pimpl = nullptr;
    }
    return *this;
}

Stack::~Stack() {
    delete _pimpl;
}

void Stack::push(const ValueType& value) {
    _pimpl->push(value);
}

void Stack::pop() {
    _pimpl->pop();
}

const ValueType& Stack::top() const {
    return _pimpl->top();
}

bool Stack::isEmpty() const {
    return _pimpl->isEmpty();
}

size_t Stack::size() const {
    return _pimpl->size();
}
