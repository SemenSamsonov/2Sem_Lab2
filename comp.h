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
