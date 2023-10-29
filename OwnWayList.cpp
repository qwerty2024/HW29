#include "OwnWayList.h"

void OwnWayList::addFirstNode(int value)
{
    Node* newNode = new Node(value);

    head = newNode;
}

// Оговорки:
// очередь не пустая
// вставляется элемент в середину или конец списка, то есть вставку в начало списка не нужно рассматривать
// если pos больше длины списка, то нужно вставить элемент в конец списка
void OwnWayList::insertIntoMiddle(int value, int pos)
{
    // создаем новый узел 
    Node* newNode = new Node(value);

    int currPos = 0;
    bool flag = false;

    queue_mutex.lock();

    Node* current = head;

    current->node_mutex.lock();

    queue_mutex.unlock();


    while (currPos < pos - 1 && current->next != nullptr)
    {
        this_thread::sleep_for(chrono::nanoseconds(50)); // небольшая задержка, что бы подержать подольше указатель и была вероятность зафейлиться
        current->next->node_mutex.lock();

        Node* tmp = current;
        current = current->next;
        currPos++;

        tmp->node_mutex.unlock();
    }

    if (current->next == nullptr)
    {
        this_thread::sleep_for(chrono::nanoseconds(50)); // небольшая задержка, что бы подержать подольше указатель и была вероятность зафейлиться
        current->next = newNode;
        current->node_mutex.unlock();
    }
    else
    {
        current->next->node_mutex.lock();

        Node* next_node = current->next;
        this_thread::sleep_for(chrono::nanoseconds(50)); // небольшая задержка, что бы подержать подольше указатель и была вероятность зафейлиться
        current->next = newNode;
        newNode->next = next_node;

        next_node->node_mutex.unlock();
        current->node_mutex.unlock();
    }
}

void OwnWayList::unsave_insertIntoMiddle(int value, int pos)
{
    // создаем новый узел 
    Node* newNode = new Node(value);

    int currPos = 0;

    Node* current = head;
    // в цикле идем по списку, пока список не кончится, или пока не дойдем до позиции
    while (currPos < pos - 1 && current->next != nullptr)
    {
        current = current->next;
        currPos++;
    }
    // меняем указатель на следующий узел на указатель на новый узел
    Node* next = current->next;
    this_thread::sleep_for(chrono::nanoseconds(50)); // небольшая задержка, что бы подержать подольше указатель и была вероятность зафейлиться
    current->next = newNode;
    // связываем список обратно, меняем указатель на узел, следующий после нового узла, на указатель на узел, следующий за current
    newNode->next = next;
}

void OwnWayList::printer()
{
    Node* node = head;

    while (node != nullptr)
    {
        cout << node->value << " ";
        node = node->next;
    }
    cout << endl;

    delete node;
}

int OwnWayList::count(int value) // количество значений value в списке
{
    Node* node = head;
    int res = 0;

    while (node != nullptr)
    {
        if (value == node->value) res++;
        node = node->next;
    }

    delete node;

    return res;
}

bool OwnWayList::two_occurrences()
{
    for (int i = 1; i < N + 1; ++i)
    {
        if (this->count(i) != 2)
        {
            cout << "Count " << i << "?" << endl;
            return false;
        }
    }

    return true;
}