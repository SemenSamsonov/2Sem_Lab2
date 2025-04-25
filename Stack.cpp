#include "Stack.h"
#include "StackImplementation.h"
#include "Vector.h"
#include "ForwardList.h"
#include <stdexcept>

// на векторе
class VectorStack : public IStackImplementation {
private:
    Vector _vector;
public:
    void push(const ValueType& value) override {
        _vector.pushBack(value);
    }

    void pop() override {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        _vector.popBack();
    }

    const ValueType& top() const override {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return _vector[_vector.size() - 1];
    }

    bool isEmpty() const override {
        return _vector.size() == 0;
    }

    size_t size() const override {
        return _vector.size();
    }
};

// на форвард листе
class ListStack : public IStackImplementation {
private:
    MyList::ForwardList _list;
public:
    void push(const ValueType& value) override {
        _list.push_front(value);
    }

    void pop() override {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        _list.pop_front();
    }

    const ValueType& top() const override {
        return _list.front();
    }

    bool isEmpty() const override {
        return _list.empty();
    }

    size_t size() const override {
        return _list.size();
    }
};

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
