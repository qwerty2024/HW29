#include <iostream>
#include <thread>
//#include <chrono>
#include "OwnWayList.h"

using namespace std;


void go_thread(OwnWayList& que, bool safty)
{
    for (int i = 1; i < N + 1; ++i)
    {
        if (safty)
            que.insertIntoMiddle(i, i);
        else
            que.unsave_insertIntoMiddle(i, i);
    }
}

void test(bool safly)
{
    OwnWayList que;

    que.addFirstNode(-1); // по условию задания очередь всегда не пустая

    thread t1(go_thread, ref(que), safly);
    thread t2(go_thread, ref(que), safly);


    t1.join();
    t2.join();


    que.printer(); // опционально

    // проверка, что каждое число от 1 до N записалось 2 раза
    if (que.two_occurrences()) cout << "Good!" << endl;
    else cout << "Bad!" << endl;
}

int main()
{
    // тестируем структуру с вызовом непотокобезопасного метода вставки
    test(false);

    // тестируем структуру с вызовом потокобезопасного метода вставки
    test(true);

    return 0;
}



