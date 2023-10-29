#pragma once

#include <mutex>
#include <iostream>
#include <chrono>
#include <thread>

#define N 100

using namespace std;

struct Node
{
    Node(int _value) : value(_value), next(nullptr) {}

    int value;
    Node* next;
    mutex node_mutex;
};

class OwnWayList
{
public:
    OwnWayList() : head(nullptr) {}


public:
    void addFirstNode(int value);
    void insertIntoMiddle(int value, int pos);
    void unsave_insertIntoMiddle(int value, int pos);

    void printer(); // выводит список
    int count(int value); // количество вхождений значения value в список
    bool two_occurrences(); // проверка на корректность работы нитей

private:
    Node* head;
    mutex queue_mutex;
};

