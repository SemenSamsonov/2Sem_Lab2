#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include <cstddef>

namespace MyList {

class ForwardList {
private:
    struct Node {
        double data;
        Node* next;
        Node(double value) : data(value), next(nullptr) {}
    };
    Node* head;
    size_t listSize;

public:
    ForwardList();
    ForwardList(const ForwardList& other);  // Конструктор копирования
    ~ForwardList();

    ForwardList& operator=(const ForwardList& other);  // Оператор присваивания
    
    void push_front(double value);
    void pop_front();
    double& front();
    const double& front() const;
    size_t size() const;
    bool empty() const;
    void clear();
};

} // namespace MyList

#endif
