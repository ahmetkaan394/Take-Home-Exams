#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    
    if (obj.head != NULL && this != &obj){
        Node<T>* temp = obj.head;
        Node<T>* new_Node = new Node<T>(temp -> data);
        Node<T>* new_Head = new_Node;
        if (obj.size > 1){
            for(int i = 0; i < obj.size; i++){
                if (i == obj.size - 1){
                    new_Node -> next = new_Head;
                    new_Head -> prev = new_Node;
                }
                else {
                    new_Node -> next = new Node<T>((temp -> next) -> data);
                    (new_Node -> next) -> prev = new_Node;
                    new_Node = new_Node -> next;
                    temp = temp -> next;
                }
            }
            head = new_Head;
            size = obj.size;
        }
        else if (obj.size == 1){
            new_Head -> next = new_Head;
            new_Head -> prev = new_Head;
            head = new_Head;
            size = 1;
        }
        
    }
    else if (obj.head == NULL){
        head = NULL;
        size = 0;
    }

}

template<class T>
LinkedList<T>::~LinkedList()
{
    if (head != NULL) {
        Node<T>* temp = head;
        if (size == 1){
            delete temp;
            head = NULL;
            size = 0;
        }
        else {
            Node<T>* temp2;
            temp = head -> prev;
            do{
                temp2 = temp;
                temp = temp -> prev;
                delete temp2;
            }while(temp != head);
            delete temp;
            head = NULL;
            size = 0;
        }
    }
    else {
        head = NULL;
        size = 0;
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    
    if (rhs.head != NULL && this != &rhs){
        this -> ~LinkedList();
        Node<T>* temp = rhs.head;
        Node<T>* new_Node = new Node<T>(temp -> data);
        Node<T>* new_Head = new_Node;
        if (rhs.size > 1){
            for(int i = 0; i < rhs.size; i++){
                if (i == rhs.size - 1){
                    new_Node -> next = new_Head;
                    new_Head -> prev = new_Node;
                }
                else {
                    new_Node -> next = new Node<T>((temp -> next) -> data);
                    (new_Node -> next) -> prev = new_Node;
                    new_Node = new_Node -> next;
                    temp = temp -> next;
                }
            }
            head = new_Head;
            size = rhs.size;
        }
        else if (rhs.size == 1){
            new_Head -> next = new_Head;
            new_Head -> prev = new_Head;
            head = new_Head;
            size = 1;
        }
        
    }
    else if (rhs.head == NULL){
        head = NULL;
        size = 0;
    }
    return *this;
}

template<class T>
int LinkedList<T>::getSize() const
{
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    if (head == NULL){
        return true;
    }
    return false;
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    Node<T>* temp = head;
    for (int i = 0; i < size; i++){
        if (temp == node){
            return true;
        }
        temp = temp -> next;
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    Node<T>* temp = head;
    if (temp == NULL){
        return NULL;
    }
    return temp;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    if (head == NULL){
        return NULL;
    }
    Node<T>* temp = head -> prev;
    return temp;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    if (!isEmpty()){
        Node<T>* temp = head;
        do{
            if (temp -> data == data){
                return temp;
            }
            temp = temp -> next;
        }while (temp != head);
    }
    return NULL;   
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    if (!isEmpty()){
        Node<T>* temp = head;
        Node<T>* first = head;
        int i = 0;
        if (size <= index){
            return NULL;
        }
        do{
            if (i == index){
                return temp;
            }
            temp = temp -> next;
            i++;
        }while (temp != first);
    }
    return NULL;
}

template<class T>
void LinkedList<T>::append(const T &data)
{
    if (!isEmpty()){
        Node<T>* temp = head -> prev;
        Node<T>* new_Node = new Node<T>(data);
        
        new_Node -> next = head;
        new_Node -> prev = temp;
        head -> prev = new_Node;
        temp -> next = new_Node;
        size++;
    }
    else {
        Node<T>* new_Node = new Node<T>(data);
        head = new_Node;
        head -> next = head;
        head -> prev = head;
        size++;
    }
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    if (!isEmpty()){
        Node<T>* temp = head -> prev;
        Node<T>* new_Node = new Node<T>(data);
        
        new_Node -> next = head;
        new_Node -> prev = temp;
        head -> prev = new_Node;
        temp -> next = new_Node;
        head = new_Node;
        size++;
    }
    else {
        Node<T>* new_Node = new Node<T>(data);
        head = new_Node;
        head -> next = head;
        head -> prev = head;
        size++;
    }
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    if (!isEmpty()){
        Node<T>* temp = head;
        Node<T>* first = head;
        do{
            if (temp -> data == node -> data){
                Node<T>* new_Node = new Node<T>(data);
                new_Node -> next = temp -> next;
                (temp -> next) -> prev = new_Node;
                temp -> next = new_Node;
                new_Node -> prev = temp;
            }
            temp = temp -> next;
        }while (temp != first);
        size++;
    }
    
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    if (!isEmpty()){
        Node<T>* temp = head;
        Node<T>* first = head;
        int i = 0;
        do{
            if (i == index){
                Node<T>* new_Node = new Node<T>(data);
                new_Node -> next = temp;
                new_Node -> prev = temp -> prev;
                (temp -> prev) -> next = new_Node;
                temp -> prev = new_Node;
                if (index == 0){
                    head = temp;
                }
            }
            temp = temp -> next;
            i++;
        }while ((temp != first) && (index < size));
        size++;
    }
    else {
        Node<T>* new_Node = new Node<T>(data);
        head = new_Node;
        size++;
    }
    
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    int count = 0;
    Node<T>* temp = head;
    for (int i = 0; i < size; i++){
        if (temp -> data == node -> data){
            return count;
        }
        temp = temp -> next;
        count++;
    }
    return -1;
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    if (!isEmpty()){
        Node<T>* temp = head;
        Node<T>* temp2 = head;
        int i = 0;
        while (i != currentIndex){
            temp = temp -> next;
            i++;
        }
        i = 0;
        while (i != newIndex){
            temp2 = temp2 -> next;
            i++;
        }
        if (newIndex >= size && currentIndex < size){
            if (currentIndex != size-1){
                if (currentIndex == 0){
                    head = head -> next;
                }
                (temp -> prev) -> next = temp -> next;
                (temp -> next) -> prev = temp -> prev;
                temp -> next = head;
                temp -> prev = head -> prev;
                (head -> prev) -> next = temp;
                head -> prev = temp;
            }
        }
        else if (newIndex < size && currentIndex < size && currentIndex != newIndex){
            if (currentIndex == 0){
                head = head -> next;
                (temp -> prev) -> next = temp -> next;
                (temp -> next) -> prev = temp -> prev;
                temp -> next = temp2 -> next;
                temp -> prev = temp2;
                (temp2 -> next) -> prev = temp;
                temp2 -> next = temp;
            }
            else if (newIndex == 0){
                if (currentIndex == size - 1){
                    head = head -> prev;
                }
                else {
                    (temp -> prev) -> next = temp -> next;
                    (temp -> next) -> prev = temp -> prev;
                    temp -> next = head;
                    temp -> prev = head -> prev;
                    head -> prev = temp;
                    (head -> prev) -> next = temp;
                    head = temp;
                }
            }
            else if (currentIndex < newIndex && currentIndex != 0){
                (temp -> prev) -> next = temp -> next;
                (temp -> next) -> prev = temp -> prev;
                temp -> next = temp2 -> next;
                temp -> prev = temp2;
                (temp2 -> next) -> prev = temp;
                temp2 -> next = temp;
            }
            else if (currentIndex > newIndex && newIndex != 0){
                (temp -> prev) -> next = temp -> next;
                (temp -> next) -> prev = temp -> prev;
                temp -> next = temp2;
                temp -> prev = temp2 -> prev;
                (temp2 -> prev) -> next = temp;
                temp2 -> prev = temp;
            }
        }
    }
    
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    
    if (!isEmpty()){
        if (containsNode(node)){
            Node<T>* temp = head;
            while (temp != node){
                temp = temp -> next;
            }
            if (size == 1){
                delete temp;
                head = NULL;
                size--;
            }
            else {
                if (temp == head){
                    head = head -> next;
                    (temp -> prev) -> next = temp -> next;
                    (temp -> next) -> prev = temp -> prev;
                    delete temp;
                    size--;
                }
                else {
                    (temp -> prev) -> next = temp -> next;
                    (temp -> next) -> prev = temp -> prev;
                    delete temp;
                    size--;
                }
            }
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{
    Node<T>* temp = head;
    Node<T>* temp2;
    int count = 0;
    if (!isEmpty()){
        if (size == 1 && head -> data == data){
            delete temp;
            head = NULL;
            size=0;
            return;
        }
        do {
            if (temp -> data == data){
                count++;
            }
            temp = temp -> next;
        }while (temp != head);
        temp = head;
        do{
            if (temp -> data == data && head -> data != data){
                temp2 = temp;
                temp = temp -> next;
                (temp2 -> prev) -> next = temp;
                temp -> prev = temp2 -> prev;
                delete temp2;
                count--;
                size--;
                if (size == 0){
                    head = NULL;
                    break;
                }
            }
            else if (head -> data == data){
                while (head -> data == data){
                    temp2 = temp;
                    temp = temp -> next;
                    (temp2 -> prev) -> next = temp;
                    temp -> prev = temp2 -> prev;
                    delete temp2;
                    head = temp;
                    count--;
                    size--;
                }
                if (size == 0){
                    head = NULL;
                    break;
                }
            }
            else {
                temp = temp -> next;
            }
        }while (size > 0 && temp != head && count != 0);
    } 
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    if (!isEmpty()){
        if (index >= size || index < 0){
            return;
        } 
        else if (index < size){
            Node<T>* temp = head;
            Node<T>* temp2;
            if (index == 0){
                if (size != 1){
                    temp2 = head;
                    head = head -> next;
                    (temp2 -> prev) -> next = head;
                    head -> prev = temp2 -> prev;
                    delete temp2;
                    size--;
                }
                else if (size == 1){
                    delete temp;
                    head = NULL;
                    size = 0;
                }
            }
            else {
                int i = 0;
                while (i != index){
                    temp = temp -> next;
                    i++;
                }
                temp2 = temp;
                temp = temp -> next;
                (temp2 -> prev) -> next = temp;
                temp -> prev = temp2 -> prev;
                delete temp2;
                size--;
            }
        }
    }
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    Node<T>* temp = head;
    Node<T>* temp2 = head;

    for (int i = 0; i < size - 1; i++){
        temp = temp -> next;
        delete temp2;
        temp2 = temp;
    }
    delete temp;
    head = NULL;
    size = 0;
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    do {
        std::cout << *node << std::endl;
        node = node->next;
    }
    while (node != this->getFirstNode());
}

#endif //LINKEDLIST_H
