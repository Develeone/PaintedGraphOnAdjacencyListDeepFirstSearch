//
// Created by Ouden on 30.03.2016.
//

#ifndef GRAPHDEEPSEARCH_LIST_H
#define GRAPHDEEPSEARCH_LIST_H

#pragma once


#pragma once

#include <iostream>

template <class T = int>
struct ListElement
{
    ListElement* next;
    T value;
};

template <class T = int>
class List
{
private:
    ListElement<T>* head;

public:
    List()
    {
        head = nullptr;
    }

    int Count() {
        if (head == nullptr)
            return 0;

        int count = 1;
        ListElement<T>* currElement = head;

        while (currElement->next != nullptr) {
            currElement = currElement->next;
            count++;
        }
        return count;
    }

    ListElement<T>* GetLast() {
        ListElement<T>* currElement = head;
        while (currElement->next != nullptr) {
            currElement = currElement->next;
        }
        return currElement;
    }

    ListElement<T>* GetListElementByIndex(int index) {
        ListElement<T>* currElement = head;
        for (int i = 0; i < index; i++) {
            currElement = currElement->next;
        }
        return currElement;
    }

    T &operator [] (int index) {
        return GetListElementByIndex(index)->value;
    }

    void Add(T _value) {
        ListElement<T>* newElement = new ListElement<T>;
        newElement->value = _value;
        newElement->next = nullptr;

        if (head == nullptr) {
            head = newElement;
        }
        else
        {
            GetLast()->next = newElement;
        }
    }

    void Print() {
        ListElement<T>* currElement = head;
        while (currElement != nullptr) {
            std::cout << currElement->value << " " << std::endl;
            currElement = currElement->next;
        }
    }

    void operator = (const List & right) {
        ListElement<T>* currElement = right.head;
        while (currElement != nullptr) {
            Add(currElement->value);
            currElement = currElement->next;
        }
    }

    void Clear(){
        head = nullptr;
    }

};


#endif //GRAPHDEEPSEARCH_LIST_H
