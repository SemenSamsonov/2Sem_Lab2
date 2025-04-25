#include "ForwardList.h"
#include <stdexcept>

namespace MyList {

ForwardList::ForwardList() : head(nullptr), listSize(0) {}

ForwardList::ForwardList(const ForwardList& other) : head(nullptr), listSize(0) {
    Node* current = other.head;
    Node* prev = nullptr;
    
    while (current != nullptr) {
        Node* newNode = new Node(current->data);
        if (prev == nullptr) {
            head = newNode;
        } else {
            prev->next = newNode;
        }
        prev = newNode;
        current = current->next;
        listSize++;
    }
}

ForwardList::~ForwardList() {
    clear();
}

ForwardList& ForwardList::operator=(const ForwardList& other) {
    if (this != &other) {
        clear();
        Node* current = other.head;
        Node* prev = nullptr;
        
        while (current != nullptr) {
            Node* newNode = new Node(current->data);
            if (prev == nullptr) {
                head = newNode;
            } else {
                prev->next = newNode;
            }
            prev = newNode;
            current = current->next;
            listSize++;
        }
    }
    return *this;
}

void ForwardList::push_front(double value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    listSize++;
}

void ForwardList::pop_front() {
    if (head == nullptr) {
        throw std::runtime_error("List is empty");
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    listSize--;
}

double& ForwardList::front() {
    if (head == nullptr) {
        throw std::runtime_error("List is empty");
    }
    return head->data;
}

const double& ForwardList::front() const {
    if (head == nullptr) {
        throw std::runtime_error("List is empty");
    }
    return head->data;
}

size_t ForwardList::size() const {
    return listSize;
}

bool ForwardList::empty() const {
    return head == nullptr;
}

void ForwardList::clear() {
    while (head != nullptr) {
        pop_front();
    }
}

} 
